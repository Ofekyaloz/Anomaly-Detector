#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{
    map<string, vector<float>> map;
    vector(string) subj;


public:
    TimeSeries(const char* CSVfileName){
        bool new_line = False;
        char* str = CSVfileName;
        str.co
        while (str != NULL)
        {
            if (!new_line && str.find('\n')) {
                break;
            }
            else if (!new_line) {
                sub = strtok (NULL, ",");
                this->map[sub] = vector<float>;
            }
        }
};



#endif /* TIMESERIES_H_ */
