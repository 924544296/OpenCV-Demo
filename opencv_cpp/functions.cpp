#include "functions.h"


//void get_roi(cv::Mat image, cv::Mat& thresh, cv::Mat& roi)
//{
//	//
//	cv::threshold(image, thresh, 250, 255, cv::THRESH_BINARY_INV);
//	thresh.convertTo(thresh, CV_64F, 1.0 / 255.0);
//	//cv::imshow("thresh", thresh);
//	//cv::waitKey(0);
//	//
//	image.convertTo(image, CV_64F, 1.0 / 255.0);
//	//image.convertTo(image, CV_64F);
//	//
//	cv::multiply(image, thresh, roi);
//}


void get_roi(cv::Mat image, cv::Mat& mask, cv::Mat& roi, int thresh, int type)
{
	//
	cv::threshold(image, mask, thresh, 255, type); // cv::THRESH_BINARY_INV
	mask.convertTo(mask, CV_64F, 1.0 / 255.0);
	//cv::imshow("mask", mask);
	//cv::waitKey(0);
	//
	//image.convertTo(image, CV_64F, 1.0 / 255.0);
	image.convertTo(image, CV_64F);
	//
	cv::multiply(image, mask, roi);
}


Eigen::VectorXd polynomial_fit(std::string path, double weight, double* c1, double* c2, int n)
{
	// read images
	std::vector<cv::Mat> images;
	std::vector<cv::String> fn;
	cv::glob(path, fn, false);
	for (int i = 0; i < fn.size(); i++) 
	{
		images.push_back(cv::imread(fn[i], cv::IMREAD_GRAYSCALE));
	}
	// calculate coefficients
	//Eigen::MatrixXd A(images.size() * 2, n);
	//Eigen::VectorXd b(images.size() * 2);
	Eigen::MatrixXd A(images.size(), n);
	Eigen::VectorXd b(images.size());
	for (int i = 0; i < images.size(); i++)
	{
		cv::Mat image =  255 - images[i];
		//calculate(image, n, c);
		cv::Mat mask, roi, mask_inv, roi_inv, roi_i, roi_inv_i;
		//get_roi(image, mask, roi);
		get_roi(image.clone(), mask, roi, 5, cv::THRESH_BINARY);
		get_roi(image.clone(), mask_inv, roi_inv, 5, cv::THRESH_BINARY_INV);
		//cv::imshow("image", image);
		//cv::imshow("mask", mask);
		//cv::imshow("mask_inv", mask_inv);
		//cv::waitKey(0);
		//get_roi(image, mask, roi, 250, cv::THRESH_BINARY_INV);
		//get_roi(image, mask_inv, roi_inv, 250, cv::THRESH_BINARY);
		//c1[0] = cv::sum(mask)[0];
		//c2[0] = cv::sum(mask_inv)[0];
		//std::cout << "j: 0" << ",  cv::sum(thresh)[0] = " << cv::sum(mask)[0] << std::endl;
		//std::cout << "j: 0" << ",  cv::sum(thresh)[0] = " << cv::sum(mask_inv)[0] << std::endl;
		for (int j = 0; j < n; j++)
		{
			cv::pow(image, j+1, roi_i);
			c1[j] = cv::sum(roi_i)[0];
			cv::pow(roi_inv, j+1, roi_inv_i);
			c2[j] = cv::sum(roi_inv_i)[0];
			std::cout << "j: " << j << ",  cv::sum(roi_i)[0] = " << cv::sum(roi_i)[0] << std::endl;
			//std::cout << "j: " << j << ",  cv::sum(roi_inv_i)[0] = " << cv::sum(roi_inv_i)[0] << std::endl;
		}
		//A.row(i*2).segment(0, n) = Eigen::Map<Eigen::RowVectorXd>(c1, n);
		//b(i*2) = weight;
		//A.row(i * 2+1).segment(0, n) = Eigen::Map<Eigen::RowVectorXd>(c2, n);
		//b(i * 2+1) = 0;
		A.row(i).segment(0, n) = Eigen::Map<Eigen::RowVectorXd>(c1, n);
		b(i) = weight;
	}
	//std::cout << "A=" << A << std::endl;
	//std::cout << "b=" << b << std::endl;
	//Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
	//Eigen::VectorXd x = A.fullPivLu().solve(b);
	//Eigen::VectorXd x = A.completeOrthogonalDecomposition().solve(b);
	Eigen::VectorXd x = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);
	//Eigen::VectorXd x = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

	return x;
}


double polynomial_predict(cv::Mat image, int n, Eigen::VectorXd x)
{
	//
	image = 255 - image;
	cv::Mat mask, roi, mask_inv, roi_inv, roi_i, roi_inv_i;
	//get_roi(image, mask, roi);
	get_roi(image.clone(), mask, roi, 5, cv::THRESH_BINARY);
	get_roi(image.clone(), mask_inv, roi_inv, 5, cv::THRESH_BINARY_INV);
	//
	//double weight_predict = cv::sum(mask)[0] * x(0);
	double weight_predict = 0.0;
	//std::cout << "cv::sum(thresh)[0] * x(0) = " << cv::sum(mask)[0] * x(0) << std::endl;
	for (int i = 0; i < n; i++)
	{
		cv::pow(image, i+1, roi_i);
		weight_predict += cv::sum(roi_i)[0] * x(i);
		std::cout << "cv::sum(image_i)[0] * x(i) = " << cv::sum(roi_i)[0] * x(i) << std::endl;
	}

	return weight_predict;
}