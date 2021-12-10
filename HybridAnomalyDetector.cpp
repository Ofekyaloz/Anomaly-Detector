
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    this->minThreshold = 0.5;
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void HybridAnomalyDetector::checkCorrelation(const TimeSeries& ts, int c1, int c2, float m, Point** points) {
    SimpleAnomalyDetector::checkCorrelation(ts, c1, c2, m, points);
    if (m < minThreshold || m > threshold)
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

// return if there is a deviation in both, the HybriadAmomalyDetector and in the SimpleAnomalyDetector
bool HybridAnomalyDetector::isDeviation(Point *p, correlatedFeatures c) {
    return ((c.corrlation > minThreshold) && (c.corrlation < threshold) && (distance(*p, c.center) > c.threshold))
    || ((c.corrlation >= threshold) && (SimpleAnomalyDetector::isDeviation(p, c)));
}