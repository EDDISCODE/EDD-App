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
#define TARGET_PATH "/home/cgs/school/edd/test13.jpg" // 1, 7, 10, 12, 13
#define SCALEXCARD (8/13.0) //1 //8/13 for ID
#define SCALEYCARD (6/18.0) //1 //6/18 for ID
#define TEMPL_PATH "/home/cgs/school/edd/testtmp3.jpg"
#define MAXDIM 1024.0
#define BLURDIVISOR 150
#define UPPERTHRESH 255
#define LOWERTHRESH 240
//for Segmentation only
#define TOPN 10 // !!!THROWS "COMMAND TERMINATED" WHEN >= 5!!!
#define DIVROWS 2
#define DIVCOLS 2
#define COVERFAC 2
//for main3 only
#define XDIV (3*target.rows/templ.rows)
#define YDIV (7*target.cols/templ.cols)

using namespace cv;


int main1();
int main2();
int main3();
int main4();

void resizeTarget(Mat& img);
bool findComparator(Mat img, vector<Rect>& locs,
					string classifierPath = "/home/cgs/code/edd/haarcascade_frontalface_alt2.xml");
void process(Mat in, Mat& out, Size blurSize = Size(0,0), bool isTempl = false);
Rect getAvgRect(vector<Rect> rects);
void resizeTemplate(Mat& templ, Rect comparator, double scaleX = SCALEXCARD, double scaleY = SCALEYCARD);
Size genBlurSize(Mat& img);
void dispLoc(Mat img, vector<Point> points);
void dispLoc(Mat img, vector<Rect> rects);
void distanceWeight(Mat& img, Rect comparator);
#endif /* RUNNER2_H_ */
