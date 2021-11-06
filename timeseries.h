#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{

public:
    TimeSeries(const char* CSVfileName){
    int getRowSize() const;
    int getColSize() const;
    vector<float> getCol(int i);
    string getRowSubject(int i) const;
    }
};

#endif /* TIMESERIES_H_ */