#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <limits.h>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};


void generate_vertices(vector<Point> &vertices, int n) {
    for (int i = 0; i < n; i++) {
        vertices.push_back({rand() % 100, rand() % 100});
    }
}

void max_min(vector<Point> &vertices, int i, int j, int &maximum, int &minimum, int &maxIdx, int &minIdx) {
    if (i == j) {
        if (vertices[i].x > maximum) {
            maximum = vertices[i].x;
            maxIdx = i;
        }
        if (vertices[i].x < minimum) {
            minimum = vertices[i].x;
            minIdx = i;
        }
        return;
    } else if (i == j - 1) {
        if (vertices[i].x > vertices[j].x) {
            if (vertices[i].x > maximum) {
                maximum = vertices[i].x;
                maxIdx = i;
            }
            if (vertices[j].x < minimum) {
                minimum = vertices[j].x;
                minIdx = j;
            }
        } else {
            if (vertices[j].x > maximum) {
                maximum = vertices[j].x;
                maxIdx = j;
            }
            if (vertices[i].x < minimum) {
                minimum = vertices[i].x;
                minIdx = i;
            }
        }
        return;
    }

    int mid = (i + j) / 2;
    int max1 = vertices[mid + 1].x, min1 = vertices[mid + 1].x;
    int maxIdx1 = mid + 1, minIdx1 = mid + 1;

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

double area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}


int farthest_point(vector<Point> &vertices, vector<int> &side, int minIdx, int maxIdx) {
    double max_area = 0;
    int idx = -1;

    int x1 = vertices[minIdx].x;
    int y1 = vertices[minIdx].y;
    int x2 = vertices[maxIdx].x;
    int y2 = vertices[maxIdx].y;

    for (int i = 0; i < side.size(); i++) {
        int pointIdx = side[i];
        double curr_area = area(x1, y1, x2, y2, vertices[pointIdx].x, vertices[pointIdx].y);
        if (curr_area > max_area) {
            max_area = curr_area;
            idx = pointIdx;
        }
    }

    return idx;
}


void quickhull(vector<Point> &vertices, int n, int minIdx, int maxIdx, vector<int> &hull) {
    if(minIdx == maxIdx)
    return ;
    vector<int> left, right;

    int x1 = vertices[minIdx].x;
    int y1 = vertices[minIdx].y;
    int x2 = vertices[maxIdx].x;
    int y2 = vertices[maxIdx].y;

    for (int i = 0; i < n; i++) {
        if (i == minIdx || i == maxIdx) continue;
        int val = (vertices[i].x - x1) * (y2 - y1) - (vertices[i].y - y1) * (x2 - x1);
        if (val > 0) {
            left.push_back(i);
        } else if (val < 0) {
            right.push_back(i);
        }
    }

    int idx_left = farthest_point(vertices, left, minIdx, maxIdx);
    if (idx_left == -1) {
        if (find(hull.begin(), hull.end(), minIdx) == hull.end()) {
            hull.push_back(minIdx);
            cout<<vertices[minIdx].x<<" "<<vertices[minIdx].y<<endl;
            return;
        }
    } else {
        quickhull(vertices, n, minIdx, idx_left, hull);
        quickhull(vertices, n, idx_left, maxIdx, hull);
    }

    int idx_right = farthest_point(vertices, right, minIdx, maxIdx);
    if (idx_right == -1) {
        if (find(hull.begin(), hull.end(), maxIdx) == hull.end()) {
            hull.push_back(maxIdx);
            cout<<vertices[maxIdx].x<<" "<<vertices[maxIdx].y<<endl;
            return;
        }
    } else {
        quickhull(vertices, n, maxIdx, idx_right, hull);
        quickhull(vertices, n, idx_right, minIdx, hull);
    }
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<Point> vertices;
    generate_vertices(vertices, n);

    cout << "Generated Points:\n";
    for (int i = 0; i < n; i++) {
        cout << vertices[i].x <<", ";
    }
    cout<<"\ny\n";
    for (int i = 0; i < n; i++) {
        cout << vertices[i].y <<", ";
    }
    cout<<"end";

    int maximum = INT32_MIN;
    int minimum = INT32_MAX;
    int maxIdx = 0, minIdx = 0;

    max_min(vertices, 0, n - 1, maximum, minimum, maxIdx, minIdx);

    vector<int> hull;
    quickhull(vertices, n, minIdx, maxIdx, hull);

    cout << "Convex Hull Points:\n";
    for (int i : hull) {
        cout << "(" << vertices[i].x << ", " << vertices[i].y << ")\n";
    }

    return 0;
}