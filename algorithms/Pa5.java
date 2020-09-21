import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.StringReader;
import java.util.regex.Pattern;

public class Pa5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        int n = sc.nextInt();
        sc.nextLine();
        WeightedDigraph g = new WeightedDigraph(n);

        while (sc.hasNextLine()) {
            Scanner lsc = new Scanner(new StringReader(sc.nextLine()));
            int v = lsc.nextInt() - 1;
            while (lsc.hasNext()) {
                String[] dupa = lsc.next().split(",");
                int w = Integer.parseInt(dupa[0]) - 1;
                double weight = Double.parseDouble(dupa[1]);
                //System.out.format("%d %d %f\n", v, w, weight);
                g.addEdge(new WeightedDigraph.Edge(v, w, weight));
            }
        }

        DijkstraNaive dijkstra = new DijkstraNaive(g, 0);
        /*for (int i = 0; i < g.getn(); i++) {
            System.out.format("%d: [%.2f]\n", i, dijkstra.distTo(i));
        }*/

        // WARNING: indexing starts at 1 here
        int[] verticesOfInterest = {7,37,59,82,99,115,133,165,188,197};
        System.out.print((int) dijkstra.distTo(verticesOfInterest[0] - 1));
        for (int i = 1; i < verticesOfInterest.length; i++) {
            int d = (int) (dijkstra.distTo(verticesOfInterest[i] - 1));
            System.out.print("," + d);
        }
        System.out.println();
    }
}

