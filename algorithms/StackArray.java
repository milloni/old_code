import java.util.Iterator;

public class StackArray<T> implements Iterable<T> {
    private static final int INIT_SIZE = 10;

    private int sz = 0;
    private T[] items = (T[]) new Object[INIT_SIZE];

    public void push(T item) {
        if (this.size() >= this.items.length) {
            resize(2 * this.size());
        }
        this.items[this.sz++] = item;
    }

    public T pop() {
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

    @Override
    public Iterator<T> iterator() {
        return new StackIterator();
    }

    private void resize(int newsz) {
        assert newsz > this.items.length;
        T[] t = (T[]) new Object[newsz];
        for (int i = 0; i < this.size(); i++) {
            t[i] = this.items[i];
        }
        this.items = t;
    }

    private class StackIterator implements Iterator<T> {
        private int index = StackArray.this.size() - 1;
        
        @Override
        public boolean hasNext() {
            return this.index >= 0;
        }

        @Override
        public T next() {
            return StackArray.this.items[this.index--];
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("Sucks having to" +
                "implement all those methods :/");
        }
    }

    public static void main(String[] args) {
        StackArray<Integer> s = new StackArray<>();
        assert s.size() == 0;
        assert s.isEmpty();

        Iterator<Integer> it = s.iterator();
        assert !it.hasNext();

        s.push(0);
        assert s.size() == 1;
        assert !s.isEmpty();
        it = s.iterator();
        assert it.hasNext();
        assert it.next() == 0;
        assert !it.hasNext();
        assert s.pop() == 0;
        assert s.size() == 0;
        assert s.isEmpty();

        s.push(0);
        s.push(1);
        s.push(2);
        assert s.size() == 3;
        it = s.iterator();
        assert it.hasNext();
        assert it.next() == 2;
        assert it.hasNext();
        assert it.next() == 1;
        assert it.hasNext();
        assert it.next() == 0;
        assert !it.hasNext();
        assert s.pop() == 2;
        assert s.pop() == 1;
        assert s.pop() == 0;

        // Should trigger resize()
        for (int i = 0; i < INIT_SIZE + 1; i++) s.push(i);
        for (int i = INIT_SIZE; i >= 0;i --) assert s.pop() == i;
        System.out.println("All tests passed.");
    }
}

