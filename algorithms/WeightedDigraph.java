import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;

public class WeightedDigraph {
    private int          n;
    private List<Edge>[] adjacent;
    private List<Edge>   edges;

    public WeightedDigraph(int n) {
        if (n < 1) {
            throw new IllegalArgumentException(
                "Number of vertices must be at least one"
            );
        }

        this.n = n;
        this.adjacent = (List<Edge>[]) new LinkedList<?>[this.n];
        for (int i = 0; i < this.adjacent.length; i++) {
            this.adjacent[i] = new LinkedList<Edge>();
        }
        this.edges = new ArrayList<Edge>(20 * this.n);
    }

    public int getn() {
        return this.n;
    }

    public int getm() {
        return this.edges.size();
    }

    public List<Edge> adj(int v) {
        return Collections.unmodifiableList(this.adjacent[v]);
    }

    public List<Edge> edges() {
        return Collections.unmodifiableList(this.edges);
    }

    public void addEdge(Edge e) {
        int v = e.from();
        int w = e.to();
        this.adjacent[v].add(e);
        this.edges.add(e);
    }

    public static class Edge {
        private int    from;
        private int    to;
        private double weight;

        public Edge(int from, int to, double weight) {
            this.to = to;
            this.from = from;
            this.weight = weight;
        }

        @Override
        public boolean equals(Object that) {
            Edge _that = (Edge) that;
            return this.from == _that.from &&
                this.to == _that.to &&
                this.weight == _that.weight;
        }

        @Override
        public String toString() {
            return String.format("%d->%d (%f)", this.from,
                this.to, this.weight);
        }

        public int from() { return this.from; }
        public int to() { return this.to; }
        public double weight() { return this.weight; }
    }

    public static void main(String[] args) {

    }
}

