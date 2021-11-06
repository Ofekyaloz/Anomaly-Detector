class TimeSeries{
    int getRowSize() const;
    int getColSize() const;
    vector<float> getCol(int i);
    string getRowSubject(int i) const;
    };

class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
}; 