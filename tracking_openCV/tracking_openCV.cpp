#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\tracking.hpp"

int main() {

	cv::VideoCapture video(0);
	if (!video.isOpened())
	{
		return -1;
	}

	cv::Mat frame;

	// Tracker 
	cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
	video.read(frame);
	cv::Rect trackingBox = cv::selectROI(frame, false);
	tracker->init(frame, trackingBox);


	while (video.read(frame)) {

		if (tracker->update(frame, trackingBox)) 
		{
			cv::rectangle(frame, trackingBox, cv::Scalar(255, 0, 0), 2, 8);
		}

		cv::imshow("camera", frame);

		if (cv::waitKey(25) >= 0) 
		{
			break;
		}
	} 

	//clear
	video.release();
	cv::destroyAllWindows();

	return 0;

}