#include "CannyEdgeDetector.h"

void main()
{
	Mat source = imread("E:\\house.jpg", IMREAD_UNCHANGED);
	Mat destination;
	if (source.data == NULL)
	{
		cerr << "Cannot read image!!!" << endl;
		return;
	}

	//GaussianBlur(source, source, Size(11, 11), BORDER_DEFAULT);

	namedWindow("Input Image");
	imshow("Input Image", source);

	
	CannyEdgeDetector ced(30, 90);
	ced.Apply(source, destination);

	namedWindow("Output Image");
	imshow("Output Image", destination);
	//imwrite("E:\\hoicham.png", destination);
	waitKey(0);
}

//int main(int argc, char* argv[])
//{
//	Mat source = imread(argv[2], IMREAD_UNCHANGED);
//	Mat destination;
//
//	if (source.data == NULL)
//	{
//		cerr << "Cannot read image!!!\n";
//		return 1;
//	}
//
//	namedWindow("Input Image");
//	imshow("Input Image", source);
//
//	if (argc == 6)
//	{
//		float param1, param2;
//		param1 = stof(argv[4]);
//		param2 = stof(argv[5]);
//		CannyEdgeDetector CED(param1, param2);
//		int check;
//		if (argv[1] == "--canny")
//			check = CED.Apply(source, destination);
//		else
//		{
//			cerr << "Error: Invalid arguments\n";
//			return 1;
//		}
//
//		if (check == 0)
//		{
//			namedWindow("Output Image");
//			imshow("Output Image", destination);
//			bool checkWrite = imwrite(argv[3], destination);
//			if (!checkWrite)
//			{
//				cerr << "Cannot save image!!!\n";
//				return 1;
//			}
//		}
//		else
//		{
//			cerr << "Something went wrong!!!\n";
//			return 1;
//		}
//	}
//	else {
//		cout << "Error: Invalid arguments\n";
//		return 1;
//	}
//
//	waitKey(0);
//	return 0;
//}