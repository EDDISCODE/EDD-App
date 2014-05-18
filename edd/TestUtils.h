/*
 * testUtils.h
 *
 *  Created on: Feb 8, 2014
 *      Author: cgs
 */

#ifndef TESTUTILS_H_
#define TESTUTILS_H_

#include "cv.h"
#include "opencv.hpp"
using namespace cv;

namespace testutils {
	void imgInfo(const Mat&);
	void showImg(Mat img, char* wname="window", bool wait=true);
	void printpt(const Point&, int flags = 1);
}

#endif /* TESTUTILS_H_ */
