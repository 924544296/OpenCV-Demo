#include "functions.h"


int main()
{
	// train
	//std::string path = "D:\\data\\cheng_zhong\\data\\0_221train\\*.jpg";
	std::string path = "D:\\data\\cheng_zhong\\data\\347g\\*.jpg";
	double weight = 347.0;
	const int n = 1;
	double c1[n]{};
	double c2[n]{};

	Eigen::VectorXd x = polynomial_fit(path, weight, c1, c2, n);
	// 输出结果
	std::cout << "最小二乘解 x 是：\n" << x << std::endl;


	//// test
	////cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\0_221test\\10-16-44-191.jpg", 1);
	////cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\0_221train\\10-16-44-181.jpg", 1);	
	//cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\29g\\14-00-15-17.jpg", cv::IMREAD_GRAYSCALE);
	////cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\24g\\14-00-15-13.jpg", 1);
	//cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\67g\\14-00-15-28.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\8g\\14-00-15-39.jpg", cv::IMREAD_GRAYSCALE);
	////cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\15g\\14-00-15-29.jpg", 1);
	//cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\69g\\15-46-34-25.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\35g\\15-46-34-15.jpg", 1);
	cv::Mat image_test = cv::imread("D:\\data\\cheng_zhong\\data\\437g\\14-00-15-74.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat image_test = cv::Mat(512, 512, CV_8UC1, cv::Scalar(255));

	double weight_predict = polynomial_predict(image_test, n, x);
	std::cout << "预测重量: " << weight_predict << std::endl;


	return 0;
}