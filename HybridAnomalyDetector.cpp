
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    this->minThreshold = 0.5;
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::checkCorrelation(const TimeSeries& ts, int c1, int c2, float m, Point** points) {
    SimpleAnomalyDetector::checkCorrelation(ts, c1, c2, m);
    if (p < minThreshold || p > threshold)
        return;

    Circle c = findMinCircle(points, ts.getColSize());

    // Create struct of correlatedFeatures for the columns
    correlatedFeatures correlation;
    correlation.corrlation = m;
    correlation.feature1 = ts.getColSubject(c1);
    correlation.feature2 = ts.getColSubject(c2);
    correlation.threshold = c.radius * 1.1;
    correlation.center = c.center;

    // Add the correlated feature to the vector of correlations
    this->cf.push_back(correlation);
}
