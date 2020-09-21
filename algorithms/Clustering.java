import java.io.InputStream;
import java.io.BufferedInputStream;
import java.util.Scanner;
import java.util.List;
import java.util.LinkedList;
import java.util.InputMismatchException;
import java.util.Arrays;
import java.util.Deque;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.BitSet

public class Clustering {
    private int numNodes;
    private int numEdges;
    private int numClusters;
    private double maxSpacing;
    private Edge[] edgesSorted;
    private int[] unionFind;
    private int[] unionSize;

    private void _d(String msg) {
        System.out.println("Log: " + msg);
    }

    private Clustering(InputStream in) {
        _d("Clustering.Clustering()");
        buildGraph(in);
        doClustering();
    }

    private void buildGraph(InputStream in) {
        _d("Clustering.buildGraph()");
        numClusters = 4; // NUMBER OF CLUSTERS
        Scanner sc = new Scanner(in);
        numNodes = sc.nextInt();
        numEdges = numNodes * (numNodes - 1) / 2;
        assert numNodes != 0;
        edgesSorted = new Edge[numEdges];
        unionFind = new int[numNodes];
        unionSize = new int[numNodes];
        assert unionFind.length == unionSize.length;
        for (int i = 0; i < unionFind.length; i++) {
            unionFind[i] = i;
            unionSize[i] = 1;
        }
        for (int i = 0; i < numEdges; i++) {
            int v = sc.nextInt() - 1;
            int w = sc.nextInt() - 1;
            double weight = sc.nextDouble();
            int index = (numNodes - 1) * v + w;
            edgesSorted[i] = new Edge(v, w, weight);
        }
        Arrays.sort(edgesSorted);
    }

    private void doClustering() {
        int curClusters = numNodes;
        for (Edge e : edgesSorted) {
            if (curClusters <= numClusters) {
                break;
            }
            int findV = unionFind[e.v];
            int findW = unionFind[e.w];
            if (findV == findW) {
                continue;
            } else {
                if(unionSize[e.v] > unionSize[e.w]) {
                    for (int i = 0; i < unionFind.length; i++) {
                        if (unionFind[i] == findV) {
                            unionFind[i] = findW;
                        }
                    }
                    unionFind[e.w] = unionFind[e.v];
                } else { // unionSize[e.v] <= unionSize[e.w]
                    for (int i = 0; i < unionFind.length; i++) {
                        if (unionFind[i] == findW) {
                            unionFind[i] = findV;
                        }
                    }
                }
                curClusters--;
            }
        }

        maxSpacing = Double.POSITIVE_INFINITY;
        for (Edge e : edgesSorted) {
            if (unionFind[e.v] != unionFind[e.w] && e.weight < maxSpacing) {
                maxSpacing = e.weight;
            }
        }
    }

    public double getMaxSpacing() {
        return maxSpacing;
    }

    public static void main(String[] args) {
        Clustering clustering =
            new Clustering(new BufferedInputStream(System.in));
        System.out.println(clustering.getMaxSpacing());
    }

    private static class Edge implements Comparable<Edge> {
        public int v;
        public int w;
        public double weight;
        
        public Edge(int v, int w, double weight) {
            this.v = v;
            this.w = w;
            this.weight = weight;
        }

        @Override
        public boolean equals(Object other) {
            if (this == other) {
                return true;
            }
            Edge otherEdge = (Edge) other;
            return weight == otherEdge.weight
                && (v == otherEdge.v || v == otherEdge.w)
                && (w == otherEdge.w || w == otherEdge.v);
        }

        @Override
        public int compareTo(Edge other) {
            if (this.equals(other)) {
                return 0;
            }
            if (weight < other.weight) {
                return -1;
            } else if (weight > other.weight) {
                return 1;
            } else { // weight == other.weight
                if (v < other.v) {
                    return -1;
                } else if (v > other.v) {
                    return 1;
                } else { // v == other.v
                    if (w < other.w) {
                        return -1;
                    } else if (w > other.w) {
                        return 1;
                    } else { // w == other.w
                        return 0;
                    }
                }
            }
        }
    }
};

