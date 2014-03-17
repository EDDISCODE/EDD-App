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
	Point m_max;
	Point m_min;
	const int m_METHOD = 0;
	float startScale;
public:
	TemplateMatcher(string targetPath = NULL, Mat* target = NULL);
	TemplateMatcher(Mat templ, string targetPath = NULL, Mat* target = NULL);
	TemplateMatcher(string path, string targetPath = NULL, Mat* target = NULL);
	void setTempl(Mat templ);
	void setTempl(string path);
	void templSize(Size sz);
	Point getMin();
	void run();
};

#endif /* TEMPLATEMATCHER_H_ */
