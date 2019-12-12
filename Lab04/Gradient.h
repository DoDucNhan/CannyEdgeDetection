#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Convolution.h"
#include <vector>

class Gradient
{
	void gradientOperator(const Mat& src, Mat& Gx, Mat &Gy, int xArr[], int yArr[]);
	Mat magnitudeCalculation(const Mat& Gx, const Mat& Gy);
	Mat slopeCalculation(const Mat& Gx, const Mat& Gy);

public:
	/*
	Hàm tính toán cường độ và độ dốc của ảnh thông qua toán tử gradient (chỉ tính với kernel 3x3)
	sourceImage: ảnh input
	magnitude: ma trận cường độ
	slope: ma trận độ dốc
	method: phương pháp detect
		1: Sobel
		2: Prewitt
	Hàm trả về
		0: nếu tính toán thành công
		1: nếu tính toán thất bại (không đọc được ảnh input,...)
	*/
	int getMagnitudeAndSlope(const Mat& sourceIamge, Mat& magnitude, Mat& slope, int method);

	Gradient() {};
	~Gradient() {};
};

