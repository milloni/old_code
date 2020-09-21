import java.util.Set;
import java.util.HashSet;
import java.util.Scanner;
import java.io.InputStream;
import java.io.BufferedInputStream;

public class TwoSum {
    private static final long T1 = -10000;
    private static final long T2 = 10000;
    private static final int INITIAL_CAPACITY = 1 << 21;

    private Set<Long> numbers;
    private long t1, t2;
    private int count;

    private double progress;
    private boolean running;

    public TwoSum(InputStream is, long t1, long t2) {
        init(t1, t2);
        constructSet(is);

        Runnable rProgress = () -> {
            try {
                while (this.running) {
                    System.out.print(String.format("\rProgress: %.2f%%", this.progress));
                    System.out.flush();
                    Thread.sleep(33); // 30fps
                }
                System.out.println();
            } catch (InterruptedException e) { }
            
        };
        Thread progressThread = new Thread(rProgress);
        progressThread.start();

        for (long i = t1; i <= t2; i++) {
            if (sumsTo(i)) {
                this.count++;
            }
            this.progress = (100.0 * (i - t1)) / (t2 - t1);
        }

        this.running = false;
        try {
            progressThread.join();
        } catch (InterruptedException e) { }
    }

    public int getCount() {
        return this.count;
    }

    private void init(long t1, long t2) {
        if (t1 >= t2) {
            throw new IllegalArgumentException("t2 must be larger than t1");
        }

        this.t1 = t1;
        this.t2 = t2;
        this.count = 0;
        this.running = true;
        this.progress = 0;
    }

    private void constructSet(InputStream is) {
        this.numbers = new HashSet<Long>(INITIAL_CAPACITY);
        Scanner sc = new Scanner(is);
        while (sc.hasNextLong()) {
            long v = sc.nextLong();
            this.numbers.add(v);
        }
    }

    private boolean sumsTo(long t) {
        for (long x : this.numbers) {
            if (x != t - x && this.numbers.contains(t - x)) {
                return true;
            }
        }

        return false;
    } 
    
    public static void main(String[] args) {
        TwoSum ts = new TwoSum(new BufferedInputStream(System.in), T1, T2);
        System.out.println(ts.getCount());
    }
}

