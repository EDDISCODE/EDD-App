/*
 * testUtils.h
 *
 *  Created on: Feb 8, 2014
 *      Author: cgs
 */

#ifndef TESTUTILS_H_
#define TESTUTILS_H_

// Put names of test images here for easy reference
enum TestImg{ELE, E=0, ELEPHANT=0, OLD_BALL, BLK16_3, BLK256_3, BLK256_1, BALL256_3};

void imgInfo(const Mat&);
void showImg(Mat&, char* wname="window", bool wait=true);
string testImg(TestImg);
void printpt(const Point&, int flags = 1);

#endif /* TESTUTILS_H_ */
