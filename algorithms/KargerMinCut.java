import java.io.BufferedInputStream;
import static java.lang.Math.log;

public class KargerMinCut {
    public static void main(String[] args) {
        RandomContractionCut karger =
            new RandomContractionCut(new BufferedInputStream(System.in));
        int n = karger.getn();
        int numIterations = (n > 2) ? ((int) (n * log((double) n))) : (8);

        RandomContractionCut copy = karger.copyOf();
        copy.init();
        RandomContractionCut.Cut bestCut = copy.getCut();
        for (int i = 0; i < numIterations; i++) {
            copy = karger.copyOf();
            copy.init();
            RandomContractionCut.Cut cut = copy.getCut();
            if (cut.getSize() < bestCut.getSize()) bestCut = cut;
        }

        System.out.println("Cut: " + bestCut);
        System.out.println("Cut length: " + bestCut.getSize());
    }
}

