/*
 * testUtils.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: cgs
 */

#include "cv.h"
#include <iostream>
#include "highgui.h"

using namespace cv;
#include "testUtils.h"


//Prints basic info about image
void imgInfo(const Mat& img){
	std::cout << "Type: " << img.type()
			<<"  Channels: " << img.channels()
			<< "   Depth:" << img.depth()
			<< std::endl;
}

// Displays image in new window
void showImg(Mat& img, char* wname, bool wait){
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
 //return path of named TestImg
string testImg(TestImg name){
	string path;
	switch(name){
	case 0:
		path = "/home/cgs/school/edd/testimg.png";
		break;
	case 1:
		path = "/home/cgs/school/edd/testimg_bwBall.png";
		break;
	case 2:
		path = "/home/cgs/school/edd/testimg_16x16blocks.jpg";
		break;
	case 3:
		path = "/home/cgs/school/edd/testimg_256x256-8UC3-block.jpg";
		break;
	case 4:
			path = "/home/cgs/school/edd/testimg_256x256-8UC1-block.jpg";
			break;
	case 5:
		path = "/home/cgs/school/edd/testimg_256x256-8UC3-ball.jpg";
		break;
	default:
		try {
			if(path.empty()) throw 1;
		}
		catch(int e) {
			std::cout <<"Image does not exist." << std::endl;
		}
	}
	return path;
}
