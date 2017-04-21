#pragma once
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class cvMat2HDC
{
private:
	cv::Mat mat;
	HDC hdc;
	int posx;
	int posy;
public:
	cvMat2HDC();
	cvMat2HDC(IplImage*, HDC);
	cvMat2HDC(cv::Mat&, HDC);
	~cvMat2HDC();
	void setMat(IplImage*);
	void setMat(cv::Mat&);
	void setHDC();
	void setHDC(HDC);
	void setRendPos(int, int);
	void flip();
	void scale(int);
	void save(const std::string&);
	void convert();
	void load(const std::string&);
	cv::Mat getMat() const;
	HDC getHDC() const;
	void releaseHDC();
};
