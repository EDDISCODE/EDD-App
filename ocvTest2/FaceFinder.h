/*
 * FaceFinder.h
 *
 *  Created on: Mar 3, 2014
 *      Author: cgs
 */

#ifndef FACEFINDER_H_
#define FACEFINDER_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

class FaceFinder {
private:
	Mat m_img;
	CascadeClassifier m_cc;
	const string m_PATH = "/home/cgs/code/haarcascade_frontalface_alt2.xml";
	// "../haarcascade_frontalface_alt2.xml";
	vector<Rect> m_locs;
public:
	FaceFinder();
	FaceFinder(Mat& img);
	FaceFinder(string imgpath);
	bool setTarget(string imgpath);
	vector<Rect> getLocs();
	bool run();
	void displayLocs();
};

#endif /* FACEFINDER_H_ */
