#include "OpenCv.h"

using namespace cv;

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
	imshow("Image", img);
	waitKey(1);
}
