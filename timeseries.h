#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>

using namespace std;

class TimeSeries {
    vector<pair<string, vector<float>>> table;


public:
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>
    TimeSeries(const char *CSVfileName) {

        // Create a vector of <string, int vector> pairs to store the result

        // Create an input filestream
        ifstream myFile(CSVfileName);

        // Make sure the file is open
        if (!myFile.is_open()) throw std::runtime_error("Cant open the file");

        // Helper vars
        string subjects, column, line;
        int val;

        // Read the column names
        if (myFile.good()) {
            // Extract the first line in the file
            getline(myFile, subjects);

            // Create a string stream from line
            stringstream ss(subjects);

            // Extract each column name
            while (std::getline(ss, column, ',')) {

                // Initialize and add <colname, int vector> pairs to result
                this->table.push_back({column, vector<float>{}});
            }
        }

        // Read data, line by line
        while (std::getline(myFile, line)) {
            // Create a string stream of the current line
            std::stringstream ss(line);

            // Keep track of the current column index
            int colIdx = 0;

            // Extract each integer
            while (ss >> val) {

                // Add the current integer to the 'colIdx' column's values vector
                table.at(colIdx).second.push_back(val);

                // If the next token is a comma, ignore it and move on
                if (ss.peek() == ',') ss.ignore();

                // Increment the column index
                colIdx++;
            }
        }
        // Close file
        myFile.close();
    }

    int getRowSize() {
        return this->table.size();
    }

    int getColSize() {
        return this->table[0].second.size();
    }

    vector<float> getRow(int i) {
        return this->table[i].second;
    }

    string getRowSubject(int i) {
        return this->table[i].first;
    }

};


#endif /* TIMESERIES_H_ */