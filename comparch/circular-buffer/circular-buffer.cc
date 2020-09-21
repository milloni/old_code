#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <array>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define UNUSED(x) (void)(x)

constexpr int BUFSZ = 4;
constexpr int NITEMS = 16;
constexpr int MAXWORK = 10; // seconds

void my_pthread_mutex_lock(pthread_mutex_t *mutex);
void my_pthread_mutex_unlock(pthread_mutex_t *mutex);

class scoped_lock {
private:
    pthread_mutex_t *mutex;
public:
    scoped_lock(pthread_mutex_t *mutex);
    ~scoped_lock();
};

scoped_lock::scoped_lock(pthread_mutex_t *cmutex) {
    mutex = cmutex;
    my_pthread_mutex_lock(mutex);
}

scoped_lock::~scoped_lock(void) {
    my_pthread_mutex_unlock(mutex);
}

template <typename T, size_t N>
class circular_buffer {
private:
    int widx;
    int ridx;
    std::array<T, N> buf;
    pthread_mutex_t mutex;
    int sz;

public:
    circular_buffer(void);
    T read(void);
    void write(T t);
    size_t size(void);
    bool empty(void);
    bool full(void);
};

template <typename T, size_t N>
circular_buffer<T, N>::circular_buffer(void) :
        widx(0),
        ridx(0),
        buf(std::array<T, N>()),
        mutex(PTHREAD_MUTEX_INITIALIZER),
        sz(0) {}

template <typename T, size_t N>
T circular_buffer<T, N>::read(void) {
    scoped_lock l(&mutex);
    if (widx == ridx) throw std::logic_error("No more data to read");

    printf("%d %d\n", widx, ridx);
    T result = buf[ridx];
    ridx = (ridx + 1) % N;
    sz--;
    return result;
}

template <typename T, size_t N>
void circular_buffer<T, N>::write(T t) {
   scoped_lock l(&mutex);
   if (ridx == widx + 1 || (ridx == 0 && widx == N - 1)) {
       throw std::logic_error("Buffer is full"); 
   }

   printf("%d %d\n", widx, ridx);
   buf[widx] = t;
   widx = (widx + 1) % N;
   sz++;
}

template <typename T, size_t N>
size_t circular_buffer<T, N>::size(void) {
    scoped_lock l(&mutex);
    return sz;
}

template <typename T, size_t N>
bool circular_buffer<T, N>::empty(void) {
    return size() == 0;
}

template <typename T, size_t N>
bool circular_buffer<T, N>::full(void) {
    return size() == N;
}

circular_buffer<int, BUFSZ> cbuf;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void _f(const char *msg) {
    perror(msg);
    exit(1);
}

char *my_strerror(int errnum) {
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    my_pthread_mutex_lock(&mutex);

    const char *static_result = strerror(errnum);
    if (static_result == nullptr) _f("strerror");
    size_t sz = strlen(static_result) + 1;
    char *result = (char *) malloc(sizeof(char) * sz);
    if (result == nullptr) _f("malloc");
    strncpy(result, static_result, sz);
    result[sz - 1] = '\0';

    my_pthread_mutex_unlock(&mutex);
    return result;
}

void _f2(int errnum, const char *msg) {
    char *errdesc = my_strerror(errnum);
    if (errdesc != nullptr) {
        fprintf(stderr, "%s: %s\n", msg, errdesc);
    } else {
        fprintf(stderr, "Unknown error\n");
    }

    free(errdesc);
    exit(1);
}

void my_pthread_mutex_lock(pthread_mutex_t *mutex) {
    int ret = pthread_mutex_lock(mutex);
    if (ret != 0) _f2(ret, "pthread_mutex_lock");
}

void my_pthread_mutex_unlock(pthread_mutex_t *mutex) {
    int ret = pthread_mutex_unlock(mutex);
    if (ret != 0) _f2(ret, "pthread_mutex_unlock");
}

void *run_prod(void *arg) {
    UNUSED(arg);

    for (int i = 0; i < NITEMS; i++) {
        sleep(rand() % MAXWORK);
        int item = i;
        printf("[Producer] Produced item %d\n", item);

        while (cbuf.full()) sleep(0);
        cbuf.write(item);
    }

    return nullptr;
}

void *run_cons(void *arg) {
    UNUSED(arg);

    int i = 0;
    while (i < NITEMS) {
        if (cbuf.empty()) continue;
        int item = cbuf.read();

        sleep(rand() % MAXWORK);
        printf("[Consumer] Consumed item %d\n", item);
        i++;
    }

    return nullptr;
}

int main(void) {
    srand(0xfaceb00c);
    pthread_t prod, cons;
    int ret = pthread_create(&prod, nullptr, run_prod, nullptr) != 0;
    if (ret != 0) _f2(ret, "pthread_create");
    ret = pthread_create(&cons, nullptr, run_cons, nullptr);
    if (ret != 0) _f2(ret, "pthread_create");

    ret = pthread_join(prod, nullptr);
    if (ret != 0) _f2(ret, "pthread_join");
    ret = pthread_join(cons, nullptr);
    if (ret != 0) _f2(ret, "pthread_join");

    return 0;

}

