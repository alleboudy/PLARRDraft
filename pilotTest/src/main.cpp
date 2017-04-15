#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	cout << "hahaha" << endl;
	Mat image;
	image = imread("c:\\me.jpg", 1);
	if (!image.data)
	{
		printf("No image data \n");
		return -1;
	}
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	system("pause");
	return 0;
}
