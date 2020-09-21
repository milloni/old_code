import java.util.Queue;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Deque;
import java.util.Iterator;

public class BfsShortestPath {
    public static final int INFINITY = 1 << 30;

    private Graph g;
    private int s;
    private boolean[] marked;
    private int[] prevEdge;
    private int[] pathLen;

    public BfsShortestPath(Graph g, int s) {
        this.g = g;
        this.s = s;
        this.marked = new boolean[g.getn()];
        this.prevEdge = new int[g.getn()];
        this.pathLen = new int[g.getn()];
        Arrays.fill(this.pathLen, INFINITY);
        this.pathLen[s] = 0;
        this.prevEdge[s] = s;
        bfs(s);
    }

    public boolean hasPathTo(int v) {
        return this.marked[v];
    }

    public Iterable<Integer> pathTo(int v) {
        Deque<Integer> stack = new LinkedList<Integer>();
        while (v != this.s) {
            stack.addFirst(v);
            v = this.prevEdge[v];
        }
        return stack;
    }

    public int pathLength(int v) {
        return this.pathLen[v];
    }

    private void bfs(int v) {
       this.marked[v] = true;
       Queue<Integer> q = new LinkedList<Integer>();
       q.add(v);
       while (!q.isEmpty()) {
           int u = q.poll();
           for (int w : this.g.adj(u)) {
               if (!this.marked[w]) {
                   q.add(w);
                   this.marked[w] = true;
                   this.prevEdge[w] = u;
                   this.pathLen[w] = this.pathLen[u] + 1;
               }
           }
       }
       
    }

    private static void testTinyCG(Graph g) {
        BfsShortestPath sp = new BfsShortestPath(g, 0);
        assert sp.pathLength(0) == 0;
        Iterator<Integer> it = sp.pathTo(0).iterator();
        assert !it.hasNext();

        assert sp.pathLength(1) == 1;
        it = sp.pathTo(1).iterator();
        assert it.next() == 1;
        assert !it.hasNext();
        
        assert sp.pathLength(2) == 1;
        it = sp.pathTo(2).iterator();
        assert it.next() == 2;
        assert !it.hasNext();

        assert sp.pathLength(3) == 2;
        it = sp.pathTo(3).iterator();
        int a = it.next();
        assert a == 2 || a == 5;
        assert it.next() == 3;
        assert !it.hasNext();

        assert sp.pathLength(4) == 2;
        it = sp.pathTo(4).iterator();
        assert it.next() == 2;
        assert it.next() == 4;
        assert !it.hasNext();
    }

    public static void main(String[] args) {
        Scanner stdin = new Scanner(new BufferedInputStream(System.in));
        int n = stdin.nextInt();
        int m = stdin.nextInt();
        Graph g = new Graph(n);
        for (int i = 0; i < m; i++) {
            int v = stdin.nextInt();
            int w = stdin.nextInt();
            g.addEdge(v, w);
        }

        testTinyCG(g);
    }
}

