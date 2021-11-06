#include <string.h>
#include <vector>
#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "timeseries.h"

struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    std::vector<correlatedFeatures> correlated;
    std::vector<float> distance;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts) {
        int i,j, colSize = ts.getColSize();
        float treshold = 0.9;
        for (int i = 0; i < colSize; i++) {
            int m = 0, c = -1;
            for (int j = i + 1; j < colSize; j++ ) {
                float* f = &ts.getCol(i)[0];
                float* g = &ts.getCol(j)[0];
                float p = pearson(f, g, colSize);
                if (p > m) {
                    m = p;
                    c = j;
                }
            }
            if (c != -1) {
                Point* ps[colSize];
                vector<float> v1 = ts.getCol(i), v2 = ts.getCol(j);
                for (int h = 0; h < colSize; h++)
                    ps[h]=new Point(v1[h], v2[h]);
                correlatedFeatures correlatedFeatures(ts.getRowSubject(i), ts.getRowSubject(j), m, lin_reg(ps, colSize), treshold);
                correlated.push_back(correlateFeatures);
            }
        }
        int corlen = correlated.size();
        for (i = 0; i < corlen; i++) {
            vector<float> v1 = ts.getCol(correlated[i].feature1), v2 = ts.getCol(correlated[i].feature2);
            float max = 0;
            for (j = 0; j < colSize; j++) {
                Point p = new Point(v1[j], v2[j]);
                float dis = dev(p, correlated[i].lin_reg);
                if (dis > max)
                    max = dis;
            }
            distance.push_back(max);
        }
    }

    virtual std::vector<AnomalyReport> detect(const TimeSeries& ts);

    std::vector<correlatedFeatures> getNormalModel();
};