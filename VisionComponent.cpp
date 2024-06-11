#include "VisionComponent.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "SecurityCameraComponent.h"
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
chrono::steady_clock::time_point lastCameraToggle = chrono::steady_clock::now();

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
		if (center.x < 150 / 2 && center.x > 60 / 2 && center.y < 610 / 2 && center.y > 520 / 2) {
			if (chrono::duration_cast<chrono::seconds>(now - lastRightDoorToggle).count() >= 2) {
				cout << "Door right toggled" << endl;
				gameObject->gameManager->rightDoorToggle();
				lastRightDoorToggle = now;
			}
		}

		/// DoorButtonLeft ///
		if (center.x < 290 / 2 && center.x > 200 / 2 && center.y < 610 / 2 && center.y > 520 / 2) {
			if (chrono::duration_cast<chrono::seconds>(now - lastLeftDoorToggle).count() >= 2) {
				cout << "Door left toggled" << endl;
				gameObject->gameManager->leftDoorToggle();
				lastLeftDoorToggle = now;
			}
		}

		/// CameraSystemToggleButton ///
		if (center.x < 280 / 2 && center.x > 70 / 2 && center.y < 490 / 2 && center.y > 420 / 2) {
			if (chrono::duration_cast<chrono::seconds>(now - lastCameraToggle).count() >= 1.5) {
				cout << "Camerasystem toggled" << endl;
				gameObject->gameManager->toggleCameraSystem();
				lastCameraToggle = now;
			}
		}

		/// CameraViewButtonLeft ///
		if (center.x < 280 / 2 && center.x > 210 / 2 && center.y < 390 / 2 && center.y > 150 / 2) {
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
		if (center.x < 140 / 2 && center.x > 70 / 2 && center.y < 390 / 2 && center.y > 150 / 2) {
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
		if (center.x < 290 / 2 && center.x > 60 / 2 && center.y < 120 / 2 && center.y > 30 / 2) {
			//controlsComponent.controls(ControlsComponent::CAMERASWITCH)
			cout << "Camera switched" << endl;
			try {
				gameObject->getComponent<SecurityCameraComponent>()->switchCamera();
			}
			catch (const std::exception& e) {
				cout << "SecurityCameraComponent not found" << endl;
			}
			
		}


		Mat handROI = imgGray(hands[i]);
	}



	////////////////////// DoorButtons(purple) //////////////////////
	rectangle(img, Point(60 / 2, 520 / 2), Point(150 / 2, 610 / 2), Scalar(255, 0, 255), 3); // Right
	rectangle(img, Point(200 / 2, 520 / 2), Point(290 / 2, 610 / 2), Scalar(255, 0, 255), 3); // Left

	////////////////////// CameraButton(red) ////////////////////// 
	rectangle(img, Point(70 / 2, 420 / 2), Point(280 / 2, 490 / 2), Scalar(0, 0, 255), 3);

	////////////////////// CameraViewButtons(green) //////////////////////
	rectangle(img, Point(70 / 2, 150 / 2), Point(140 / 2, 390 / 2), Scalar(0, 255, 0), 3); // Right
	rectangle(img, Point(210 / 2, 150 / 2), Point(280 / 2, 390 / 2), Scalar(0, 255, 0), 3); // Left

	////////////////////// CameraSwitchButton(blue) //////////////////////
	rectangle(img, Point(60 / 2, 30 / 2), Point(290 / 2, 120 / 2), Scalar(255, 0, 0), 3);

	flip(img, img, 1);

	imshow("HandDetection", img);
	waitKey(1);
}