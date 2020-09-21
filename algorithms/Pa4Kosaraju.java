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

// SCC.txt must be preprocessed to work with this class
// Add number of vertices in the first line
// and number of edges in the second
public class Pa4Kosaraju {
    private int n;
    private int m;
    private List<Integer>[] adj;
    private List<Integer>[] adjRev;
    private int[] processingOrder;
    private int current;
    private boolean[] marked;
    private int[] topFive = new int[5];
    public int[] group;

    private Deque<Integer> auxStack = new ArrayDeque<Integer>(1 << 25); // 32MB

    public Pa4Kosaraju(InputStream in) {
        buildGraph(in);
        computeProcessingOrder();
        findSccs();
    }

    public int[] getTopFive() {
        return this.topFive;
    }

    private void buildGraph(InputStream in) {
        _d("building the graph from input stream");
        try {
            Scanner sc = new Scanner(in);
            this.n = sc.nextInt();
            this.m = sc.nextInt();
            this.adj = (List<Integer>[]) new LinkedList<?>[this.n];
            this.adjRev = (List<Integer>[]) new LinkedList<?>[this.n];
            this.group = new int[this.n];
            this.current = n - 1;
            for (int i = 0; i < this.n; i++) {
                this.adj[i] = new LinkedList<Integer>();
                this.adjRev[i] = new LinkedList<Integer>();
            }
            this.processingOrder = new int[this.n];
            this.marked = new boolean[this.n];

            for (int i = 0; i < m; i++) {
                int v = sc.nextInt() - 1;
                int w = sc.nextInt() - 1;
                this.adj[v].add(w);
                this.adjRev[w].add(v);
            }

        } catch (IllegalStateException e) {
            _f("Input stream is closed!");
        } catch (InputMismatchException e) {
            _f("No more elements in the input stream!");
        } catch (NoSuchElementException e) {
            _f("Element of the input string is not of expected type!");
        } finally {
            // I'll probably remember something...
        }
    }

    private void computeProcessingOrder() {
        _d("computing processing order");
        Arrays.fill(this.marked, false);
        for (int i = this.n - 1; i >= 0; i--) {
            if (!this.marked[i]) {
                firstDfs(i);
            }
        }

        /*for (int i = 0; i < this.processingOrder.length; i++) {
            System.out.print(this.processingOrder[i] + " ");
        }
        System.out.println();*/
        //System.out.println(Arrays.asList(this.processingOrder));
    }

    private void findSccs() {
        _d("finding strongly connected components in the graph");
        Arrays.fill(this.marked, false);
        for (int i : this.processingOrder) {
            if (!this.marked[i]) {
                //System.out.println("!");
                secondDfs(i);
            }
        }
    }

    private void firstDfs(int s) {
        Deque<Integer> stack = this.auxStack;
        stack.clear();
        stack.addFirst(s);
        this.marked[s] = true;

        /*while (!stack.isEmpty()) {
            int v = stack.removeFirst();
            for (int w : this.adjRev[v]) {
                if (!this.marked[w]) {
                    stack.addFirst(w);
                    this.marked[w] = true;
                }
            }
        }*/

        while (!stack.isEmpty()) {
            int v = stack.peekFirst();
            //System.out.println("FirstDfs(): " + (v + 1) + " " + this.adjRev[v]);
            int w = findFirstNotMarked(this.adjRev[v]);
            if (w == -1) {
                stack.removeFirst();
                this.processingOrder[this.current--] = v;
            } else {
                stack.addFirst(w);
                this.marked[w] = true;
            }
        }
    }

    private int findFirstNotMarked(List<Integer> adj) {
        for (int v : adj) {
            if (!this.marked[v]) {
                return v;
            }
        }
        return -1;
    }

    private void secondDfs(int s) {
        Deque<Integer> stack = this.auxStack;
        stack.clear();
        stack.addFirst(s);
        this.marked[s] = true;

        int size = 1;

        while (!stack.isEmpty()) {
            int v = stack.peekFirst();
            //System.out.println("secondDfs(): " + v);
            int w = findFirstNotMarked(this.adj[v]);
            if (w == -1) {
                stack.removeFirst();
            } else {
                stack.addFirst(w);
                this.marked[w] = true;
                size++;
            }
        }
        insertTopFive(size);
        //_d((new Integer(size)).toString());
    }

    private void insertTopFive(int size) {
        if (size > this.topFive[4]) {
            this.topFive[4] = size;
        } else {
            return;
        }

        for (int i = 4; i >= 1; i--) {
            if (this.topFive[i] > this.topFive[i - 1]) {
                int t = this.topFive[i - 1];
                this.topFive[i - 1] = this.topFive[i];
                this.topFive[i] = t;
            }
        }
    }

    private void _f(String msg) {
        System.err.println(msg);
        System.exit(1);
    }

    private void _d(String msg) {
        System.out.println("Log: " + msg);
    }

    private static void printTopFive(Pa4Kosaraju k) {
        int[] t = k.getTopFive();
        System.out.print("[");
        for (int i = 0; i < t.length - 1; i++) {
            System.out.print(t[i] + ", ");
        }
        System.out.println(t[t.length - 1] + "]");
    }

    // SCCpreprocessed.txt
    public static void main(String[] args) {
        long t1 = System.currentTimeMillis();
        Pa4Kosaraju kosaraju =
            new Pa4Kosaraju(new BufferedInputStream(System.in));
        long t2 = System.currentTimeMillis();
        long dt = (t2 - t1) / 1000;
        System.out.println("Running time: " + dt + " seconds");
        printTopFive(kosaraju);
    }
}

