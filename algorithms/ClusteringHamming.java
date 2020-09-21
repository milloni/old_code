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
import java.util.BitSet;
import java.util.Comparator;

public class ClusteringHamming {
    private BitSet[] values;
    private BitSet[] codes;
    private int numValues;
    private int numBits;
    private int numClusters;

    private void _d(String msg) {
        System.out.println("Log: " + msg);
    }

    private ClusteringHamming(InputStream in) {
        Scanner sc = new Scanner(in);
        numValues = sc.nextInt();
        numBits = sc.nextInt();
        values = new BitSet[numValues];
        codes = new BitSet[numValues];
        for (int i = 0; i < values.length; i++) {
            BitSet bitSet = new BitSet(numBits);
            values[i] = bitSet;
            for (int j = 0; j < numBits; j++) {
                boolean bit = sc.nextInt() == 0;
                bitSet.set(j, bit);
            }
            codes[i] = hammingCode(bitSet);
        }

        //System.out.println(values[0] + " " + codes[0]);
        doClustering();
    }

    private void doClustering() {
        BitSet[] codesSorted = new BitSet[codes.length];
        for (int i = 0; i < codesSorted.length; i++) {
            codesSorted[i] = codes[i];
        }
        Arrays.sort(codesSorted, new BitSetComparator());
        numClusters++;
        for (int i = 1; i < codesSorted.length; i++) {
            if (!codesSorted[i].equals(codesSorted[i - 1])) {
                numClusters++;
            }
        }
    }

    private BitSet hammingCode(BitSet bitSet) {
        BitSet result = new BitSet();
        for (int i = 0; i < bitSet.length(); i++) {
            BitSet iBitSet = makeBitSet(i);
            for (int j = 0; j < iBitSet.length(); j++) {
                if (iBitSet.get(j) && bitSet.get(i)) {
                    result.flip(j);
                }
            }
        }
        return result;
    }

    private BitSet makeBitSet(int n) {
        BitSet result = new BitSet();
        int i;
        for (i = 0; n > 0; i++) {
            result.set(i, (n & 1) == 1);
            n >>= 1;
        }

        System.out.println(result);
        for (int j = 0; j < (i + 1) / 2; j++) {
            boolean b = result.get(j);
            result.set(j, result.get(i - j));
            result.set(i - j, b);
        }
        System.out.println(result);
        return result;
    }

    public int getMaxClusters() {
        return numClusters;
    }

    public static void main(String[] args) {
       // ClusteringHamming ch =
        //    new ClusteringHamming(new BufferedInputStream(System.in));
        //System.out.println(ch.getMaxClusters());
        BitSet s = BitSet.valueOf("111000001101001111001111".getBytes());
        printBitSet(s);
    }

    public static void printBitSet(BitSet s) {
        for (int i = 0; i < s.length(); i++) {
            if (s.get(i)) System.out.print("1");
            else System.out.print("0");
        }
        System.out.println();
    }

    public static class BitSetComparator implements Comparator<BitSet> {
        @Override
        public int compare(BitSet a, BitSet b) {
            if (a.length() > b.length()) return 1;
            if (a.length() < b.length()) return -1;

            for (int i = 0; i < a.length(); i++) {
                if (a.get(i) == true && b.get(i) == false) {
                    return 1;
                }
                if (a.get(i) == false && b.get(i) == true) {
                    return -1;
                }
            }

            return 0;
        }
    }
};

