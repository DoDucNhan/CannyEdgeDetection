#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Gradient.h" 

using namespace cv;
class CannyEdgeDetector
{
	//ngưỡng dưới
	int _lowThreshold = 0;
	//ngưỡng trên
	int _highThreshold = 0;
	Mat nonMaxSuppression(const Mat& magnitude, const Mat& slope);
	Mat doubleThreshold(const Mat& src);
	Mat Hysteresis(const Mat& src);


public:
	/*
		Hàm áp dụng thuật toán Canny để phát hiện biên cạnh
		- srcImage: ảnh input
		- dstImage: ảnh kết quả
		Hàm trả về
			1: nếu detect thành công
			0: nếu detect không thành công
	*/


	int Apply(const Mat& srcImage, Mat& dstImage);

	CannyEdgeDetector(int lowThreshold, int hightThreshold) 
	{
		this->_lowThreshold = lowThreshold;
		this->_highThreshold = hightThreshold;
	};
	~CannyEdgeDetector() {};
};

