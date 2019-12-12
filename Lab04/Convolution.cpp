#include "Convolution.h"

vector<float> Convolution::GetKernel()
{
	return this->_kernel;
}

void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight)
{
	int i, size = kernel.size();
	this->_kernelHeight = kHeight;
	this->_kernelWidth = kWidth;
	this->_kernel.resize(size);

	for (i = 0; i < size; i++)
		this->_kernel[i] = kernel[i];
}

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage)
{
	if (this->_kernel.size() == 0 || sourceImage.data == NULL)
		return 1;

	int row, col, nRow, nCol, sum;
	nRow = sourceImage.rows;
	nCol = sourceImage.cols;

	int indexR, indexC, i, j, count, value;

	//Initialize dest matrix
	destinationImage = Mat(sourceImage.size(), CV_32FC1);

	//Do convolution
	for (row = 0; row < nRow; row++)
	{
		
		for (col = 0; col < nCol; col++)
		{
			sum = 0;
			count = 0;

			//Ilterate mask vector
			for (i = -(this->_kernelWidth/2); i <=(this->_kernelWidth/2); i++)
			{
				for (j = -(this->_kernelHeight/2); j <= (this->_kernelHeight/2); j++)
				{
					//Calculate the new index of (row, col) in neighboring
					indexR = row - i; 
					indexC = col - j;

					//if pixel out of boundaries, pixel = 0
					if ((indexR < 0 || indexR > nRow - 1) || (indexC < 0 || indexC > nCol - 1))
						value = 0;
					else
						value = sourceImage.at<uchar>(indexR, indexC);

					sum += this->_kernel[count] * value;
					count++;
				}
			}

			//Assign sum to dest pixel(row,col)
			destinationImage.at<float>(row, col) = sum;
		}
	}
	return 0;
}
