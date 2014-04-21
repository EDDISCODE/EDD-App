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

#define MAXDIM 1024.0
#define BLURDIVISOR 200
#define UPPERTHRESH 255
#define LOWERTHRESH 240
using namespace cv;


void resizeTarget(Mat& img);
Mat targetRotAndComparator(Mat& img, vector<Rect>& locs); //DO NOT USE YET
bool findComparator(Mat img, vector<Rect>& locs,
					string classifierPath = "/home/cgs/code/edd/haarcascade_frontalface_alt2.xml");
void process(Mat in, Mat& out, Size blurSize = Size(0,0));
Rect getAvgRect(vector<Rect> rects);
void resizeTemplate(Mat& templ, Rect comparator, double scaleX = 8.6/13.0, double scaleY = 6.2 / 18.0);
Size genBlurSize(Mat& img);
void dispLoc(Mat img, vector<Point> points);
void dispLoc(Mat img, vector<Rect> rects);
void distanceWeight(Mat& img, Rect comparator);
#endif /* RUNNER2_H_ */
