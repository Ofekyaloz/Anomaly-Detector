#include <string.h>
#include <vector>
#include "../anomaly_detection_util.h"
#include "../AnomalyDetector.h"

struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    std::vector<correlatedFeatures> correlated;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts) {
        int i,j, rowsSize = ts.getRowSize();
        for (int i = 0; i < rowsSize; i++) {
            int m = 0, c = -1;
            for (int j = i + 1; j < rowsSize; j++ ) {
                float p = pearson(ts.getCol(i), ts.getCol(j), ts.getColSize())
                if (p > m) {
                    m = p;
                    c = j;
                }
            }
            if (c != -1) {
                Point* ps[rowsSize];
                std::vector v1 = ts.getCol(i), v2 = ts.getCol(j);
                for (int h = 0; h < rowsSize; h++)
                    ps[h]=new Point(v1[h], v2[h]);
                correlatedFeatures correlatedFeatures(ts.getRowSubject(i), ts.getRowSubject(j), m, lin_reg(ps, rowsSize), 0.7)
                correlated.push_back(correlateFeatures);
            }
        }
    }
    virtual std::vector<AnomalyReport> detect(const TimeSeries& ts);
    std::vector<correlatedFeatures> getNormalModel();
};