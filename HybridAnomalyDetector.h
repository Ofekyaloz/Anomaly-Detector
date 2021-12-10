

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
    float minThreshold;

public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    void checkCorrelation(const TimeSeries& ts, int c1, int c2, float m, Point **point) override;
    virtual bool isDeviation (Point *p, correlatedFeatures c);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
