import java.util.Arrays;

public class Heapsort {
    public static void sort(int[] a) {
        heapify(a);
        for (int i = a.length - 1; i >= 1; i--) {
            swap(a, 0, i);
            bubbleDown(a, 0, i); 
        }
    }

    // Old implementation of heapify
    // Runs in O(n * log(n)) time
    private static void _heapify(int[] a) {
        for (int i = 1; i < a.length; i++) {
            bubbleUp(a, i, i + 1);
        }
    }

    // Runs in O(n) time
    private static void heapify(int[] a) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            bubbleDown(a, i, n);
        }
    }

    private static void bubbleUp(int[] a, int k, int hi) {
        int p = (k + 1) / 2 - 1;
        while (k > 0 && a[p] < a[k]) {
            swap(a, p, k);
            k = p;
            p = (k + 1) / 2 - 1;
        }
    }

    private static void bubbleDown(int[] a, int k, int hi) {
        int c = 2 * k + 1;
        if (c + 1 < hi && a[c] < a[c + 1]) c++;
        while (c < hi && a[k] < a[c]) {
            swap(a, k, c);
            k = c;
            c = 2 * k + 1;
            if (c + 1 < hi && a[c] < a[c + 1]) c++;
        }
    }

    private static void swap(int[] a, int i, int j) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    public static void main(String[] args) {
        int[] a = {7, 3, 5, 1, 0, 4, 6, 2, 7, 11, 9, 13, 0, 15};
        //int[] a = {1, 3, 2};
        sort(a);
        System.out.println(Arrays.toString(a));
    }
}

