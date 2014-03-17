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
	Point* m_max;
	Point* m_min;
	const int m_METHOD = 0;
	float startScale;
	Size m_templSize;

public:
	TemplateMatcher(string targetPath = NULL, Mat* target = NULL, Size templSize = Size(50,50));
	TemplateMatcher(Mat templ, string targetPath = NULL, Mat* target = NULL, Size templSize= Size(50,50));
	TemplateMatcher(string path, string targetPath = NULL, Mat* target = NULL, Size templSize= Size(50,50));
	void setTempl(Mat templ);
	void setTempl(string path);
	Point getMin();
	Point getMax();
	void run();
};

#endif /* TEMPLATEMATCHER_H_ */
