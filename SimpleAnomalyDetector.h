struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> correlated;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts) {
        int i,j, rowsSize = ts.getRowSize();
        for (int i = 0; i < rowsSize; i++) {
            int m = 0, c = -1;
            for (int j = i + 1; j < rowsSize; j++ ) {
                float p = pearson(ts.getColumn(i), ts.getColumn(j), ts.getColumnSize())
                if (p > m) {
                    m = p;
                    c = j;
                }
            }
            if (c != -1) {
                Point* ps[rowsSize];
                vector v1 = ts.getColumn(i), v2 = ts.getColumn(j);
                for (int h = 0; h < rowsSize; h++)
                    ps[h]=new Point(v1[h], v2[h]);
                correlatedFeatures correlatedFeatures(ts.getSub(i), ts.getSub(j), m, lin_reg(ps, rowsSize), 0.7)
                correlated.push_back(correlateFeatures);
            }
        }
    }
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};