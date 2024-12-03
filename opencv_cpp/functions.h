#pragma once


#include <iostream>
#include <opencv2/opencv.hpp>
#include "Eigen/Dense"
#include <cmath>


//void get_roi(cv::Mat image, cv::Mat& thresh, cv::Mat& roi);
void get_roi(cv::Mat image, cv::Mat& mask, cv::Mat& roi, int thresh, int type);


Eigen::VectorXd polynomial_fit(std::string path, double weight, double* c1, double* c2, int n);


double polynomial_predict(cv::Mat image, int n, Eigen::VectorXd x);