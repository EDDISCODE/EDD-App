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
	const int m_METHOD = 0;
	float startScale;
	bool procTempl(Mat templ);
public:
	Point getLoc();
	bool setTempl(Mat templ);
	bool setTempl(string path);
};

#endif /* TEMPLATEMATCHER_H_ */
