/*
 * Authors: Gili Gutfeld - 209284512
 * Ofek Yaloz - 206666729
 */

#include "minCircle.h"

using namespace std;

// return the distance between two points
float distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// check if the circle contains the point
bool is_in_circle(const Circle& c, const Point& p) {
    return (distance(c.center, p) <= c.radius);
}

// get the center of the circle
Point get_circle_center(float x1, float y1, float x2, float y2) {
    float a = x1 * x1 + y1 * y1;
    float b = x2 * x2 + y2 * y2;
    float c = x1 * y2 - y1 * x2;
    return Point((y2 * a - y1 * b) / (2 * c), (x1 * b - x2 * a) / (2 * c));
}

// get the minimum circle from three points by calling the get_circle_center function
Circle get_circle(const Point& p1, const Point& p2, const Point& p3) {
    Point I = get_circle_center(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y);
    I.x += p1.x;
    I.y += p1.y;
    return {I, distance(I, p1)};
}

// get the minimum circle from two points
Circle get_circle(const Point& p1, const Point& p2) {
    Point *p = new Point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
    return Circle(*p, (distance(p1, p2)) / 2.0);
}

// check if the circle contains all the points in the vector we got
bool is_encloses_points(const Circle& c, const vector<Point>& p) {
    for (const Point &p: p)
        if (!is_in_circle(c, p))
            return false;
    return true;
}

// get the minimum circle from 0, 1, 2 or 3 points
Circle min_circle_trivial(vector<Point>& points) {
    if (points.empty()) {
        return {{0, 0}, 0};
    } else if (points.size() == 1) {
        return {points[0], 0};
    } else if (points.size() == 2) {
        return get_circle(points[0], points[1]);
    }

    // Check if we can find a circle that contains all the three points by only two points
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = get_circle(points[i], points[j]);
            if (is_encloses_points(c, points))
                return c;
        }
    }

    // we must create circle from three points
    return get_circle(points[0], points[1], points[2]);
}

// welzl algorithm - returns the minimum circle by using in a vector of points and of boundary points.
// n represents the number of points in points that are not yet processed.
Circle welzl_algorithm(Point** points, vector<Point> boundary_points, int n)
{
    // Base case when all points processed or |boundary_points| = 3
    if (n == 0 || boundary_points.size() == 3) {
        return min_circle_trivial(boundary_points);
    }

    // Get the minimum circle from the vector of points without the last one
    Circle c = welzl_algorithm(points, boundary_points, n - 1);

    // If c contains the last point, return c
    if (is_in_circle(c, *points[n - 1])) {
        return c;
    }

    // Otherwise, the last point must be on the boundary_points of the minimum circle
    boundary_points.push_back(*points[n - 1]);

    // Return the minimum circle for the vector of points without the last one and boundary_points with the last one
    return welzl_algorithm(points, boundary_points, n - 1);
}

Circle findMinCircle(Point** points,size_t size) {
    return welzl_algorithm(points, {}, size);
}
