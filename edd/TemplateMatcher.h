/*
 * TemplateMatcher.h
 *
 *  Created on: Mar 13, 2014
 *      Author: cgs
 */

#ifndef TEMPLATEMATCHER_H_
#define TEMPLATEMATCHER_H_

#include "TestUtils.h"

class TemplateMatcher {
private:
	Mat m_templ;
	Mat m_out;
	Mat m_target;
	const int m_METHOD = 0;
	float startScale;
public:
	TemplateMatcher(string targetPath = NULL, Mat* target = NULL);
	TemplateMatcher(Mat templ, string targetPath = NULL, Mat* target = NULL);
	TemplateMatcher(string path, string targetPath = NULL, Mat* target = NULL);
	Point getLoc();
	void setTempl(Mat templ);
	void setTempl(string path);
	void run(Mat target);
	void templSize(Size sz);
};

#endif /* TEMPLATEMATCHER_H_ */
