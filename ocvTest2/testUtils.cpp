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
void printImgInfo(Mat& img){
	std::cout << "Type: " << img.type() <<"  Channels: " << img.channels()  << "   Depth:" << img.depth();
}

// Displays image in new window
void showImg(Mat& img, char* wname, bool wait){
	cvNamedWindow(wname, 1);
	imshow(wname, img);
	if(wait) waitKey(0);
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


