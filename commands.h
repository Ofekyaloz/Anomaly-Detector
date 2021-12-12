

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

    // you may add additional methods here

    void readToFile(string fileName) {
        ofstream out(fileName);
        string data = "";

        while (data != "Done.") {
            data = read();
            out << data << endl;
        }
        out.close();
    }

};

// you may add here helper classes


// you may edit this class
class Command{
protected:
    DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
};

// implement here your command classes
class UploadCsv: public Command{

public:
    UploadCsv(DefaultIO* dio): Command(dio) {};

    virtual void execute() override {
        dio->write("Please upload your local train CSV file.\n");
        dio->readToFile("trainCSV");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readToFile("testCSV");
        dio->write("Upload complete.\n");
    }
};


class ThresholdSettings: public Command{
    ThresholdSettings(DefaultIO* dio): Command(dio) {};

    virtual void execute() override {
        dio->write("The current correlation threshold is \n");

        float* threshold;
        dio->read(threshold);

    }
};

class RunDetect: public Command{

};

class DisplayResults: public Command{

};

class AnalyzeResults: public Command{

};

class Exit: public Command{

};

#endif /* COMMANDS_H_ */
