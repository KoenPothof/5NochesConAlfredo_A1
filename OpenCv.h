#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

class OpenCv
{
public:
	OpenCv();
	~OpenCv();
	void init();
	void run();
};

