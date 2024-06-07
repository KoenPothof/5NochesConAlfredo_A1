#include "VisionComponent.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "GameManager.h"
#include <chrono>


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

chrono::steady_clock::time_point lastRightDoorToggle = chrono::steady_clock::now();
chrono::steady_clock::time_point lastLeftDoorToggle = chrono::steady_clock::now();

VisionComponent::VisionComponent()
{
}

VisionComponent::~VisionComponent()
{
}

void VisionComponent::init()
{
	handCascade.load("Resources/fist.xml");
	if (handCascade.empty()) { cout << "XML file not loaded" << endl; }

	// resolution decrease
	cap.set(CAP_PROP_FRAME_WIDTH, 640 / 2);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480 / 2);
}

void VisionComponent::update(float elapseTime)
{
	cap.read(img);

	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	handCascade.detectMultiScale(imgGray, hands);

	auto now = chrono::steady_clock::now();
	
	
	for (int i = 0; i < hands.size(); i++)
	{
		Point center(hands[i].x + hands[i].width / 2, hands[i].y + hands[i].height / 2);
		rectangle(img, hands[i].tl(), hands[i].br(), Scalar(siggy1, siggy2, siggy3), 3);


		/// DoorButtonRight ///
		if (center.x < 100 / 2 && center.x > 10 / 2 && center.y < 470 / 2 && center.y > 380 / 2) {
			if (chrono::duration_cast<chrono::seconds>(now - lastRightDoorToggle).count() >= 2) {
				cout << "Door right toggled" << endl;
				gameObject->gameManager->rightDoorToggle();
				lastRightDoorToggle = now;
			}
		}

		/// DoorButtonLeft ///
		if (center.x < 630 / 2 && center.x > 540 / 2 && center.y < 470 / 2 && center.y > 380 / 2) {
			if (chrono::duration_cast<chrono::seconds>(now - lastLeftDoorToggle).count() >= 2) {
				cout << "Door left toggled" << endl;
				gameObject->gameManager->leftDoorToggle();
				lastLeftDoorToggle = now;
			}
		}

		/// CameraButton ///
		if (center.x < 470 / 2 && center.x > 160 / 2 && center.y < 460 / 2 && center.y > 390 / 2) {
			//controlsComponent.controls(ControlsComponent::TOGGLECAMERAS);
			cout << "Camerasystem toggled" << endl;
		}

		/// CameraViewButtonLeft ///
		if (center.x < 620 / 2 && center.x > 550 / 2 && center.y < 340 / 2 && center.y > 100 / 2) {
			//controlsComponent.controls(ControlsComponent::LOOKLEFT);
			cout << "Camera to the left" << endl;
			try {
				gameObject->getComponent<CameraComponent>()->lookLeft();
			}
			catch (const std::exception& e) {
				cout << "CameraComponent not found" << endl;
			}
			
		}

		/// CameraViewButtonRight ///
		if (center.x < 90 / 2 && center.x > 20 / 2 && center.y < 340 / 2 && center.y > 100 / 2) {
			//controlsComponent.controls(ControlsComponent::LOOKRIGHT);
			cout << "Camera to the right" << endl;
			try {
				gameObject->getComponent<CameraComponent>()->lookRight();
			}
			catch (const std::exception& e) {
				cout << "CameraComponent not found" << endl;
			}
		}

		/// CameraSwitchButton ///
		if (center.x < 360 / 2 && center.x > 280 / 2 && center.y < 280 / 2 && center.y > 200 / 2) {
			//controlsComponent.controls(ControlsComponent::CAMERASWITCH);
			cout << "Camera switched" << endl;
		}


		Mat handROI = imgGray(hands[i]);
	}



	////////////////////// DoorButtons(purple) //////////////////////
	rectangle(img, Point(10 / 2, 380 / 2), Point(100 / 2, 470 / 2), Scalar(255, 0, 255), 3);
	rectangle(img, Point(540 / 2, 380 / 2), Point(630 / 2, 470 / 2), Scalar(255, 0, 255), 3);

	////////////////////// CameraButton(red) //////////////////////
	rectangle(img, Point(160 / 2, 390 / 2), Point(470 / 2, 460 / 2), Scalar(0, 0, 255), 3);

	////////////////////// CameraViewButtons(green) //////////////////////
	rectangle(img, Point(20 / 2, 100 / 2), Point(90 / 2, 340 / 2), Scalar(0, 255, 0), 3);
	rectangle(img, Point(550 / 2, 100 / 2), Point(620 / 2, 340 / 2), Scalar(0, 255, 0), 3);

	////////////////////// CameraSwitchButton(blue) //////////////////////
	rectangle(img, Point(280 / 2, 200 / 2), Point(360 / 2, 280 / 2), Scalar(255, 0, 0), 3);

	flip(img, img, 1);

	imshow("HandDetection", img);
	waitKey(1);
}

void VisionComponent::toggleRightDoor() 
{
	gameObject->gameManager->rightDoorToggle();
}

void VisionComponent::toggleLeftDoor()
{
	gameObject->gameManager->leftDoorToggle();
}