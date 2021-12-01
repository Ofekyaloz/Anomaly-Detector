cmake_minimum_required(VERSION 3.20)
project(The_Best_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(The_Best_Project main.cpp anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h SimpleAnomalyDetector.h testTImeSeries.cpp testTImeSeries.h SimpleAnomalyDetector.cpp timeseries.cpp timeseries.h minCircle.cpp)