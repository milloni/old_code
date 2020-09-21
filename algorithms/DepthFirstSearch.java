import java.util.Queue;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.IOException;

public class DepthFirstSearch {
    private Graph g;
    private int s;
    private boolean[] marked;
    
    public DepthFirstSearch(Graph g, int s) {
        this.g = g;
        this.s = s;
        this.marked = new boolean[g.getn()];
        dfs(s);
    }

    public boolean connected(int v) {
        return this.marked[v];
    }

    private void dfs(int v) {
        this.marked[v] = true;
        for (int w : g.adj(v)) {
            if (!this.marked[w]) {
                dfs(w);
            }
        }
    }

    private static void testTinyG(Graph g) {
        // tinyG.txt with s == 0
        // [0, 1, 2, 3, 4, 5, 6]
        BreadthFirstSearch dfs = new BreadthFirstSearch(g, 0);
        assert dfs.connected(0);
        assert dfs.connected(1);
        assert dfs.connected(2);
        assert dfs.connected(3);
        assert dfs.connected(4);
        assert dfs.connected(5);
        assert dfs.connected(6);
        assert !dfs.connected(7);
        assert !dfs.connected(8);
        assert !dfs.connected(9);
        assert !dfs.connected(10);
        assert !dfs.connected(11);
        assert !dfs.connected(12);

        // tinyG.txt with s == 7
        // [7, 8]
        dfs = new BreadthFirstSearch(g, 7);
        assert !dfs.connected(0);
        assert !dfs.connected(1);
        assert !dfs.connected(2);
        assert !dfs.connected(3);
        assert !dfs.connected(4);
        assert !dfs.connected(5);
        assert !dfs.connected(6);
        assert dfs.connected(7);
        assert dfs.connected(8);
        assert !dfs.connected(9);
        assert !dfs.connected(10);
        assert !dfs.connected(11);
        assert !dfs.connected(12);
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

