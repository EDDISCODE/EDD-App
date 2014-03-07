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
	//img = imread(testImg(BLK256_3), 1);
	img = imread(testImg(OLD_BALL), 1);
	imgInfo(img);
	findCol(Scalar(255, 255, 255), img);
	showImg(img);
}

//locates color and draws a box around the blob
//target is BGR!!!
void findCol(const Scalar& target, Mat& img){
	Point hits[img.rows*img.cols];
	int hitsInd = 0;
	if(img.channels() == 3){
		Point pt;
		for(int i = 0; i < img.rows; i++){
			for( int j = 0; j < img.cols; j++){
				pt = Point(j,i);
				Vec3b px = img.at<Vec3b>(pt);
				bool same = true;
				for(int k = 0; k < 3; k++){
					if(target.val[k] != px.val[k] ){
						same = false;
					}
			}

				if(same){
					hits[hitsInd] = pt;
					hitsInd++;
					printpt(pt);
				}
			}
		}
	}
	else std::cout << "ERROR: invalid channels" <<std::endl;

	if(hitsInd > 0) {
		int avgX = 0;
		for(int i = hitsInd-1; i >= 0; i--)
			avgX += hits[i].x;
		avgX /= hitsInd;
		int avgY = 0;
		for(int i = hitsInd-1; i >= 0; i--)
			avgY += hits[i].y;
		avgY /= hitsInd;

		Point avgP(avgX, avgY);
		Point p1, p2;
		int offset = 35;
		p1 = Point(avgP.x - offset, avgP.y -offset);
		p2 = Point(avgP.x + offset, avgP.y + offset);
		std::cout << hitsInd <<std::endl;
		printpt(avgP);
		rectangle(img, p1, p2, Scalar(0,0,255));
		circle(img, avgP, 3, Scalar(0,0,255));
	}
}

