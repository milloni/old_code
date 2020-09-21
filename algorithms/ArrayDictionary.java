public class ArrayDictionary<K, V> {
    private static final int INIT_SIZE = 16;

    private int sz;
    private Entry[] entries;

    public ArrayDictionary() {
        this(16);
    }

    public ArrayDictionary(int initSize) {
        this.sz = 0;
        this.entries = new Entry[initSize];
    }

    public int size() {
        return this.sz;
    }

    public V get(K k) {
        
    }

    public void put(K k, V v) {

    }

    public int rank(K k) {

    }

    public void delete(K k) {

    }

    public Iterable<K> keys(K lo, K hi) {

    }

    public K min() {

    }

    public K max() {

    }

    public Key select(int i) {

    }

    public Key ceil(K k) {

    }

    public Key floor(K k) {

    }

    private class Entry {
        K key;
        V val;
    }

    public static void main(String[] args) {

    }
}

