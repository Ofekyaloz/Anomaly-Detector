#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

    int colSize = ts.getColSize(), rowSize = ts.getRowSize();
    float max, distance, threshold = 0.9;

    for (int i = 0; i < rowSize; i++) {

        // m is the threshold and c is the column that will be correlative to i
        int m = threshold, c = -1;
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
            correlation.feature1 = ts.getRowSubject(i);
            correlation.feature2 = ts.getRowSubject(c);
            correlation.lin_reg = linear_reg(points, colSize);

            // Find the biggest deviation of point from the linear reg
            max = 0;
            for (int k = 0; k < colSize; k++) {
                distance = dev(*points[k], correlation.lin_reg);
                if(distance > max){
                    max = distance;
                }
            }

            correlation.threshold = max;

            //  Add the correlated feature to the vector of correlations
            this->cf.push_back(correlation);
        }

    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){

}
