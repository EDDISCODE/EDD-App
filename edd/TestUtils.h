/*
 * testUtils.h
 *
 *  Created on: Feb 8, 2014
 *      Author: cgs
 */

#ifndef TESTUTILS_H_
#define TESTUTILS_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

// Put names of test images here for easy reference
enum TestImg{ELE, E=0, ELEPHANT=0, OLD_BALL,
			BLK16_3, BLK256_3, BLK256_1, BALL,
			BLK256_3_2, CRECT};

string testImg(TestImg);

void imgInfo(const Mat&);
void showImg(Mat img, char* wname="window", bool wait=true);
void printpt(const Point&, int flags = 1);

#endif /* TESTUTILS_H_ */
