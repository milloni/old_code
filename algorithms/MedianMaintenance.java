import java.util.PriorityQueue;
import java.util.Scanner;
import java.io.InputStream;
import java.io.BufferedInputStream;

import java.util.Collections;

public class MedianMaintenance {
    private static final int INITIAL_CAPACITY = 10000;
    private int size;
    private int result;
    private PriorityQueue<Integer> minpq;
    private PriorityQueue<Integer> maxpq;

    public MedianMaintenance(InputStream is) {
        this.size = 0;
        this.result = 0;
        this.minpq =
            new PriorityQueue<Integer>(INITIAL_CAPACITY, (x, y) -> x - y);
        this.maxpq =
            new PriorityQueue<Integer>(INITIAL_CAPACITY, (x, y) -> y - x);
        
        Scanner sc = new Scanner(is);
        int v = sc.nextInt();
        this.result += v;
        this.maxpq.add(v);
        while (sc.hasNextInt()) {
            v = sc.nextInt();
            if (this.maxpq.peek() > v) {
                this.maxpq.add(v);
            } else {
                this.minpq.add(v);
            }
            this.size++;
            rebalance();
            computeMedian();
        }

        this.result %= 10000;
    }

    public int getMedian() {
        return this.result;
    }

    private void rebalance() {
        if (this.maxpq.size() - this.minpq.size() > 1) {
            this.minpq.add(this.maxpq.poll());
        } else if (this.minpq.size() - this.maxpq.size() > 1) {
            this.maxpq.add(this.minpq.poll());
        }
    }

    private void computeMedian() {
        if (this.maxpq.size() - this.minpq.size() == 1) {
            this.result += this.maxpq.peek();
        } else if (this.minpq.size() - this.maxpq.size() == 1) {
            this.result += this.minpq.peek();
        } else {
            this.result += this.maxpq.peek();
        }
    }

    public static void main(String[] args) {
        MedianMaintenance mm =
            new MedianMaintenance(new BufferedInputStream(System.in));
        System.out.println(mm.getMedian());
    }
}

