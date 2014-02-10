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
	img = imread(testImg(BALL256_3), 1);
	imgInfo(img);
	findCol(Scalar(200, 200, 200), img);
	showImg(img);
}

//locates color and draws a box around the blob
//target is BGR!!!
//NOTE DOESN'T SEEM TO WORK WITH CIRCLE. SOLVE FAST
void findCol(const Scalar& target, Mat& img){
	Point hits[img.rows*img.cols];
	int hitsInd = 0;
	if(img.channels() == 3){
		for(int i = img.rows - 1; i >= 0; i--){
			for( int j = img.cols - 1; j >= 0; j--){
				//compare values
				Vec3b px = img.at<Vec3b>(j, i);
				bool same = true;
				for(int k = 0; k < 3; k++){
					if(target.val[k] > px.val[k] ){
						same = false;
					}
				}
				if(same){
					hits[hitsInd] = Point(j, i);
					hitsInd++;
				}
			}
		}
	}
	else if(img.channels() == 1){
		for(int i = img.rows - 1; i >= 0; i--) {
			for(int j = img.cols -1 ; j >= 0; j--) {
				if(target.val[0] == (int)(img.at<uchar>(j,i)) ) {
					hits[hitsInd] = Point(j, i);
					hitsInd++;
				}
			}
		}
	}
	Point p1, p2;
	p1 = hits[hitsInd - 1];
	p2 = hits[500];
	printpt(p1);
	printpt(p2);
	std::cout << hitsInd;
	rectangle(img, p1, p2, Scalar(0,0,255));
}

