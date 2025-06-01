#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Structure to represent a 2D point
struct Point {
    int x, y;
};

// Node in the 2D Range Tree
struct RangeTreeNode {
    int x;
    vector<Point> pointsSortedByY;
    RangeTreeNode *left, *right;

    RangeTreeNode() : left(nullptr), right(nullptr) {}
};

// Comparators
bool compareX(const Point &a, const Point &b) { return a.x < b.x; }
bool compareY(const Point &a, const Point &b) { return a.y < b.y; }

class RangeTree2D {
    RangeTreeNode* root;

    // Recursive tree builder
    RangeTreeNode* build(vector<Point>& points) {
        if (points.empty()) return nullptr;

        sort(points.begin(), points.end(), compareX);
        RangeTreeNode* node = new RangeTreeNode();
        node->pointsSortedByY = points;

        if (points.size() == 1) {
            node->x = points[0].x;
            return node;
        }

        int mid = points.size() / 2;
        vector<Point> leftPoints(points.begin(), points.begin() + mid);
        vector<Point> rightPoints(points.begin() + mid, points.end());

        node->x = points[mid].x;
        node->left = build(leftPoints);
        node->right = build(rightPoints);

        return node;
    }

    // Perform query and collect results in a set (no duplicates)
    void query(RangeTreeNode* node, int x1, int x2, int y1, int y2, set<pair<int, int>>& result) {
        if (!node) return;

        if (x2 < node->x) {
            query(node->left, x1, x2, y1, y2, result);
        } else if (x1 > node->x) {
            query(node->right, x1, x2, y1, y2, result);
        } else {
            for (const Point& p : node->pointsSortedByY) {
                if (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2) {
                    result.insert({p.x, p.y});
                }
            }
            if (node->left) query(node->left, x1, x2, y1, y2, result);
            if (node->right) query(node->right, x1, x2, y1, y2, result);
        }
    }

public:
    RangeTree2D(const vector<Point>& points) {
        vector<Point> pts = points;
        root = build(pts);
    }

    // Query using Chebyshev distance
    vector<Point> queryChebyshev(int x0, int y0, int d) {
        int x1 = x0 - d, x2 = x0 + d;
        int y1 = y0 - d, y2 = y0 + d;

        set<pair<int, int>> resultSet;
        query(root, x1, x2, y1, y2, resultSet);

        vector<Point> result;
        for (auto& p : resultSet) {
            result.push_back({p.first, p.second});
        }
        return result;
    }
};



int main() {
    int n;
    cout << "Enter number of restaurants: ";
    cin >> n;

    vector<Point> restaurants(n);
    cout << "Enter the coordinates (x y) of each restaurant:\n";
    for (int i = 0; i < n; ++i) {
        cin >> restaurants[i].x >> restaurants[i].y;
    }

    int x, y, d;
    cout << "Enter reference point (x y): ";
    cin >> x >> y;
    cout << "Enter Chebyshev distance: ";
    cin >> d;

    // Build tree and query
    RangeTree2D tree(restaurants);
    vector<Point> found = tree.queryChebyshev(x, y, d);

    // Output results
    cout << "\nRestaurants within Chebyshev distance " << d << " of (" << x << ", " << y << "):\n";
    cout << "Total: " << found.size() << " restaurant(s)\n";
    for (auto& p : found) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
