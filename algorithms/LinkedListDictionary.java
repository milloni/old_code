import java.util.Queue;
import java.util.LinkedList;
import java.util.Iterator;

public class LinkedListDictionary<K extends Comparable<K>, V> {
    private int  sz;
    private Node first;

    public LinkedListDictionary() {
        this.sz = 0;
        this.first = null;
    }

    public void put(K key, V val) {
        Node n = new Node();
        n.next = null;
        n.key = key;
        n.val = val;
        if (this.first == null) {
            this.first = n;
        } else {
            Node c = this.first;
            Node p = null;
            while (c != null) {
                if (c.key.equals(key)) {
                    c.val = val;
                    return;
                }
                p = c;
                c = c.next;
            }
            p.next = n;
        }
        this.sz++;
    }

    public V get(K key) {
        Node c = this.first;
        while (c != null) {
            if (c.key.equals(key)) {
                return c.val;
            }
            c = c.next;
        }

        return null;
    }

    public void delete(K key) {
        Node p = null;
        Node c = this.first;
        while (c != null) {
            if (c.key.equals(key)) {
               if (p == null) {
                   this.first = c.next;
               } else {
                   p.next = c.next;
               }
               this.sz--;
            }
            p = c;
            c = c.next;
        }
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    public int size() {
        return this.sz;
    }

    public Iterable<K> keys() {
        Queue<K> q = new LinkedList<K>();
        Node c = this.first;
        while (c != null) {
            q.add(c.key);
            c = c.next;
        }

        return q;
    }

    public Iterable<V> values() {
        Queue<V> q = new LinkedList<V>();
        Node c = this.first;
        while (c != null) {
            q.add(c.val);
            c = c.next;
        }

        return q;
    }

    public static void main(String[] args) {
        LinkedListDictionary<String, Integer> dict =
            new LinkedListDictionary<>();
        assert dict.size() == 0;
        assert dict.isEmpty();
        dict.put("a", 1337);
        assert dict.size() == 1;
        assert !dict.isEmpty();
        assert dict.get("a") == 1337;
        dict.put("b", 420);
        assert dict.size() == 2;
        assert dict.get("b") == 420;
        assert dict.get("a") == 1337;
        dict.put("c", 123);
        dict.put("d", 987);
        assert dict.size() == 4;
        assert dict.get("c") == 123;
        assert dict.get("a") == 1337;
        dict.delete("c");
        assert dict.size() == 3;
        assert dict.get("c") == null;
        assert dict.get("a") == 1337;
        assert dict.get("b") == 420;
        Iterable<Integer> values = dict.values();
        Iterator<Integer> vit = values.iterator();
        assert vit.next() == 1337;
        assert vit.next() == 420;
        assert vit.next() == 987;
        assert !vit.hasNext();
        Iterable<String> keys = dict.keys();
        Iterator<String> kit = keys.iterator();
        assert kit.next() == "a";
        assert kit.next() == "b";
        assert kit.next() == "d";
        assert !kit.hasNext();
        dict.put("a", 1);
        assert dict.size() == 3;
        assert dict.get("a") == 1;
    }

    private class Node {
        Node next;
        K    key;
        V    val;
    }
}

