import java.util.Arrays;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.util.List;
import java.util.ArrayList;

public class TopologicalSort {
    private Digraph dag;
    private boolean[] marked;
    private int[] order;
    private int current;

    public TopologicalSort(Digraph dag) {
        this.dag = dag;
        this.marked = new boolean[dag.getn()];
        this.order = new int[dag.getn()];
        Arrays.fill(this.order, -1);
        this.current = dag.getn() - 1;

        for (int i = 0; i < dag.getn(); i++) {
            if (!this.marked[i]) {
                dfs(i);
            }
        }
    }

    public int getOrder(int i) {
        return this.order[i];
    }

    private void dfs(int s) {
        this.marked[s] = true;
        for (int v : this.dag.adj(s)) {
            if (!this.marked[v]) {
                dfs(v);
            }
        }
        this.order[this.current--] = s;
    }

    private static void testConstraints(Digraph dag) {
        TopologicalSort ts = new TopologicalSort(dag);
        for (int i = 0; i < dag.getn(); i++) {
            System.out.print(ts.getOrder(i) + " ");
        }
        System.out.println(); 
    }

    public static void main(String[] args) {
        Scanner stdin = new Scanner(new BufferedInputStream(System.in));
        int n = stdin.nextInt();
        int m = stdin.nextInt();
        Digraph dag = new Digraph(n);
        for (int i = 0; i < m; i++) {
            int v = stdin.nextInt();
            int w = stdin.nextInt();
            dag.addEdge(v, w);
        }

        testConstraints(dag);
    }
}

