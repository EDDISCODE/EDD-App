/*
 * testUtils.h
 *
 *  Created on: Feb 8, 2014
 *      Author: cgs
 */

#ifndef TESTUTILS_H_
#define TESTUTILS_H_

// Put names of test images here for easy reference
enum TestImg{ELE, E=0, ELEPHANT=0, BALL};

void printImgInfo(Mat&);
void showImg(Mat&, char* wname="window", bool wait=true);
string testImg(TestImg);

#endif /* TESTUTILS_H_ */
