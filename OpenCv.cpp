#include "OpenCv.h"

using namespace cv;
using namespace std;

VideoCapture cap(0);
Mat img;

OpenCv::OpenCv()
{
}

OpenCv::~OpenCv()
{
}

void OpenCv::run()
{
	cap.read(img);

	Mat imgGray;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	CascadeClassifier handCascade;
	handCascade.load("Resources/fist.xml");

	if (handCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> hands;
	handCascade.detectMultiScale(imgGray, hands);

	for (int i = 0; i < hands.size(); i++)
	{
		Point center(hands[i].x + hands[i].width / 2, hands[i].y + hands[i].height / 2);
		rectangle(img, hands[i].tl(), hands[i].br(), Scalar(255, 0, 255), 3);
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
