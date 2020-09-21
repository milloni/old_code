public class MatrixUtil {
    /**
    * Dot product of vectors x, y
    */
    public static double dot(double[] x, double[] y) {
        double result = 0;
        int n = Math.min(x.length, y.length);
        for (int i = 0; i < n; i++) {
            result += x[i] * y[i];
        }
        return result;
    }

    /**
    * Matrix-matrix product of a, b
    */
    public static double[][] mult(double[][] a, double[][] b) {
        int m = a.length;
        int n = b[0].length;
        int l = a[0].length;
        assert l == b.length;
        double[][] result = new double[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < l; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }

    /**
    * Transpose of matrix a
    */
    public static double[][] transpose(double[][] a) {
        int m = a[0].length;
        int n = a.length;
        double result[][] = new double[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = a[j][i];
            }
        }
        return result;
    }

    /**
    * Print matrix a to stdout
    */
    public static void printMatrix(double[][] a) {
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[0].length; j++) {
                System.out.print(a[i][j] + " ");
            }
            System.out.println();
        }
    }

    /**
    * Test main() function
    */
    public static void main(String[] args) {
        double[] x = {1, 2.7, 3.14, -7};
        double[] y = {0.24, -1, 0, 4};
        assert dot(x, y) == -30.46;
        
        double[][] a = {
            {-1, 5, 2, 0},
            {1, -4, -3, -2}
        };
        double[][] b = {
            {-1, 3, 2, 0},
            {1, 4, -3, 5},
            {6, 7, -2, -4},
            {8, 9, 10, 11}
        };
        //printMatrix(a);

        double[][] c = mult(a, b);
        assert c[0][0] == 18.0;
        assert c[0][1] == 31.0;
        assert c[0][2] == -21.0;
        assert c[0][3] == 17.0;
        assert c[1][0] == -39.0;
        assert c[1][1] == -52.0;
        assert c[1][2] == 0.0;
        assert c[1][3] == -30.0;
        //printMatrix(c);
        
        double[][] d = transpose(a);
        printMatrix(d);
    }
}

