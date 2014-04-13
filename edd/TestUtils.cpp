/*
 * testUtils.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: cgs
 */

#include <iostream>
#include "TestUtils.h"
using namespace cv;

namespace testutils{
//Prints basic info about image
void imgInfo(const Mat& img){
	std::cout << "Type: " << img.type()
					<<"  Channels: " << img.channels()
					<< "   Depth:" << img.depth()
					<< std::endl;
}

// Displays image in new window
void showImg(Mat img, char* wname, bool wait){
	cvNamedWindow(wname, 1);
	imshow(wname, img);
	if(wait) waitKey(0);
}

//flags: 0- nothing after printing,
//1-end line after printing,
//2- space after printing
void printpt(const Point& p, int flags){
	std::cout << "(" << p.x << ", " << p.y << ")";
	if(flags == 1) std::cout << std::endl;
	else if(flags == 2) std::cout << " ";
}
}
