import java.util.Arrays;

public class PriorityQueue<T extends Comparable> {
    private static final int INIT_SIZE = 16;

    private int sz;
    private T[] items; // Note: 0th item is unused

    public PriorityQueue() {
        this(INIT_SIZE);
    }
    
    public PriorityQueue(int initSize) {
        this.sz = 0;
        this.items = (T[]) new Comparable[initSize];
    }

    public void insert(T item) {
        if (this.sz + 1 >= this.items.length) {
            resize(2 * this.items.length);
        }
        this.items[++this.sz] = item;
        bubbleUp(this.sz);
    }

    public T getMin() {
        return this.items[1];
    }

    public T removeMin() {
        T result = this.items[1];
        this.items[1] = this.items[this.sz--];
        bubbleDown(1);
        return result;
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    public int size() {
        return this.sz;
    }

    public static <E extends Comparable> PriorityQueue<E> heapify(E[] a) {
        return null;
    }

    private void bubbleUp(int k) {
        int p = k / 2;
        while (k > 1 && this.items[p].compareTo(this.items[k]) > 0) {
            swap(k, p);
            k = p;
            p = k / 2;
        }
    }

    private void bubbleDown(int k) {
        while (2 * k <= this.sz) {
            int c = 2 * k;
            if (c < this.sz && this.items[2 * k].compareTo(this.items[2 * k + 1]) > 0) {
                c++;
            }

            if (this.items[k].compareTo(this.items[c]) < 0) break;
            swap(k, c);
            k = c;
        } 
    }

    private void resize(int newsz) {
        this.items = Arrays.copyOf(this.items, newsz);
    }

    private void swap(int i, int j) {
        T t = this.items[i];
        this.items[i] = this.items[j];
        this.items[j] = t;
    }

    public static void main(String[] args) {
        PriorityQueue<Integer> pq = new PriorityQueue();
        assert pq.size() == 0;
        assert pq.isEmpty();
        pq.insert(3);
        assert pq.size() == 1;
        assert !pq.isEmpty();
        pq.insert(1);
        assert pq.getMin() == 1;
        pq.insert(2);
        assert pq.getMin() == 1;
        assert pq.size() == 3;
        pq.insert(0);
        assert pq.getMin() == 0;
        pq.insert(4);
        assert pq.size() == 5;
        assert pq.getMin() == 0;
        assert pq.removeMin() == 0;
        assert pq.getMin() == 1;

        pq = new PriorityQueue();
        pq.insert(4);
        assert pq.getMin() == 4;
        pq.insert(9);
        assert pq.getMin() == 4;
        pq.insert(4);
        assert pq.getMin() == 4;
        pq.insert(8);
        assert pq.getMin() == 4;
        pq.insert(13);
        pq.insert(11);
        pq.insert(9);
        pq.insert(4);
        pq.insert(12);
        assert pq.size() == 9;
        assert pq.removeMin() == 4;
        assert pq.removeMin() == 4;
        assert pq.removeMin() == 4;
        assert pq.removeMin() == 8;
        assert pq.removeMin() == 9;
        assert pq.removeMin() == 9;
        assert pq.removeMin() == 11;
        assert pq.removeMin() == 12;
        assert pq.removeMin() == 13;
        assert pq.isEmpty();

        
    }
}

