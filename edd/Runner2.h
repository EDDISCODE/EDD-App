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
bool findComparator(Mat img, vector<Rect>& locs,
					string classifierPath = "/home/cgs/code/edd/haarcascade_frontalface_alt2.xml");
void process(Mat in, Mat& out, Size blurSize = Size(0,0));
Rect getAvgRect(vector<Rect> rects);
void resizeTemplate(Mat& templ, Rect comparator, double scaleX = 8.6/13.0, double scaleY = 5.8 / 18.0);
Size genBlurSize(Mat& img);
void dispLoc(Mat img, vector<Point> points);
void dispLoc(Mat img, vector<Rect> rects);
#endif /* RUNNER2_H_ */
