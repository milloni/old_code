import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;

// n - number of vertices
// m - number of edges
public class WeightedGraph {
    private int n;
    private List<WeightedEdge>[] adjacent;
    private List<WeightedEdge> edges;

    public WeightedGraph(int n) {
        if (n < 1) {
            throw new IllegalArgumentException(
                "Number of vertices must be at least one"
            );
        }

        this.n = n;
        this.adjacent = (List<WeightedEdge>[]) new LinkedList<?>[this.n];
        for (int i = 0; i < this.adjacent.length; i++) {
            this.adjacent[i] = new LinkedList<WeightedEdge>();
        }
        this.edges = new ArrayList<WeightedEdge>(20 * this.n);
    }

    public int getn() {
        return this.n;
    }

    public int getm() {
        return this.edges.size();
    }

    public List<WeightedEdge> adj(int v) {
        return Collections.unmodifiableList(this.adjacent[v]);
    }

    public List<WeightedEdge> edges() {
        return Collections.unmodifiableList(this.edges);
    }

    public void addEdge(WeightedEdge e) {
        int v = e.from();
        int w = e.to();
        this.adjacent[v].add(e);
        this.adjacent[w].add(e);
        this.edges.add(e);
    }
}

