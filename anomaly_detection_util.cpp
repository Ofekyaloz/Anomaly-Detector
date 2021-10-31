/*
 * animaly_detection_util.cpp
 *
 * Authors: Gili Gutfeld - 209284512
 * Ofek Yaloz - 206666729
 */

#include "anomaly_detection_util.h"
#include <math.h>

float avg(float* x, int size) {
    if (size == 0 || x == nullptr) {
        return -1;
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum / size;
}

float var(float* x, int size) {
    if (size == 0 || x == nullptr) {
        return -1;
    }
    float sum = 0, miu = avg(x, size);
    for (int i = 0; i < size; i++) {
        sum += x[i] * x[i];
    }
    return sum / size - miu * miu;
}

float cov(float* x, float* y, int size) {
    if (size == 0 || x == nullptr || y == nullptr) {
        return -1;
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i] * y[i];
    }
    return sum / size - avg(x, size) * avg(y, size);
}

float pearson(float* x, float* y, int size) {
    if (size == 0 || x == nullptr || y == nullptr) {
        return -1;
    }
    return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

Line linear_reg(Point** points, int size) {
    if (size == 0 || points == nullptr) {
        return Line(0,0);
    }
    float x[size], y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size) / var(x, size);
    float b = avg(y, size) - a * avg(x, size);
    return Line(a, b);
}

float dev(Point p,Point** points, int size) {
    if (size == 0 || points == nullptr) {
        return -1;
    }
    return dev(p, linear_reg(points, size));
}

float dev(Point p,Line l) {
    float num = p.y - l.f(p.x);
    if (num < 0) {
        num *= -1;
    }
    return num;
}