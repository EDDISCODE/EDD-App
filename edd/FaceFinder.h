/*
 * FaceFinder.h
 *
 *  Created on: Mar 3, 2014
 *      Author: cgs
 */

#ifndef FACEFINDER_H_
#define FACEFINDER_H_

#include "TestUtils.h"

using namespace cv;

class FaceFinder {
private:
	Mat m_img;
	CascadeClassifier m_cc;
	const std::string m_PATH = "/home/cgs/code/edd/haarcascade_frontalface_alt2.xml";
	// "../haarcascade_frontalface_alt2.xml";
	std::vector<Rect> m_locs;
public:
	FaceFinder();
	FaceFinder(Mat& img);
	FaceFinder(std::string imgpath);
	bool setTarget(std::string imgpath);
	std::vector<Rect> getLocs();
	bool run();
	void displayLocs();
	Size getAvgSize();
};

#endif /* FACEFINDER_H_ */
