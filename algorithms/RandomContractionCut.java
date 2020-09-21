import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class RandomContractionCut {
    private int             n;
    private int             m;
    private List<Integer>[] adjacent;
    private int[]           id;
    private Cut             cut;

    public RandomContractionCut(InputStream is) {
        Scanner sc = new Scanner(is);
        this.m = 0;
        this.n = sc.nextInt();
        sc.nextLine();

        this.id = new int[this.n];
        for (int i = 0; i < this.id.length; i++) this.id[i] = i;
        this.adjacent = (List<Integer>[]) new List<?>[this.n];
        for (int i = 0; i < this.adjacent.length; i++) {
            this.adjacent[i] = new LinkedList<Integer>();
        }

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            Scanner lsc =
                new Scanner(new ByteArrayInputStream(line.getBytes()));
            int v = lsc.nextInt() - 1;
            while (lsc.hasNextInt()) {
                int w = lsc.nextInt() - 1;
                if (!edgeExists(v, w)) addEdge(v, w);
            }
        }
    }

    public int getn() {
        return this.n;
    }

    public int getm() {
        return this.m;
    }

    public Cut getCut() {
        if (this.cut == null) {
            throw new IllegalStateException("First call init()");
        }

        return this.cut;
    }

    public void init() {
        Random r = new Random();
        for (int i = this.n; i > 2; i--) {
            Edge eContr = getRandomEdge(r);
            contract(eContr);
        }

        List<Integer> a = new LinkedList<Integer>();
        List<Integer> b = new LinkedList<Integer>();
        int oneId = this.id[0];
        for (int i = 0; i < this.id.length; i++) {
            if (this.id[i] == oneId) a.add(i);
            else                     b.add(i);
        }

        int size = 0;
        for (int i = 0; i < this.n; i++) {
            if (!this.adjacent[i].isEmpty()) {
                size = this.adjacent[i].size();
                break;
            }
        }

        this.cut = new Cut(a, b, size);
    }

    public RandomContractionCut copyOf() {
        if (this.cut != null) {
            throw new IllegalStateException("This must be called before init");
        }

        return new RandomContractionCut(this);
    }

    private RandomContractionCut(RandomContractionCut that) {
        this.n = that.n;
        this.m = that.m;
        this.adjacent = (List<Integer>[]) new List<?>[that.n];
        for (int i = 0; i < this.adjacent.length; i++) {
            this.adjacent[i] = new LinkedList<Integer>(that.adjacent[i]);
        }
        this.id = new int[that.n];
        for (int i = 0; i < this.id.length; i++) this.id[i] = i;
    }

    private void contract(Edge e) {
        int v = e.v;
        int w = e.w;

        removeParallelEdges(v, w);
        List<Integer> wadj =                           // To avoid ConcurrentModificationException
            new LinkedList<Integer>(this.adjacent[w]); // how bad can this be anyway?
        for (int x : wadj) {
            removeEdge(w, x);
            addEdge(v, x);
        }
        assert this.adjacent[w].isEmpty();

        int vId = this.id[v];
        int wId = this.id[w];
        for (int i = 0; i < this.id.length; i++) {
            if (this.id[i] == wId) this.id[i] = vId;
        }
    }

    private Edge getRandomEdge(Random r) {
        int v = r.nextInt(this.n);
        while (this.adjacent[v].isEmpty()) v = r.nextInt(this.n);
        int wIdx = r.nextInt(this.adjacent[v].size());
        int w = this.adjacent[v].get(wIdx);

        return new Edge(v, w);
    }

    private void removeEdge(int v, int w) {
        this.adjacent[v].remove(Integer.valueOf(w));
        this.adjacent[w].remove(Integer.valueOf(v));
        this.m--;
    }

    private void removeParallelEdges(int v, int w) {
        int fcount = 0;
        int scount = 0;
        while (this.adjacent[v].remove(Integer.valueOf(w))) fcount++;
        while (this.adjacent[w].remove(Integer.valueOf(v))) scount++;
        assert fcount == scount;
        this.m -= fcount;
    }

    private void addEdge(int v, int w) {
        this.adjacent[v].add(w);
        this.adjacent[w].add(v);
        this.m++;
    }

    private boolean edgeExists(int v, int w) {
        boolean b = this.adjacent[v].contains(w);
        assert b == this.adjacent[w].contains(v);
        return b;
    }

    public static class Edge {
        private int v;
        private int w;

        public Edge(int v, int w) { this.v = v; this.w = w; }

        public String toString() {
            return String.format("%d-%d", this.v, this.w);
        }
    }

    public static class Cut {
        private List<Integer> a;
        private List<Integer> b;
        private int           size;

        public Cut(List<Integer> a, List<Integer> b, int size) {
            this.a = new ArrayList<Integer>(a);
            this.b = new ArrayList<Integer>(b);
            this.size = size;
        }

        public List<Integer> getA() {
            return Collections.unmodifiableList(this.a);
        }

        public List<Integer> getB() {
            return Collections.unmodifiableList(this.b);
        }

        public int getSize() {
            return this.size;
        }

        public String toString() {
            return String.format("(%s, %s)", this.a, this.b);
        }
    }

    public static void main(String[] args) {
        RandomContractionCut cut = new RandomContractionCut(
            new BufferedInputStream(System.in));
        cut.init();
        System.out.println("Cut: " + cut.getCut());
        System.out.println("Cut length: " + cut.getCut().getSize());
    }
}

