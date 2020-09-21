import java.util.Queue;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.IOException;

public class BreadthFirstSearch {
    private Graph g;
    private int s;
    private boolean[] marked;

    public BreadthFirstSearch(Graph g, int s) {
        this.g = g;
        this.s = s;
        this.marked = new boolean[g.getn()];
        bfs(s);
    }

    public boolean connected(int v) {
        return this.marked[v];
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
                }
            }
        }
    }

    private static void testTinyG(Graph g) {
        // tinyG.txt with s == 0
        // [0, 1, 2, 3, 4, 5, 6]
        BreadthFirstSearch bfs = new BreadthFirstSearch(g, 0);
        assert bfs.connected(0);
        assert bfs.connected(1);
        assert bfs.connected(2);
        assert bfs.connected(3);
        assert bfs.connected(4);
        assert bfs.connected(5);
        assert bfs.connected(6);
        assert !bfs.connected(7);
        assert !bfs.connected(8);
        assert !bfs.connected(9);
        assert !bfs.connected(10);
        assert !bfs.connected(11);
        assert !bfs.connected(12);

        // tinyG.txt with s == 7
        // [7, 8]
        bfs = new BreadthFirstSearch(g, 7);
        assert !bfs.connected(0);
        assert !bfs.connected(1);
        assert !bfs.connected(2);
        assert !bfs.connected(3);
        assert !bfs.connected(4);
        assert !bfs.connected(5);
        assert !bfs.connected(6);
        assert bfs.connected(7);
        assert bfs.connected(8);
        assert !bfs.connected(9);
        assert !bfs.connected(10);
        assert !bfs.connected(11);
        assert !bfs.connected(12);

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

