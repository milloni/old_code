import java.util.Iterator;

public class QueueLinkedList<T> implements Iterable<T> {
    private int sz = 0;
    private Node first = null;
    private Node last = null;
    
    public void enqueue(T item) {
        assert (this.first == null) == (this.last == null);
        
        Node n = new Node();
        n.item = item;
        n.next = null;
        if (this.last == null) {
            this.first = n;
        } else {
            this.last.next = n;
        }
        this.last = n;
        this.sz++;
    }

    public T dequeue() {
        Node oldfirst = this.first;
        if (this.first.next != null) {
            this.first = this.first.next;
        } else {
            this.first = this.last = null;
        }
        this.sz--;
        return oldfirst.item;
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    public int size() {
        return this.sz;
    }

    @Override
    public Iterator<T> iterator() {
        return new QueueIterator();
    }

    private class QueueIterator implements Iterator<T> {
        private Node current = QueueLinkedList.this.first;

        @Override
        public boolean hasNext() {
            return this.current != null;
        }

        @Override
        public T next() {
            Node old = this.current;
            this.current = (this.current == QueueLinkedList.this.last) ?
                (null) : (this.current.next);
            return old.item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    private class Node {
        T    item;
        Node next;
    }

    public static void main(String[] args) {
        QueueLinkedList<Integer> queue = new QueueLinkedList<>();
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

        queue = new QueueLinkedList<>();
        for (int i = 0; i < 5; i++) {
            queue.enqueue(i);
            assert queue.size() == i + 1;
            assert !queue.isEmpty();
        }
        it = queue.iterator();
        for (int i = 0; i < 4; i++) {
            assert it.hasNext();
            assert it.next() == i;
        }
        for (int i = 4; i >= 0; i--) {
            assert queue.size() == i + 1;
            assert !queue.isEmpty();
            assert queue.dequeue() == 4 - i;
        }
    }
}

