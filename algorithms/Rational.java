public class Rational {
    private int m = 0;
    private int n = 1;

    public Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw new IllegalArgumentException("fuck off jack chick");
        }
        this.m = numerator;
        this.n = denominator;
    }

    public Rational plus(Rational that) {
        int b = lcm(this.n, that.n);
        return new Rational(this.m * b / this.n + that.m * b / that.n, b);
    }

    public Rational minus(Rational that) { 
        int b = lcm(this.n, that.n);
        return new Rational(this.m * b / this.n - that.m * b / that.n, b);
    }

    public Rational times(Rational that) {
        int a = this.m * that.m;
        int b = this.n * that.n;
        int l = lcm(a, b);
        a /= l;
        b /= l;
        return new Rational(a, b);
    }

    public Rational divides(Rational that) {
        int a = this.m * that.n;
        int b = this.n * that.m;
        int l = lcm(a, b);
        a /= l;
        b /= l;
        return new Rational(a, b);
    }

    @Override
    public boolean equals(Object that) {
        Rational tthat = (Rational) that;
        return this.m == tthat.m && this.n == tthat.n;
    }

    @Override
    public String toString() {
        return String.format("%d/%d", this.m, this.n);
    }

    private int lcm(int a, int b) {
        return a * b / gcd(a, b);
    }

    private static int gcd(int a, int b) {
        if (b == 0) return a;
        if (b > a) return gcd(b, a);
        return gcd(b, a % b);
    }

    public static void main(String[] args) {
        Rational r1 = new Rational(1, 2);
        assert r1.equals(new Rational(1, 2));

        Rational r2 = new Rational(1, 4);
        Rational r3 = r1.plus(r2);
        assert r3.equals(new Rational(3, 4));

        Rational r4 = r3.minus(r1);
        assert r4.equals(new Rational(1, 4));
    }
}

