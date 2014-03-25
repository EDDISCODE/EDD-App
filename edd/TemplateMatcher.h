/*
 * TemplateMatcher.h
 *
 *  Created on: Mar 13, 2014
 *      Author: cgs
 */

#ifndef TEMPLATEMATCHER_H_
#define TEMPLATEMATCHER_H_

#ifndef DEF_TEMP_SZ
#define DEF_TEMP_SZ 256.0
#endif

#ifndef DEF_TARG_SZ
#define DEF_TARG_SZ 1024.0
#endif

#include "TestUtils.h"

class TemplateMatcher {
private:
	Mat m_templ;
	Mat m_out;
	double m_scale;
	Point* m_max;
	Point* m_min;
	const int m_METHOD = 0;
	void process(Mat in, Mat out);
	void computeScale(string type);

public:
	TemplateMatcher();
	TemplateMatcher(Mat templ);
	TemplateMatcher(string templPath);
	void setTempl(Mat templ);
	void setTempl(string path);
	Point getMin();
	Point getMax();
	void run(Mat target, Rect faceRect);
};

#endif /* TEMPLATEMATCHER_H_ */
