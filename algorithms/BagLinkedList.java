import java.util.Iterator;

public class BagLinkedList<T> implements Iterable<T> {
    private int  sz = 0;
    private Node first = null;
    private Node last = null;

    public void add(T item) {
        assert (this.first == null) == (this.last == null);

        this.sz++;
        Node n = new Node();
        n.item = item;
        n.next = null;
        if (this.first == null && this.last == null) {
            this.first = this.last = n;
        } else {
            this.last.next = n;
            this.last = n;
        }
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

    private class BagIterator implements Iterator<T> {
        private Node current = BagLinkedList.this.first;
        
        public boolean hasNext() {
            return this.current != null;
        }

        public T next() {
            Node old = this.current;
            this.current = (this.current == BagLinkedList.this.last) ?
                (null) : (this.current.next);
            return old.item;
        }

        public void remove() {
            throw new UnsupportedOperationException("oops");
        }
    }

    private class Node {
        T    item;
        Node next;
    }

    public static void main(String[] args) {
        BagLinkedList<Integer> bag = new BagLinkedList();
        assert bag.size() == 0;
        assert bag.isEmpty();

        Iterator<Integer> it = bag.iterator();
        assert !it.hasNext();

        bag.add(0);
        assert bag.size() == 1;
        assert !bag.isEmpty();

        it = bag.iterator();
        assert it.hasNext();
        assert it.next() == 0;
        
        bag.add(1);
        bag.add(2);
        assert bag.size() == 3;
        assert !bag.isEmpty();
        it = bag.iterator(); // [0, 1, 2]
        assert it.hasNext();
        assert it.next() == 0;
        assert it.hasNext();
        assert it.next() == 1;
        assert it.hasNext();
        assert it.next() == 2;
        assert !it.hasNext();
        assert bag.size() == 3;
        assert !bag.isEmpty();
    }
}

