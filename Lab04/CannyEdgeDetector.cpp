#include "CannyEdgeDetector.h"

Mat CannyEdgeDetector::nonMaxSuppression(const Mat& magnitude, const Mat& slope)
{
	Mat result = magnitude.clone();
	int row, col, nRow, nCol;
	nRow = magnitude.rows;
	nCol = magnitude.cols;
	float q, r;

	for (row = 1; row < nRow - 1; row++)
	{
		for (col = 1; col < nCol - 1; col++)
		{
			q = r = 255;
			if (slope.at<uchar>(row, col) == 0) //angle 0 --> pixel right and left
			{
				q = magnitude.at<float>(row, col + 1);
				r = magnitude.at<float>(row, col - 1);
			}
			else if (slope.at<uchar>(row, col) == 45) //angle 45 --> pixel above_left and bottom_right
			{
				q = magnitude.at<float>(row + 1, col - 1);
				r = magnitude.at<float>(row - 1, col + 1);
			}
			else if (slope.at<uchar>(row, col) == 90) //angle 90 --> pixel above and bottom
			{
				q = magnitude.at<float>(row + 1, col);
				r = magnitude.at<float>(row - 1, col);
			}
			else if (slope.at<uchar>(row, col) == 135) //angle 135 --> pixel above_right and bottom_left
			{
				q = magnitude.at<float>(row - 1, col - 1);
				r = magnitude.at<float>(row + 1, col + 1);
			}

			if (magnitude.at<float>(row, col) >= q && magnitude.at<float>(row, col) >= r)
				result.at<float>(row, col) = magnitude.at<float>(row, col);
			else
				result.at<float>(row, col) = 0;
		}
	}

	return result;
}

Mat CannyEdgeDetector::doubleThreshold(const Mat& src)
{
	Mat result = Mat::zeros(src.size(), CV_8UC1);

	int row, col, nRow, nCol;
	nRow = src.rows;
	nCol = src.cols;
	float q, r;

	for (row = 0; row < nRow; row++)
	{
		for (col = 0; col < nCol; col++)
		{
			if (src.at<float>(row, col) >= this->_highThreshold)
				result.at<uchar>(row, col) = 255; //strong pixel
			else if (src.at<float>(row,col) < this->_highThreshold && src.at<float>(row,col) >= this->_lowThreshold)
				result.at<uchar>(row, col) = 25; //weak pixel
		}
	}
	return result;
}

Mat CannyEdgeDetector::Hysteresis(const Mat& src)
{
	Mat result = src.clone();

	int row, col, nRow, nCol;
	nRow = src.rows;
	nCol = src.cols;
	float q, r;

	for (row = 1; row < nRow - 1; row++)
	{
		for (col = 1; col < nCol - 1; col++)
		{
			if (src.at<uchar>(row,col) == 25) //if pixel = weak
			{
				//if has at least 1 strong pixel around --> weak become strong, else weak become non-relevant
				if ((src.at<uchar>(row + 1, col - 1) == 255) || (src.at<uchar>(row + 1, col) == 255) || (src.at<uchar>(row + 1, col + 1) == 255) || (src.at<uchar>(row, col - 1) == 255) 
					|| (src.at<uchar>(row, col + 1) == 255) || (src.at<uchar>(row - 1, col - 1) == 255) || (src.at<uchar>(row - 1, col) == 255) or (src.at<uchar>(row - 1, col + 1) == 255))
					result.at<uchar>(row, col) = 255;
				else
					result.at<uchar>(row, col) = 0;
			}
		}
	}

	return result;
}

int CannyEdgeDetector::Apply(const Mat& srcImage, Mat& dstImage)
{
	if (srcImage.data == NULL)
		return 1;

	Mat src;
	if (srcImage.channels() > 1)
		cvtColor(srcImage, src, COLOR_RGB2GRAY);
	else
		src = srcImage.clone();

	//Noise reduction
	GaussianBlur(src, dstImage, Size(5, 5), BORDER_DEFAULT); //gaussian blur with kernel 5x5

	//Gradient calculation
	Mat magnitude, slope;
	Gradient gradient;
	gradient.getMagnitudeAndSlope(dstImage, magnitude, slope, 1);

	//Non-maximum suppression
	dstImage = nonMaxSuppression(magnitude, slope);

	//Double threshold
	dstImage = doubleThreshold(dstImage);

	//Edge Tracking by Hysteresis
	dstImage = Hysteresis(dstImage);

	return 0;
}
