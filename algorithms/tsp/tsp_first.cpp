#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <cassert>
#include <bitset>
#include <algorithm>

constexpr int INT_BITS = 32;
constexpr int MAX_POINTS = INT_BITS - 1;

class Point {
  public:
    Point(double x, double y);
    double x() const;
    double y() const;

  private:
    double m_x;
    double m_y;
};

inline
Point::Point(double x, double y)
: m_x(x)
, m_y(y)
{
}

inline
double Point::x() const
{
    return m_x;
}

inline
double Point::y() const
{
    return m_y;
}

int loadData(std::vector<Point> *out, std::istream& inputStream)
{
    int pointCount;
    inputStream >> pointCount;
    out->reserve(pointCount);
    for (int i = 0; i < pointCount; i++) {
        double x, y;
        if (!(inputStream >> x) || !(inputStream >> y)) {
            return -1;
        }
        out->push_back(Point(x, y));
    }
    return 0;
}

int intpow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int getIndex(int path, int dest, int size)
{
    return size * path + dest;
}

double distance(const Point& a, const Point& b)
{
    return std::sqrt((a.x() - b.x()) * (a.x() - b.x())
        + (a.y() - b.y()) * (a.y() - b.y()));
}

int set_size(int set)
{
    //int _set = set;
    int sum = 0;
    while (set > 0) {
        if ((set & 1) == 1) {
            sum++;
        }
        set /= 2;
    }
    //std::cout << "SET_SIZE(" << _set << ") == " << sum << std::endl;
    return sum;
}

bool contains(int set, int x)
{
    return (set & (1 << x)) != 0;
}

int subtract(int set, int x)
{
    //std::cout << "SUBTRACT: " << set << " " << x << " " << (set & ~(1 << x)) << std::endl;
    return set & ~(1 << x);
}

double computeTsp(const std::vector<Point>& points)
{
    // Set up variables for the algorithm
    const int n = static_cast<int>(points.size());
    assert(n <= MAX_POINTS);
    const int subsetCount = intpow(2, n);
    const int tableSize = n * subsetCount;
    std::vector<double> subproblems(tableSize);

    // Base cases
    std::cout << "Computing base cases" << std::endl;
    for (int i = 0; i < subsetCount; i++) {
        subproblems[getIndex(i, 0, n)] =
            std::numeric_limits<double>::infinity();
    }
    subproblems[getIndex(1, 0, n)] = .0;

    // Compute recurrence
    for (int size = 2; size <= n; size++) {
        std::cout << "Iteration: " << size << std::endl;
        for (int set = 0; set < subsetCount; set++) {
            if (set_size(set) != size || !contains(set, 0)) {
                continue;
            }

            //std::cout << "&&&&&" << std::endl;
            for (int j = 1; j < n; j++) {
                if (!contains(set, j)) {
                    continue;
                }

                double minimum = std::numeric_limits<double>::infinity();
                for (int k = 0; k < n; k++) {
                    //std::cout << "SET: " << set << " K: " << k << std::endl;
                    if (!contains(set, k) || k == j) {
                        //std::cout << "####" << std::endl;
                        continue;
                    }
                    //std::cout << "@@@" << std::endl;

                    double x = subproblems[getIndex(subtract(set, j), k, n)]
                        + distance(points[k], points[j]);
                    if (x < minimum) {
                        minimum = x;
                    }
                }
                subproblems[getIndex(set, j, n)] = minimum;
            }
        }
    }

    // Choose the best path back to source vertex
    int allSet = subsetCount - 1;
    double result = std::numeric_limits<double>::infinity();
    for (int i = 0; i < n; i++) {
        double x = subproblems[getIndex(allSet, i, n)]
            + distance(points[i], points[0]);
        if (x < result) {
            result = x;
        }
    }
    return result;
}

int main()
{
    std::vector<Point> points;
    int rc = loadData(&points, std::cin);
    if (rc != 0) {
        std::cerr << "Error while processing the input" << std::endl;
        return 1;
    }

    std::cout << computeTsp(points) << std::endl;
    return 0;
}
