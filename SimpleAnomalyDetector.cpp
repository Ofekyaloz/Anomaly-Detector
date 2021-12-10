/*
 * Authors: Gili Gutfeld - 209284512
 * Ofek Yaloz - 206666729
 */

#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->threshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

// Earlier stage - Create vector of correlations by learn normality from the TimeSeries
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

    // Help numbers
    int colSize = ts.getColSize(), rowSize = ts.getRowSize();

    for (int i = 0; i < rowSize - 1; i++) {
        // m is the threshold and c is the column that will be correlative to i
        float m = 0, c = -1;
        for (int j = i + 1; j < rowSize; j++) {

            // Check if the columns correlatives and save the correlation and the number of column
            float p = abs(pearson(&ts.getCol(i)[0], &ts.getCol(j)[0], colSize));
            if (p > m) {
                m = p;
                c = j;
            }
        }

        // Add the correlation between columns i and c by using pointsToArray and checkCorrelation functions
        Point **points = pointsToArray(ts.getCol(i), ts.getCol(c), colSize);
        checkCorrelation(ts, i, c, m, points);

        // delete all the points
        for (int k = 0; k < colSize; k++)
            delete points[k];
        delete[] points;
    }
}

// Save the points of the columns in an array
Point** SimpleAnomalyDetector::pointsToArray(vector<float> v1, vector<float> v2, int size) {
    Point **points = new Point *[size];
    for (int i = 0; i < size; i++) {
        points[i] = new Point(v1[i], v2[i]);
    }
    return points;
}

// Find the biggest deviation of point from the linear reg
float SimpleAnomalyDetector::getThreshold(Point** points,int size,Line lin_reg) {
    float max = 0, distance;
    for (int i = 0; i < size; i++) {
        distance = dev(*points[i], lin_reg);
        if (distance > max) {
            max = distance;
        }
    }
    return max;
}

void SimpleAnomalyDetector::checkCorrelation(const TimeSeries& ts, int c1, int c2, float m, Point** points) {
    if (m < this->threshold)
        return;

    int size = ts.getColSize();

    // Create struct of correlatedFeatures for the columns
    correlatedFeatures correlation;
    correlation.corrlation = m;
    correlation.feature1 = ts.getColSubject(c1);
    correlation.feature2 = ts.getColSubject(c2);
    correlation.lin_reg = linear_reg(points, size);
    correlation.threshold = getThreshold(points, size, correlation.lin_reg) * 1.1;

    // Add the correlated feature to the vector of correlations
    this->cf.push_back(correlation);
}

// Anomaly detection stage - find anomaly detections from the correlations we learned in the earlier stage
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts) {

    // Vector of the anomaly reports and count of rows and correlated features.
    vector<AnomalyReport> detects;
    int rowCount = ts.getColSize();

    // A loop for the rows
    for (int i = 0; i < rowCount; i++) {

        // A loop for the correlated features
        for (correlatedFeatures c : cf) {

            // Create a point from the features in the correlation in the row i, column j
            Point *p = new Point((*ts.getColBySubject(c.feature1))[i],(*ts.getColBySubject(c.feature2))[i]);

            // If the deviation of the point is bigger than the threshold report about an anomaly detection
            if (dev(*p, c.lin_reg) > c.threshold) {
                AnomalyReport *an = new AnomalyReport(c.feature1 + "-" + c.feature2, i + 1);
                detects.push_back(*an);
            }
            delete[] p;
        }
    }
    return detects;
}
