#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class TimeSeries {
    vector<pair<string, vector<float>>> table;

public:
    // The function reads a CSV file into a vector of pairs of subjects and their vectors
    TimeSeries(const char* fileName) {

        // Create an input filestream and check the file is open
        ifstream csv(fileName);
        if (!csv.is_open()) throw std::runtime_error("Cant open the file");

        string subjects, column, line;
        float val;

        // Read the subjects of the columns
        if (csv.good()) {
            // Get the first line in the file and create a string stream from the line
            getline(csv, subjects);
            stringstream ss(subjects);

            // Get each column subject and insert a pair of its name and an empty vector
            while (getline(ss, column, ',')) {
                this->table.push_back({column, vector<float>{}});
            }
        }

        // Read values from the other lines
        while (getline(csv, line)) {
            stringstream ss(line);
            int count = 0;

            // Get every value in the line
            while (ss >> val) {

                // Add the current value to the current column's vector
                table.at(count).second.push_back(val);

                // Check the next token is not a comma, otherwise ignore it and increment the counter
                if (ss.peek() == ',') ss.ignore();
                count++;
            }
        }
        csv.close(); // Close the file
    }

    int getRowSize() {
        return this->table.size();
    }

    int getColSize() {
        return this->table[0].second.size();
    }

    vector<float> getCol(int i) {
        return this->table[i].second;
    }

    string getRowSubject(int i) {
        return this->table[i].first;
    }

};


#endif /* TIMESERIES_H_ */