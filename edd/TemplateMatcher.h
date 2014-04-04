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
	Mat1f m_out;
	double m_scaleX;
	double m_scaleY;
	Point* m_max;
	Point* m_min;
	void process(Mat in, Mat& out);
	void computeScale(string type);
	void init();

public:
	TemplateMatcher();
	TemplateMatcher(Mat templ);
	TemplateMatcher(string templPath);
	void setTempl(Mat templ);
	void setTempl(string path);
	Point getMin();
	Point getMax();
	void run(Mat target, Rect faceRect);
	void dispLoc(int flags, Mat target);
};

#endif /* TEMPLATEMATCHER_H_ */
