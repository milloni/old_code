import java.util.Queue;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Deque;
import java.util.Iterator;

public class UndirectedConnectivity {
    private Graph g;
    private boolean[] marked;
    private int[] id;
    private int c;
    
    public UndirectedConnectivity(Graph g) {
        this.g = g;
        this.marked = new boolean[g.getn()];
        this.id = new int[g.getn()];
        this.c = 0;

        for (int i = 0; i < g.getn(); i++) {
            if (!this.marked[i]) {
                dfs(i);
            }
        }
    }

    public boolean connected(int v, int w) {
        return this.id(v) == this.id(w);
    }

    public int count() {
        return this.c;
    }

    public int id(int v) {
        return this.id[v];
    }

    private void dfs(int s) {
        doDfs(s);
        this.c++;
    }

    private void doDfs(int s) {
        this.marked[s] = true;
        this.id[s] = this.c;
        System.out.println(s + " " + this.id[s]);
        for (int w : g.adj(s)) {
            if (!this.marked[w]) {
                doDfs(w);
            }
        }
    }

    private static void testTinyG(Graph g) {
        // tinyG.txt
        // Components:
        // [0, 1, 2, 3, 4, 5, 6]
        // [7, 8]
        // [9, 10, 11, 12]
        UndirectedConnectivity uc = new UndirectedConnectivity(g);
        int id = uc.id(0);
        for (int i = 0; i < 7; i++) {
            assert uc.id(i) == id;
        }
        id = uc.id(7);
        for (int i = 7; i < 9; i++) {
            assert uc.id(i) == id;
        }
        id = uc.id(9);
        for (int i = 9; i < 13; i++) {
            assert uc.id(i) == id;
        }
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
        
        testTinyG(g);
    }
}

