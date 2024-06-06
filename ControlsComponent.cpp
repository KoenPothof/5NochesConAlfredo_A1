#include "ControlsComponent.h"
#include "GameObject.h"
#include <iostream>
using namespace std;

//CameraComponent cameraComponent;;

ControlsComponent::ControlsComponent()
{
	//cameraComponent->getComponent<CameraComponent>()->lookLeft();

	

}

ControlsComponent::~ControlsComponent()
{
}

void ControlsComponent::controls(const CONTROLS control)
{
	switch (control)
	{
	case DOORLEFT:
		cout << "Door left button" << endl;
		break;

	case DOORRIGHT:
		cout << "Door right button" << endl;
		break;

	case LOOKLEFT:
		cout << "Look left button" << endl;
		//CameraComponent::lookLeft();
		gameObject->getComponent<CameraComponent>()->lookLeft();
		break;

	case LOOKRIGHT:
		cout << "Look right button" << endl;
		//CameraComponent::lookRight();
		gameObject->getComponent<CameraComponent>()->lookRight();
		break;

	case CAMERASWITCH:
		cout << "Cameraswitch button" << endl;
		break;

	case TOGGLECAMERAS:
		cout << "Toggle cameras button" << endl;
		break;
	}
}
