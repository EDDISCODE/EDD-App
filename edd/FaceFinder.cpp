/*
 * FaceFinder.cpp
 *
 *  Created on: Mar 3, 2014
 *      Author: cgs
 */

#include <iostream>
#include "FaceFinder.h"

FaceFinder::FaceFinder() {
	m_cc = CascadeClassifier(m_PATH);
	m_img.data = NULL;
}

FaceFinder::FaceFinder(Mat& img) {
	m_cc = CascadeClassifier(m_PATH);
	m_img = img;
}

FaceFinder::FaceFinder(std::string imgpath) {
	m_cc = CascadeClassifier(m_PATH);
	setTarget(imgpath);
}

bool FaceFinder::setTarget(std::string imgpath) {
	m_img = imread(imgpath, 0);	//0 = return grayscale, >0 = 3 channel
	if(m_img.rows > 1000 || m_img.cols > 1500) {
		double scaleFac = std::min(1000.0/m_img.rows, 1500.0/m_img.cols);
		resize(m_img, m_img, Size(0,0), scaleFac, scaleFac);
	}
	if(m_img.data != NULL)
		return true;
	return false;
}

std::vector<Rect> FaceFinder::getLocs() {
	return m_locs;
}

bool FaceFinder::run() {
	if(m_img.data == NULL) return false;
	m_cc.detectMultiScale(m_img, m_locs, 1.1, 3, 0, Size(80,80), Size(300, 300));
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
	showImg(dispImg, "window", true);
}

Size FaceFinder::getAvgSize() {
	int width = 0;
	int height = 0;
	for(int i = m_locs.size() - 1; i >= 0; i--) {
		width += m_locs[i].width;
		height += m_locs[i].height;
	}
	width /= m_locs.size();
	height /= m_locs.size();
	return Size(width, height);
}
