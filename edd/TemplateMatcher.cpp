/*
 * TemplateMatcher.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: cgs
 */

#include "TemplateMatcher.h"

TemplateMatcher::TemplateMatcher() {
	m_out.data = NULL;
	m_templ.data = NULL;
	m_max = NULL;
	m_min = NULL;
}

TemplateMatcher::TemplateMatcher(Mat templ) {
	TemplateMatcher();
	setTempl(templ);
	showImg(m_templ); //FOR TESTING
}

TemplateMatcher::TemplateMatcher(string templPath) {
	TemplateMatcher();
	setTempl(templPath);
	showImg(m_templ); //FOR TESTING
}

//sets template
void TemplateMatcher::setTempl(string path) {
	m_templ = imread(path, 0); //Loads image as black and white
	float sclfacy = 256.0 / m_templ.rows;
	resize(m_templ, m_templ, Size(sclfacy * m_templ.cols, 256));
	process(m_templ, m_templ);
}
//sets template
void TemplateMatcher::setTempl(Mat templ) {
	cvtColor(templ, m_templ, CV_BGR2GRAY);
	float sclfacy = 256.0 / m_templ.rows;
	resize(m_templ, m_templ, Size(sclfacy * m_templ.cols, 256));
	process(m_templ, m_templ);
}
//pull edges out of template or target before matching
void TemplateMatcher::process(Mat in, Mat out) {
	Mat x, y;
	Size blurSize;
	int xs, ys;
	xs = 3 + in.cols / 150;
	ys = 3 + in.rows / 150;
	if(xs % 2 == 0) xs++;
	if(ys % 2 == 0) ys++;
	blurSize = Size(xs, ys);
	GaussianBlur(in, in, blurSize,0, 0, 1);
	Scharr(in, x, 0, 1, 0);
	Scharr(in, y, 0, 0, 1);
	addWeighted(x, 0.75, y, 0.75, 0, in, -1);
	threshold(in, out, 185, 255, THRESH_TOZERO);
}

//Run matching; assign useful things to output
void TemplateMatcher::run(Mat target) {
	Mat tempTarg;
	process(target, tempTarg);
	float sclfacy = 1024.0 / tempTarg.rows;
	resize(tempTarg, tempTarg, Size(sclfacy * tempTarg.cols, 1024), 0, 0, 1);
	matchTemplate(m_out, m_templ, m_out, CV_TM_SQDIFF);
	minMaxLoc(m_out, NULL, NULL, m_min, m_max);
}
//point of minimum value of output
Point TemplateMatcher::getMin() {
	return *m_min;
}
//point of maximum value of output
Point TemplateMatcher::getMax() {
	return *m_max;
}
