/* g++ -Wall -Wextra -lgmp -pthread -o monte-carlo monte-carlo.cc common.c */

#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <linux/random.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include <gmp.h>
#include <pthread.h>

#include "util.h"

using namespace std;

struct thread_ctx_t;

struct opts_t {
    mpz_t  numiters;   /* -n */
    int    numworkers; /* -w */
    time_t tgtime;     /* -t */
};

struct calc_ctx_t {
    mpz_t                numiters;
    int                  numworkers;
    time_t               tgtime;
    vector<thread_ctx_t> workers;
};

struct thread_ctx_t {
    int         id;
    mpz_t       numiters_worker;
    mpz_t       result;
    seed_t      seed;
    pthread_t   thread;
    calc_ctx_t *calc_ctx;
};

struct fragment_t {
    int total;
    int oncircle;
};

uint64_t getseed(void) {
    /* Linux-specific */

    static seed_t result;
    while (syscall(SYS_getrandom, (void *)result.tab,
                sizeof(result.tab), 0) == -1)
    {
        if (errno == EINTR) continue;

        perror("getrandom");
        exit(1);
    }

    return result.num;
}

int getcores(void) {
    /* Linux-specific */

    return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

bool on_circle(double x, double y) {
    return x * x + y * y < 1;
}

void *run_worker(void *arg) {
    thread_ctx_t *ctx = (thread_ctx_t *)arg;
    mpz_init(ctx->result);
    Rng rng(ctx->seed.num);

    mpz_t i;
    mpz_init(i);
    for (mpz_set_ui(i, 0); mpz_cmp(i, ctx->numiters_worker) < 0;
            mpz_add_ui(i, i, 1))
    {
        double x = rng.next_double();
        double y = rng.next_double();
        if (on_circle(x, y)) {
            mpz_add_ui(ctx->result, ctx->result, 1);
        }
    }

    mpz_clear(i);
    return nullptr;
}

void dispatch_worker(calc_ctx_t *ctx, thread_ctx_t *thread_ctx,
        int id, mpz_t numiters)
{
    mpz_init(thread_ctx->numiters_worker);
    thread_ctx->id = id;
    mpz_set(thread_ctx->numiters_worker, numiters);
    thread_ctx->calc_ctx = ctx;
    thread_ctx->seed.num = getseed();
    pthread_create_w(&thread_ctx->thread, nullptr, run_worker,
            (void *)thread_ctx);
    fprintf(stderr, "[Info] Dispatched a worker #%d\n", thread_ctx->id);
}

void calc_prob(mpf_t result, opts_t *opts) { 
    calc_ctx_t ctx;
    mpz_init(ctx.numiters);
    mpz_set(ctx.numiters, opts->numiters);
    ctx.numworkers = opts->numworkers;
    ctx.workers.resize(ctx.numworkers);

    mpz_t numiters_worker;
    mpz_t rnumiters_worker;
    mpz_init(numiters_worker);
    mpz_init(rnumiters_worker);
    mpz_fdiv_qr_ui(numiters_worker, rnumiters_worker, ctx.numiters,
            ctx.numworkers);

    //assert(numiters > numworkers);
    //assert(numworkers > 0);
    //assert(numiters_worker * ctx.numworkers + rnumiters_worker == numiters);

    int x = 0;
    if (mpz_cmp_ui(rnumiters_worker, 0) != 0) {
        mpz_t asdf;
        mpz_init(asdf);
        mpz_add(asdf, numiters_worker, rnumiters_worker);
        dispatch_worker(&ctx, &ctx.workers[0], x++, asdf);
    }
    for (int i = x; i < ctx.numworkers; i++) {
        dispatch_worker(&ctx, &ctx.workers[i], i, numiters_worker);
    }
    for (int i = 0; i < ctx.numworkers; i++) {
        pthread_join_w(ctx.workers[i].thread, nullptr);
    }

    mpz_t sum;
    mpz_init(sum);
    for (int i = 0; i < ctx.numworkers; i++) {
        mpz_add(sum, sum, ctx.workers[i].result);
    }
    
    mpf_t numiters_d;
    mpf_set_z(result, sum);
    mpf_init(numiters_d);
    mpf_set_z(numiters_d, ctx.numiters);
    mpf_div(result, result, numiters_d);

    mpz_clear(ctx.numiters);
    mpz_clear(numiters_worker);
    mpz_clear(rnumiters_worker);
    mpz_clear(sum);
    mpf_clear(numiters_d);
}

void calc_pi(mpf_t result, opts_t *opts) {
    calc_prob(result, opts);
    mpf_mul_ui(result, result, 4);
}

int parse_numiters(const char *s) {
    /* TODO: */
    return atoi(s);
}

void print_usage(int argc, char **argv) {
    UNUSED(argc);

    fprintf(stderr,
        "Usage: %s [options]\n"
        "Options:\n"
        "  -n <iterations> Specify the number of iterations\n"
        "  -t <time>       Specify how long the computations will be run for\n"
        "  -w <workers>    Specify the number of threads, defaults to number of cores\n",
        argv[0]
    );
}

void parse_options(opts_t *ret, int argc, char **argv) {
    mpz_init(ret->numiters);
    mpz_set_si(ret->numiters, -1);
    ret->tgtime = -1;
    ret->numworkers = -1;

    int opt;
    while ((opt = getopt(argc, argv, "n:t:w:")) != -1) {
        switch (opt) {
        case 'n':
            if (gmp_sscanf(optarg, "%Zd\n", ret->numiters) != 1) {
                fprintf(stderr, "Error: invalid number of iterations\n");
                exit(1);
            }
            break;

        case 't':
            ret->tgtime = strtol(optarg, nullptr, 10);
            if (ret->tgtime == 0) {
                ret->tgtime = -1;
                fprintf(stderr, "Warning: invalid target time\n");
            }
            break;

        case 'w':
            ret->numworkers = strtol(optarg, nullptr, 10);
            if (ret->numworkers == 0) {
                ret->numworkers = -1;
                fprintf(stderr, "Warning: invalid number of workers\n");
            }
            break;

        default:
            fprintf(stderr, "Warning: unknown option: -%c\n", (char)opt);
            break;
        }
    }

    if (mpz_cmp_si(ret->numiters, -1) == 0) {
        print_usage(argc, argv);
        exit(1);
    }

    if (ret->numworkers == -1) {
        int numcores = getcores();
        if (numcores == -1) {
            fprintf(stderr,
                    "Warning: could not get the number of cores available\n");
            numcores = 2;
        }
        ret->numworkers = numcores;
    }

    if (ret->numworkers <= 0 || ret->numworkers > 32) {
        fprintf(stderr, "Error: number of workers must be between 1 and 32\n");
        exit(1);
    }
    if (mpz_cmp_si(ret->numiters, ret->numworkers) < 0) {
        fprintf(stderr,
            "Error: number of iterations must be at least equal to the "
            "number of workers\n"
        );
        exit(1);
    }
   
}

/* TODO:
 * Documentation
 * Run for specified time
 * Live results update (signals)
 * Better input validation
 * Weird artifacts related to the number of iterations
 *
 * */
int main(int argc, char **argv) {
    mpf_set_default_prec(1024);

    opts_t opts;
    parse_options(&opts, argc, argv);

    mpf_t ret;
    mpf_init(ret);
    calc_pi(ret, &opts);
    gmp_printf("Approximation of pi:\n%.Ff\n", ret);

    mpf_clear(ret);
    mpz_clear(opts.numiters);
    return 0;
}

