import java.util.Iterator;


public class BagArray<T> implements Iterable<T> {
    private static final int INIT_SIZE = 10;

    private T[] items;
    private int sz;
    
    public BagArray() {
        this.items = (T[]) new Object[INIT_SIZE];
        this.sz = 0;
    }

    public void add(T item) {
        if (this.size() >= items.length) {
            resize(2 * items.length);
        }
        this.items[this.sz++] = item;
    }
    
    public boolean isEmpty() {
        return this.size() == 0;
    }

    public int size() {
        return this.sz;
    }

    public Iterator<T> iterator() {
        return new BagIterator();
    }

    private void resize(int newsz) {
        T[] t = (T[]) new Object[newsz];
        for (int i = 0; i < this.items.length; i++) {
            t[i] = this.items[i];
        }
        this.items = t;
    }

    private class BagIterator implements Iterator<T> {
        private int index = 0;

        public boolean hasNext() {
            return index < BagArray.this.size();
        }

        public T next() {
            return BagArray.this.items[index++];
        }

        public void remove() {
            throw new UnsupportedOperationException("oops");
        }
    }

    public static void main(String[] args) {
        BagArray<Integer> bag = new BagArray();
        assert bag.size() == 0;
        assert bag.isEmpty();
        
        for (int i = 0; i < INIT_SIZE; i++) {
            bag.add(i);
            assert bag.size() == i + 1;
        }

        for (Integer x : bag) {
            assert x != null;
        }

        // Should trigger resize()
        bag.add(420);
        assert bag.size() == 11;
        Iterator<Integer> it = bag.iterator();
        assert it.hasNext();
        assert it.next() == 0;
        for (int i = 0; i < bag.size() - 1; i++) it.next();
        assert !it.hasNext();
    }
}

