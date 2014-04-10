/*
 * Runner2.h
 *
 *  Created on: Apr 9, 2014
 *      Author: cgs
 */

#ifndef RUNNER2_H_
#define RUNNER2_H_

#include "cv.h"
#include "TestUtils.h"
using namespace cv;

void resizeTarget(Mat& img);
bool findComparator(Mat img, vector<Rect> locs,
					string classifierPath = "/home/cgs/code/edd/haarcascade_frontalface_alt2.xml");
void process(Mat in, Mat& out);
bool getAvgRect(vector<Rect> rects, Rect& out);
void resizeTemplate(Mat& templ, Rect comparator);
#endif /* RUNNER2_H_ */
