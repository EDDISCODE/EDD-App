/*
 * FaceFinder.cpp
 *
 *  Created on: Mar 3, 2014
 *      Author: cgs
 */

#include <iostream>
#include "testUtils.h"
#include "FaceFinder.h"


FaceFinder::FaceFinder() {
	m_cc = CascadeClassifier(m_PATH);
	m_img.data = NULL;
}

FaceFinder::FaceFinder(Mat& img) {
	m_cc = CascadeClassifier(m_PATH);
	m_img = img;
}

FaceFinder::FaceFinder(string imgpath) {
	m_cc = CascadeClassifier(m_PATH);
	setTarget(imgpath);
}

bool FaceFinder::setTarget(string imgpath) {
	m_img = imread(imgpath, 0);	//0 = return grayscale, >0 = 3 channel
	if(m_img.data != NULL)
		return true;
	return false;
}

vector<Rect> FaceFinder::getLocs() {
	return m_locs;
}

bool FaceFinder::run() {
	if(m_img.data == NULL) return false;
	m_cc.detectMultiScale(m_img, m_locs, 1.1, 3, 0, Size(20,20), Size(100, 100));
	return true;
}

void FaceFinder::displayLocs() {
	Mat dispImg = Mat(m_img);
	cvtColor(dispImg, dispImg, CV_GRAY2BGR);
	for(int i = m_locs.size() - 1; i >= 0; i--) {
		Rect r = m_locs[i];
		Point p1 = Point(r.x + r.width, r.y + r.height);
		Point p2 = Point(r.x, r.y);
		rectangle(dispImg, p1, p2, Scalar(0,0,255), 2);
	}
	showImg(dispImg, "window");
}
