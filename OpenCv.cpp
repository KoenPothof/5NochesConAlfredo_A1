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

	CascadeClassifier handCascade;
	handCascade.load("Resources/palm.xml");

	if (handCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> hands;
	handCascade.detectMultiScale(img, hands, 2, 10);

	for (int i = 0; i < hands.size(); i++)
	{
		rectangle(img, hands[i].tl(), hands[i].br(), Scalar(255, 0, 255), 3);
	}

	rectangle(img, Point(10, 10), Point(100, 100), Scalar(255, 0, 255), 3);

	////////////////////// DoorButton(purple) //////////////////////
	rectangle(img, Point(10, 380), Point(100, 470), Scalar(255, 0, 255), 3);
	rectangle(img, Point(540, 380), Point(630, 470), Scalar(255, 0, 255), 3);

	////////////////////// CameraButton(red) //////////////////////
	rectangle(img, Point(160, 390), Point(470, 460), Scalar(0, 0, 255), 3);


	flip(img, img, 1);

	imshow("Image", img);
	waitKey(1);
}
