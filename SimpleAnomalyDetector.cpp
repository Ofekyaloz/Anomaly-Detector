/*
 * Authors: Gili Gutfeld - 209284512
 * Ofek Yaloz - 206666729
 */

#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

// Earlier stage - Create vector of correlations by learn normality from the TimeSeries
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

    // Help numbers
    int colSize = ts.getColSize(), rowSize = ts.getRowSize();
    float max, distance, threshold = 0.9;

    for (int i = 0; i < rowSize; i++) {

        // m is the threshold and c is the column that will be correlative to i
        float m = threshold, c = -1;
        for (int j = i + 1; j < rowSize; j++) {

            // Check if the columns correlatives and save the correlation and the number of column
            float p = pearson(&ts.getCol(i)[0], &ts.getCol(j)[0], colSize);
            if (p > m) {
                m = p;
                c = j;
            }
        }

        // When we find correlation between columns i and c we get their points
        if (c != -1) {
            Point *points[colSize];

            // Save the points of the columns in a vector
            vector<float> v1 = ts.getCol(i), v2 = ts.getCol(c);
            for (int k = 0; k < colSize; k++)
                points[k] = new Point(v1[k], v2[k]);

            // Create struct of correlatedFeatures for the columns
            correlatedFeatures correlation;
            correlation.corrlation = m;
            correlation.feature1 = ts.getColSubject(i);
            correlation.feature2 = ts.getColSubject(c);
            correlation.lin_reg = linear_reg(points, colSize);

            // Find the biggest deviation of point from the linear reg
            max = 0;
            for (int k = 0; k < colSize; k++) {
                distance = dev(*points[k], correlation.lin_reg);
                if(distance > max){
                    max = distance;
                }
            }

            correlation.threshold = max * 1.1;

            //  Add the correlated feature to the vector of correlations
            this->cf.push_back(correlation);
        }

    }
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
            Point *p = new Point((*ts.getColBySubject(c.feature1))[i],
                                 (*ts.getColBySubject(c.feature2))[i]);

            // If the deviation of the point is bigger than the threshold report about an anomaly detection
            if (dev(*p, c.lin_reg) > c.threshold) {
                AnomalyReport *an = new AnomalyReport(c.feature1 + "-" + c.feature2, i + 1);
                detects.push_back(*an);
            }
        }
    }
    return detects;
}
