#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

void generate_vertices(vector<Point>& vertices, int n) {
    vertices.clear();
    for (int i = 0; i < n; i++) {
        Point p = {rand() % 100, rand() % 100};
        // Ensure no duplicate points
        while (find(vertices.begin(), vertices.end(), p) != vertices.end()) {
            p = {rand() % 100, rand() % 100};
        }
        vertices.push_back(p);
    }
}

void max_min(vector<Point>& vertices, int i, int j, int& maximum, int& minimum, int& maxIdx, int& minIdx) {
    if (i == j) {
        maximum = minimum = vertices[i].x;
        maxIdx = minIdx = i;
        return;
    }

    if (i == j - 1) {
        if (vertices[i].x > vertices[j].x) {
            maximum = vertices[i].x;
            minimum = vertices[j].x;
            maxIdx = i;
            minIdx = j;
        } else {
            maximum = vertices[j].x;
            minimum = vertices[i].x;
            maxIdx = j;
            minIdx = i;
        }
        return;
    }

    int mid = (i + j) / 2;
    int max1, min1, maxIdx1, minIdx1;
    max_min(vertices, i, mid, maximum, minimum, maxIdx, minIdx);
    max_min(vertices, mid + 1, j, max1, min1, maxIdx1, minIdx1);

    if (max1 > maximum) {
        maximum = max1;
        maxIdx = maxIdx1;
    }
    if (min1 < minimum) {
        minimum = min1;
        minIdx = minIdx1;
    }
}

int cross_product(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int find_farthest(const vector<Point>& vertices, const vector<int>& indices, 
                 const Point& a, const Point& b) {
    int max_dist = 0;
    int farthest_idx = -1;

    for (int idx : indices) {
        int dist = abs(cross_product(a, b, vertices[idx]));
        if (dist > max_dist) {
            max_dist = dist;
            farthest_idx = idx;
        }
    }

    return farthest_idx;
}

void find_hull(vector<Point>& vertices, vector<int>& hull, 
              const vector<int>& points, const Point& a, const Point& b) {
    if (points.empty()) return;

    vector<int> new_points;
    int farthest_idx = find_farthest(vertices, points, a, b);
    if (farthest_idx == -1) return;

    const Point& c = vertices[farthest_idx];
    hull.push_back(farthest_idx);

    // Points to the left of line a-c
    vector<int> left_ac;
    for (int idx : points) {
        if (cross_product(a, c, vertices[idx]) > 0) {
            left_ac.push_back(idx);
        }
    }

    // Points to the left of line c-b
    vector<int> left_cb;
    for (int idx : points) {
        if (cross_product(c, b, vertices[idx]) > 0) {
            left_cb.push_back(idx);
        }
    }

    find_hull(vertices, hull, left_ac, a, c);
    find_hull(vertices, hull, left_cb, c, b);
}

void quickhull(vector<Point>& vertices, vector<int>& hull) {
    if (vertices.size() < 3) {
        for (int i = 0; i < vertices.size(); i++) {
            hull.push_back(i);
        }
        return;
    }

    int min_x = 0, max_x = 0;
    for (int i = 1; i < vertices.size(); i++) {
        if (vertices[i].x < vertices[min_x].x) min_x = i;
        if (vertices[i].x > vertices[max_x].x) max_x = i;
    }

    hull.push_back(min_x);
    hull.push_back(max_x);

    vector<int> left_points, right_points;
    for (int i = 0; i < vertices.size(); i++) {
        if (i == min_x || i == max_x) continue;

        int cross = cross_product(vertices[min_x], vertices[max_x], vertices[i]);
        if (cross > 0) {
            left_points.push_back(i);
        } else if (cross < 0) {
            right_points.push_back(i);
        }
    }

    find_hull(vertices, hull, left_points, vertices[min_x], vertices[max_x]);
    find_hull(vertices, hull, right_points, vertices[max_x], vertices[min_x]);
}

int main() {
    srand(time(0));
    ofstream size_file("size.csv"), time_file("time.csv");

    if (!size_file.is_open() || !time_file.is_open()) {
        cerr << "Error opening output files!" << endl;
        return 1;
    }

    for (int i = 13; i <= 20000; i *= log2(i)) {
        cout << "Processing size: " << i << endl;

        vector<Point> vertices;
        generate_vertices(vertices, i);

        auto start = high_resolution_clock::now();
        for(int t = 0;t<100;t++){
            vector<int> hull;
            quickhull(vertices, hull);
        }
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;

        size_file << i << "\n";
        time_file << elapsed.count() /100<< "\n";

        cout << "Time taken: " << elapsed.count() << " seconds\n";
    }

    size_file.close();
    time_file.close();
    cout << "CSV files generated successfully!" << endl;

    return 0;
}