import java.util.Iterator;

public class QueueArray<T> implements Iterable<T> {
    private static final int INIT_SIZE = 10;

    private T[] items = (T[]) new Object[INIT_SIZE];
    private int sz = 0;

    public void enqueue(T item) {
        if (this.items.length <= this.size()) {
            this.resize(2 * this.items.length);
        }
        insertBegin(item);
    }

    public T dequeue() {
        T v = this.items[--this.sz];
        this.items[this.sz] = null;
        return v;
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    public int size() {
        return this.sz;
    }

    public Iterator<T> iterator() {
        return new QueueIterator();
    }

    private void resize(int newsz) {
        assert newsz > this.items.length;
        T[] t = this.items;
        this.items = (T[]) new Object[newsz];
        for (int i = 0; i < t.length; i++) {
            this.items[i] = t[i];
        }
    }

    private void insertBegin(T item) {
        for (int i = this.size() - 1; i >= 0; i--) {
            this.items[i + 1] = this.items[i];
        }
        this.items[0] = item;
        this.sz++;
    }

    private class QueueIterator implements Iterator<T> {
        private int index = 0;

        public boolean hasNext() {
            return this.index < QueueArray.this.sz;
        }

        public T next() {
            return QueueArray.this.items[this.index++];
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public static void main(String[] args) {
        QueueArray<Integer> queue = new QueueArray();
        assert queue.size() == 0;
        assert queue.isEmpty();

        Iterator<Integer> it = queue.iterator();
        assert !it.hasNext();

        queue.enqueue(0);
        assert queue.size() == 1;
        assert !queue.isEmpty();

        assert queue.dequeue() == 0;
        assert queue.size() == 0;
        assert queue.isEmpty();

        queue.enqueue(0);
        queue.enqueue(1);
        queue.enqueue(2);
        assert queue.size() == 3;
        assert !queue.isEmpty();
        assert queue.dequeue() == 0;
        assert queue.dequeue() == 1;
        assert queue.dequeue() == 2;
        assert queue.size() == 0;
        assert queue.isEmpty();

        // Should trigger resize()
        queue = new QueueArray();
        for (int i = 0; i < 11; i++) {
            queue.enqueue(i);
        }
        assert queue.size() == 11;
        assert !queue.isEmpty();
        for (int i = 0; i < 11; i++) {
            assert queue.dequeue() == i;
        }
    }
}

