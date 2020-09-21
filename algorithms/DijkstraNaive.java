import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Set;
import java.util.HashSet;
import java.util.Queue;
import java.util.Iterator;
import java.util.Scanner;
import java.io.BufferedInputStream;

public class DijkstraNaive {
    private WeightedDigraph             g;
    private int                         s;
    private double[]                    distanceTo;
    private WeightedDigraph.Edge[]      edgeTo;
    private Queue<WeightedDigraph.Edge> edges;

    public DijkstraNaive(WeightedDigraph g, int s) {
        if (s >= g.getn()) {
            throw new IllegalArgumentException(
                "Source vertex index can't be greater than graph's" +
                "number of vertices"
            );
        }

        this.g = g;
        this.s = s;
        this.distanceTo = new double[g.getn()];
        Arrays.fill(this.distanceTo, Double.POSITIVE_INFINITY);
        this.distanceTo[s] = 0;
        this.edgeTo = new WeightedDigraph.Edge[g.getn()];
        this.edges = new LinkedList<WeightedDigraph.Edge>(); 

        computePaths();
    }

    public double distTo(int v) {
        return this.distanceTo[v];
    }

    public boolean hasPathTo(int v) {
        return this.distanceTo[v] != Double.POSITIVE_INFINITY;
    }

    public Iterable<WeightedDigraph.Edge> pathTo(int v) {
        Deque<WeightedDigraph.Edge> stack =
            new LinkedList<WeightedDigraph.Edge>();
        WeightedDigraph.Edge e = this.edgeTo[v];
        while (e != null) {
            stack.addFirst(e);
            e = this.edgeTo[e.from()];
        }

        return stack;
    }

    private void computePaths() {
        addEdgesFrom(this.s);
        while (!this.edges.isEmpty()) {
            WeightedDigraph.Edge best = extractBest();
            relax(best);
            addEdgesFrom(best.to());
            //System.out.println(this.edges + " " + best);
        }
    }

    private void addEdgesFrom(int v) {
        for (WeightedDigraph.Edge e : this.g.adj(v)) {
            if (!marked(e.to())) this.edges.add(e);
        }
    }

    private WeightedDigraph.Edge extractBest() {
        WeightedDigraph.Edge best = this.edges.peek();
        for (WeightedDigraph.Edge e : this.edges) {
            if (this.distanceTo[e.from()] + e.weight() <
                this.distanceTo[best.from()] + best.weight())
            {
                best = e;
            }
        }

        int w = best.to();
        Iterator<WeightedDigraph.Edge> it = this.edges.iterator();
        while (it.hasNext()) {
            WeightedDigraph.Edge e = it.next();
            if (e.to() == w) it.remove();
        }

        return best;
    }

    private void relax(WeightedDigraph.Edge e) {
        int v = e.from();
        int w = e.to();
        this.distanceTo[w] = this.distanceTo[v] + e.weight();
        this.edgeTo[w] = e;
    }

    private boolean marked(int v) {
        return this.distanceTo[v] != Double.POSITIVE_INFINITY;
    }

    // tinyEWD.txt
    private static void testTinyEwd(WeightedDigraph g) {
        DijkstraNaive dijkstra = new DijkstraNaive(g, 0);
        
    }

    public static void main(String[] args) {
        Scanner stdin = new Scanner(new BufferedInputStream(System.in));
        int n = stdin.nextInt();
        int m = stdin.nextInt();
        WeightedDigraph g = new WeightedDigraph(n);
        for (int i = 0; i < m; i++) {
            int v = stdin.nextInt();
            int w = stdin.nextInt();
            double weight = stdin.nextDouble();
            WeightedDigraph.Edge e = new WeightedDigraph.Edge(v, w, weight);
            g.addEdge(e);
        }
        
        //testTinyEwd(g);

        DijkstraNaive dijkstra = new DijkstraNaive(g, 0);
        for (int i = 0; i < g.getn(); i++) {
            System.out.format("%d: [%.2f] ", i, dijkstra.distTo(i));
            System.out.println(dijkstra.pathTo(i));
        }
    }
}




