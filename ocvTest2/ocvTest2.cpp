/*
 * ocvTest2.cpp
 *
 * FIND THE BALL AND DRAW A BOX AROUND IT
 *  Created on: Feb 8, 2014
 *      Author: cgs
 *
 *     Useful test images
 *     Elephant:	/home/cgs/school/edd/testimg.png
 *     Ball: 		/home/cgs/school/edd/testimg_bwBall.png
 *
 */


#include "cv.h"
#include <iostream>
#include "highgui.h"

using namespace cv;
#include "ocvTest2.h"
#include "testUtils.h"


int main(){
	Mat img;
	img = imread(testImg(ELEPHANT), 1);
	showImg(img);
	return 0;
}



