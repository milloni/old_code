import java.util.List;
import java.util.ArrayList;

// n - number of vertices
// m - number of edges
public class Digraph {
    private int n = 0;
    private int m = 0;
    private List<Integer>[] adj;

    public Digraph(int n) {
        if (n == 0) {
            throw new IllegalArgumentException("n can't be 0");
        }
        
        this.n = n;
        this.m = 0;
        this.adj = (List<Integer>[]) new List<?>[this.n];
        for (int i = 0; i < this.adj.length; i++) {
            this.adj[i] = new ArrayList<Integer>();
        }
    }

    public int getn() {
        return this.n;
    }

    public int getm() {
        return this.m;
    }

    public void addEdge(int v, int w) {
        assert this.adj[v] != null;
        assert this.adj[w] != null;
        this.adj[v].add(w);
        this.m++;
    }

    public List<Integer> adj(int v) {
        return this.adj[v];
    }

    public static void main(String[] args) { 
        Digraph g = new Digraph(10);
        assert g.getn() == 10;
        assert g.getm() == 0;
        g.addEdge(0, 1);
        assert g.adj(0).contains(1);
        assert !g.adj(0).contains(0);
        assert !g.adj(1).contains(0);
        assert !g.adj(1).contains(1);
        assert !g.adj(0).contains(2);
        assert g.getm() == 1;
    }
}

