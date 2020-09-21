import java.util.Iterator;

public class Deque<T> implements Iterable<T> {
    private int sz = 0;
    private Node first = null;
    private Node last = null;

    public boolean isEmpty() {
        return this.size() == 0;
    }

    public int size() {
        return this.sz;
    }

    public void pushLeft(T item) {
        assert (this.first == null) == (this.last == null);

        Node n = new Node();
        n.item = item;
        n.prev = null;
        if (this.first == null) {
            this.last = n;
        } else {
            n.next = this.first;
            n.next.prev = n;
        }
        this.first = n;
        this.sz++;
    }

    public void pushRight(T item) {
        assert (this.first == null) == (this.last == null);

        Node n = new Node();
        n.item = item;
        n.next = null;
        if (this.last == null) {
            this.first = n;
        } else {
            n.prev = this.last;
            n.prev.next = n;
        }
        this.last = n;
        this.sz++;
    }

    public T popLeft() {
        T v = this.first.item;
        this.first = this.first.next;
        if (this.first == null) {
            this.last = null;
        } else {
            this.first.prev = null;
        }
        this.sz--;
        return v;
    }

    public T popRight() {
        T v = this.last.item;
        this.last = this.last.prev;
        if (this.last == null) {
            this.first = null;
        } else {
            this.last.next = null;
        }
        this.sz--;
        return v;
    }

    @Override
    public Iterator<T> iterator() {
        return new DequeIterator();
    }

    private class Node {
        T    item;
        Node prev;
        Node next;
    }

    private class DequeIterator implements Iterator<T> {
        Node current = Deque.this.first;

        @Override
        public boolean hasNext() {
            return this.current != null;
        }

        @Override
        public T next() {
            T v = this.current.item;
            this.current = this.current.next;
            return v;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException("Oops, I did it again");
        }
    }

    public static void main(String[] args) {
        Deque<Integer> d = new Deque<>();
        assert d.size() == 0;
        assert d.isEmpty();
        Iterator<Integer> it = d.iterator();
        assert !it.hasNext();
        
        // Left stack
        d.pushLeft(0);
        assert d.size() == 1;
        assert !d.isEmpty();
        it = d.iterator();
        assert it.hasNext();
        assert it.next() == 0;
        assert !it.hasNext();
        assert d.popLeft() == 0;
        assert d.size() == 0;
        assert d.isEmpty();

        d.pushLeft(0);
        assert d.size() == 1;
        d.pushLeft(1);
        assert d.size() == 2;
        d.pushLeft(2);
        assert d.size() == 3;
        assert !d.isEmpty();
        it = d.iterator();
        assert it.hasNext();
        assert it.next() == 2;
        assert it.hasNext();
        assert it.next() == 1;
        assert it.hasNext();
        assert it.next() == 0;
        assert !it.hasNext();
        assert d.popLeft() == 2;
        assert d.size() == 2;
        assert d.popLeft() == 1;
        assert d.size() == 1;
        assert d.popLeft() == 0;
        assert d.size() == 0;
        assert d.isEmpty();

        // Right stack
        d.pushRight(0);
        assert d.size() == 1;
        assert !d.isEmpty();
        it = d.iterator();
        assert it.hasNext();
        assert it.next() == 0;
        assert !it.hasNext();
        assert d.popRight() == 0;
        assert d.size() == 0;
        assert d.isEmpty();

        d.pushRight(0);
        assert d.size() == 1;
        d.pushRight(1);
        assert d.size() == 2;
        d.pushRight(2);
        assert d.size() == 3;
        assert !d.isEmpty();
        it = d.iterator();
        assert it.hasNext();
        assert it.next() == 0;
        assert it.hasNext();
        assert it.next() == 1;
        assert it.hasNext();
        assert it.next() == 2;
        assert !it.hasNext();
        assert d.popRight() == 2;
        assert d.size() == 2;
        assert d.popRight() == 1;
        assert d.size() == 1;
        assert d.popRight() == 0;
        assert d.size() == 0;
        assert d.isEmpty();

        // Combined
        d.pushLeft(0);
        d.pushRight(1);
        d.pushLeft(2);
        d.pushRight(3);
        assert d.size() == 4;
        assert d.popRight() == 3;
        assert d.popLeft() == 2;
        assert d.popLeft() == 0;
        assert d.popLeft() == 1;
        assert d.size() == 0;
        assert d.isEmpty();

        System.out.println("All tests passed!");
    }
}



