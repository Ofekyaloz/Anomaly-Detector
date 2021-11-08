//
// Created by giligutfeld on 07/11/2021.
//

#ifndef THE_BEST_PROJECT_TIMESERIES_H
#define THE_BEST_PROJECT_TIMESERIES_H

#include <vector>
#include <string>
using namespace std;

class TimeSeries{
    vector<pair<string, vector<float>>> table;

public:
    TimeSeries(const char* fileName);
    int getRowSize() const;
    int getColSize() const;
    vector<float> getCol(int i) const;
    string getColSubject(int i) const;
    const vector<float>* getColBySubject(string s) const;
};

#endif //THE_BEST_PROJECT_TIMESERIES_H
