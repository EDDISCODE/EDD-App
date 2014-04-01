/*
 * TemplateMatcher.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: cgs
 */

#include "TemplateMatcher.h"

TemplateMatcher::TemplateMatcher() {
	init();
}

TemplateMatcher::TemplateMatcher(Mat templ) {
	init();
	setTempl(templ);
}

TemplateMatcher::TemplateMatcher(string templPath) {
	init();
	setTempl(templPath);
	showImg(m_templ); //FOR TESTING
}

//sets template: processes and resizes for decreased mem use
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
void TemplateMatcher::init() {
	m_out.data = NULL;
	m_templ.data = NULL;
	m_max = new Point();
	m_min = new Point();
	m_scaleX = 8.6/13.0;
	m_scaleY = 5.8 / 18.0;
}
//pull edges out of template or target before matching
void TemplateMatcher::process(Mat in, Mat& out) {
	if(in.channels() > 1)
		cvtColor(in, in, CV_BGR2GRAY);
	Size blurSize;
	int xs, ys;
	xs = 1 + in.cols / 150;
	ys = 1 + in.rows / 150;
	if(xs % 2 == 0) xs++;
	if(ys % 2 == 0) ys++;
	blurSize = Size(xs, ys);
	GaussianBlur(in, out, blurSize,0, 0, 1);
	Mat x, y;
	Scharr(out, x, 0, 1, 0);
	Scharr(out, y, 0, 0, 1);
	addWeighted(x, 0.75, y, 0.75, 0, out, -1);
	threshold(out, out, 185, 255, THRESH_TOZERO);
}

//Run matching; assign useful things to output
void TemplateMatcher::run(Mat target, Rect faceRect) {
	Mat processedTarg;
	process(target, processedTarg);
	showImg(processedTarg);
	Mat resizedTemp;
	Size tempSize = Size(faceRect.width * m_scaleX, faceRect.height * m_scaleY);
	resize(m_templ, resizedTemp, tempSize, 0, 0);
	matchTemplate(processedTarg, resizedTemp, m_out, CV_TM_SQDIFF);
	//Want find min with CV_TM_SQDIFF
	minMaxLoc(m_out, NULL, NULL, m_min, m_max);
	dispLoc(0, target);
}
//point of minimum value of output
Point TemplateMatcher::getMin() {
	return *m_min;
}
//point of maximum value of output
Point TemplateMatcher::getMax() {
	return *m_max;
}
//show where min or max is. 0 = min, 1 = max
void TemplateMatcher::dispLoc(int flags, Mat target) {
	if(flags == 0)
		circle(target, *m_min, 25, Scalar(0,0,255));
	else if(flags == 1)
		circle(target, *m_max, 25, Scalar(0,0,255));
	showImg(target, "test", true);
}
