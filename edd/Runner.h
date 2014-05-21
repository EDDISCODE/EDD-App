/*
 * Runner2.h
 *
 *  Created on: Apr 9, 2014
 *      Author: cgs
 */

#ifndef RUNNER2_H_
#define RUNNER2_H_

#include "TestUtils.h"
#include "Segmentation.h"

//Control panel
#define TARGET_PATH "/home/cgs/school/edd/test1.jpg"
#define TEMPL_PATH "/home/cgs/school/edd/testtmp2.jpg"
#define MAXDIM 1024.0
#define BLURDIVISOR 100 
#define UPPERTHRESH 255
#define LOWERTHRESH 240
//for Segmentation only
#define TOPN 5 // !!!THROWS "COMMAND TERMINATED" WHEN >= 5!!!
#define DIVROWS 2
#define DIVCOLS 2
#define COVERFAC 2

using namespace cv;


int main1();
int main2();

void resizeTarget(Mat& img);
bool findComparator(Mat img, vector<Rect>& locs,
					string classifierPath = "/home/cgs/code/edd/haarcascade_frontalface_alt2.xml");
void process(Mat in, Mat& out, Size blurSize = Size(0,0));
Rect getAvgRect(vector<Rect> rects);
void resizeTemplate(Mat& templ, Rect comparator, double scaleX = 8.6/13.0, double scaleY = 6.7 / 18.0);
Size genBlurSize(Mat& img);
void dispLoc(Mat img, vector<Point> points);
void dispLoc(Mat img, vector<Rect> rects);
void distanceWeight(Mat& img, Rect comparator);
#endif /* RUNNER2_H_ */
