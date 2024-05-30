#include "OpenCv.h"

using namespace cv;
using namespace std;

VideoCapture cap(0);
Mat img;
Mat imgGray;
CascadeClassifier handCascade;
vector<Rect> hands;

int siggy1 = 255;
int siggy2 = 0;
int siggy3 = 0;

OpenCv::OpenCv()
{
}

OpenCv::~OpenCv()
{
}

void OpenCv::init() 
{
	handCascade.load("Resources/fist.xml");
	if (handCascade.empty()) { cout << "XML file not loaded" << endl; }

	// resolution decrease
	cap.set(CAP_PROP_FRAME_WIDTH, 640/2);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480/2);

}

void OpenCv::run()
{
	cap.read(img);
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	handCascade.detectMultiScale(imgGray, hands);

	for (int i = 0; i < hands.size(); i++)
	{
		Point center(hands[i].x + hands[i].width / 2, hands[i].y + hands[i].height / 2);
		rectangle(img, hands[i].tl(), hands[i].br(), Scalar(siggy1, siggy2, siggy3), 3);


		/// DoorButtonRight ///
		if (center.x < 100 && center.x > 10 && center.y < 470 && center.y > 280) {
			cout << "Door right button" << endl;
		}

		/// DoorButtonLeft ///
		if (center.x < 630 && center.x > 540 && center.y < 470 && center.y > 280) {
			cout << "Door left button" << endl;
		}

		/// CameraButton ///
		if (center.x < 470 && center.x > 160 && center.y < 460 && center.y > 390) {
			cout << "Camera button" << endl;
		}

		/// CameraViewButtonRight ///
		if (center.x < 620 && center.x > 550 && center.y < 340 && center.y > 100) {
			cout << "Cameraview right button" << endl;
		}

		/// CameraViewButtonLeft ///
		if (center.x < 90 && center.x > 20 && center.y < 340 && center.y > 100) {
			cout << "Cameraview left button" << endl;
		}

		/// CameraSwitchButton ///
		if (center.x < 360 && center.x > 280 && center.y < 280 && center.y > 200) {
			cout << "Cameraswitch button" << endl;
		}


		Mat handROI = imgGray(hands[i]);
	}

	

	////////////////////// DoorButtons(purple) //////////////////////
	rectangle(img, Point(10, 380), Point(100, 470), Scalar(255, 0, 255), 3);
	rectangle(img, Point(540, 380), Point(630, 470), Scalar(255, 0, 255), 3);

	////////////////////// CameraButton(red) //////////////////////
	rectangle(img, Point(160, 390), Point(470, 460), Scalar(0, 0, 255), 3);

	////////////////////// CameraViewButtons(green) //////////////////////
	rectangle(img, Point(20, 100), Point(90, 340), Scalar(0, 255, 0), 3);
	rectangle(img, Point(550, 100), Point(620, 340), Scalar(0, 255, 0), 3);

	////////////////////// CameraSwitchButton(blue) //////////////////////
	rectangle(img, Point(280, 200), Point(360, 280), Scalar(255, 0, 0), 3);

	flip(img, img, 1);

	imshow("HandDetection", img);
	waitKey(1);
}
