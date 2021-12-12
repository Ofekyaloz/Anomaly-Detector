#include "CLI.h"


CLI::CLI(DefaultIO* dio) {

}



void CLI::start(){
    dio->write("Welcome to the Anomaly Detection Server. \n"
               "Please choose an option: \n"
               "1. upload a time series csv file \n"
               "2. algorithm settings \n"
               "3. detect anomalies \n"
               "4. display results \n"
               "5. upload anomalies and analyze results \n"
               "6. exit");

    string choice = dio->read();

//    switch (choice) {
//        case "1":
//
//            break;
//        case "1":
//
//            break;
//        case "1":
//
//            break;
//        case "1":
//
//            break;
//        case "1":
//
//            break;
//        default:
//
//            break;
//    }
}


CLI::~CLI() {
}

