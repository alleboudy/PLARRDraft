// Standard include files
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;


//returns the boundary box
 Rect2d detectCircle(Mat frame)
{
	Mat src_gray;
	//imshow("src frame",src);

	/// Convert it to gray
	cvtColor( frame, src_gray, CV_BGR2GRAY );

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );


	//imshow("current frame",src_gray);
	//int k = waitKey();

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 2, src_gray.rows/4, 200, 100);

	/// Draw the circles detected
	/*for( size_t i = 0; i < circles.size(); i++ )
	{
	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	int radius = cvRound(circles[i][2]);
	// circle center
	circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
	// circle outline
	circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}*/
	Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
	int radius = cvRound(circles[0][2]);



	return Rect2d(center.x-radius,center.y-radius,radius*2,radius*2);
	/*	
	delete &circles;
	delete &center;
	delete &radius;
	delete &src_gray;*/


}

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
	//detect the object here and create the boundary box



	//Rect2d bbox =detectCircle(frame);


	Mat src_gray;
	//imshow("src frame",src);

	/// Convert it to gray
	cvtColor( frame, src_gray, CV_BGR2GRAY );

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );


	//imshow("current frame",src_gray);
	//int k = waitKey();

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 2, src_gray.rows/4, 200, 100);

	/// Draw the circles detected
	/*for( size_t i = 0; i < circles.size(); i++ )
	{
	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	int radius = cvRound(circles[i][2]);
	// circle center
	circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
	// circle outline
	circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}*/
	Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
	int radius = cvRound(circles[0][2]);



	 Rect2d bbox(center.x-radius,center.y-radius,radius*2,radius*2);




	// Define an initial bounding box
	//Rect2d bbox(25, 20, 150, 150);
	//auto bbox = detectObject(frame);
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