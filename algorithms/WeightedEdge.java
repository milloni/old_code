public class WeightedEdge {
    private int from;
    private int to;
    private double weight;

    public WeightedEdge(int from, int to, double weight) {
        this.from = from;
        this.to = to;
        this.weight = weight;
    }

    @Override
    public boolean equals(Object that) {
        if (this == that) {
            return true;
        }
        WeightedEdge thatEdge = (WeightedEdge) that;
        return from == thatEdge.from
            && to == thatEdge.to
            && weight == thatEdge.weight;
    }

    @Override
    public String toString() {
        return String.format("%d->%d (%f)", from, to, weight);
    }

    public int from() {
        return this.from;
    }

    public int to() {
        return this.to;
    }

    public double weight() {
        return this.weight;
    }
}
