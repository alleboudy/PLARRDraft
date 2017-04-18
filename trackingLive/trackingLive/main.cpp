// Standard include files
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	// Set up tracker. 
	// Instead of MIL, you can also use 
	// BOOSTING, KCF, TLD, MEDIANFLOW or GOTURN  
	Ptr<Tracker> tracker = Tracker::create( "KCF" );
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened()) // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}



//	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
//	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	// Read video
	//VideoCapture video("c:\\ball.mp4");

	// Check video is open
	/*	if(!video.isOpened())
	{
	cout << "Could not read video file" << endl;
	return 1;
	}*/

	// Read first frame. 
	Mat frame;
	cap.read(frame);

	// Define an initial bounding box
	Rect2d bbox(25, 20, 150, 150);

	// Uncomment the line below if you 
	// want to choose the bounding box
	// bbox = selectROI(frame, false);

	// Initialize tracker with first frame and bounding box
	tracker->init(frame, bbox);

	while(cap.read(frame))
	{
		// Update tracking results
		tracker->update(frame, bbox);

		// Draw bounding box
		rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );

		// Display result
		imshow("Tracking", frame);
		int k = waitKey(1);
		if(k == 27) break;

	}

	return 0; 

}