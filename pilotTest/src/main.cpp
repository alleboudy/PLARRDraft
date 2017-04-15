
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened()) // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	Mat frame;

	while (1)
	{
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video file" << endl;
			break;
		}

		for (size_t r = 0; r < frame.rows; r++)
		{
			for (size_t c = 0; c < frame.cols; c++)
			{
				frame.at<cv::Vec3b>(r, c)[0] = abs(255 - frame.at<cv::Vec3b>(r, c)[0]);
				frame.at<cv::Vec3b>(r, c)[1] = abs(255 - frame.at<cv::Vec3b>(r, c)[1]);
				frame.at<cv::Vec3b>(r, c)[2] = abs(255 - frame.at<cv::Vec3b>(r, c)[2]);

			}
		}
		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) //wait for �esc� key press for 30ms. If �esc� key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}