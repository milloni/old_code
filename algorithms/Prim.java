import java.io.InputStream;
import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.List;
import java.util.LinkedList;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Arrays;
import java.util.Deque;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Iterator;

public class Prim {
    private WeightedGraph d_graph;
    private WeightedGraph d_mst;

    private boolean[] marked;
    private List<WeightedEdge> edges;

    private void _d(String msg) {
        System.out.println("Log: " + msg);
    }

    private boolean edgePasses(WeightedEdge e, int vertex) {
        return e.to() == vertex || e.from() == vertex;
    }
    
    private boolean edgeConnects(WeightedEdge e, int v, int w) {
        return (e.to() == v && e.from() == w)
            || (e.to() == w && e.from() == v);
    }

    public Prim(InputStream in) {
        _d("Prim.Prim()");
        buildGraph(in);
        computeMst();
    }

    private void addVertex(int v) {
        for (WeightedEdge e : d_graph.adj(v)) {
            if (!marked[e.to()]) {
                edges.add(e);
            }
        }
        marked[v] = true;

        Iterator<WeightedEdge> it = edges.iterator();
        while (it.hasNext()) {
            WeightedEdge e = it.next();
            if (marked[e.to()] && marked[e.from()]) {
                it.remove();
            }
        }
    }

    public double sumCost() {
        double result = 0;
        for (WeightedEdge e : d_mst.edges()) {
            result += e.weight();
        }
        return result;
    }

    public void computeMst() {
        _d("Prim.computeMst()");
        int n = d_graph.getn();
        d_mst = new WeightedGraph(n);

        addVertex(0);
        while (!edges.isEmpty()) {
            WeightedEdge eMin = edges.get(0);
            for (WeightedEdge e : edges) {
                if (e.weight() < eMin.weight()) {
                    eMin = e;
                }
            }

            int v = marked[eMin.from()] ? eMin.from() : eMin.to();
            int w = (eMin.from() == v) ? eMin.to() : eMin.from();
            d_mst.addEdge(eMin);
            addVertex(w);
        }

        /*List<WeightedEdge> edgesLeft =
            new LinkedList<WeightedEdge>(d_graph.edges());
        int v = 0;
        while (!edgesLeft.isEmpty()) {
            WeightedEdge eMin = edgesLeft.get(0);
            for (WeightedEdge e : edgesLeft) {
                //_d("!!");
                if (e.weight() < eMin.weight()) {
                    eMin = e;
                }
            }
            int w = (v == eMin.from()) ? eMin.to() : eMin.from();
            Iterator<WeightedEdge> it = edgesLeft.iterator();
            while (it.hasNext()) {
                WeightedEdge e = it.next();
                for (int i = 0; 
                if (edgeConnects(e, v, w)) {
                    it.remove();
                }
            }
            _d(String.format("Prim.computeMst(): added vertex %d", w));*/
        //}
    }

    public WeightedGraph getMst() {
        return d_mst;
    }

    public void buildGraph(InputStream in) {
        _d("Prim.buildGraph()");
        Scanner sc = new Scanner(in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        d_graph = new WeightedGraph(n);
        for (int i = 0; i < m; i++) {
            int v = sc.nextInt() - 1;
            int w = sc.nextInt() - 1;
            double weight = sc.nextDouble();
            WeightedEdge e = new WeightedEdge(v, w, weight);
            d_graph.addEdge(e);
        }

        marked = new boolean[n];
        edges = new LinkedList<WeightedEdge>();
    }

    public static void main(String[] args) {
        Prim prim = new Prim(new BufferedInputStream(System.in));
        //WeightedGraph mst = prim.getMst();
        //for (WeightedEdge e : mst.edges()) {
        //    System.out.println(e);
        //}
        double sum = prim.sumCost();
        System.out.println(sum);
    }
}
