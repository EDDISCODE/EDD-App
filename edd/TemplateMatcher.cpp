/*
 * TemplateMatcher.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: cgs
 */

#include "TemplateMatcher.h"

TemplateMatcher::TemplateMatcher(string targetPath, Mat* target, Size templSize) {
	m_out.data = NULL;
	m_templ.data = NULL;
	startScale = 1;
	if(targetPath.length() > 0)
		m_target = imread(targetPath, 0);
	else if(target->data != NULL)
		m_target = *target;
	else
		m_target.data = NULL;
}

TemplateMatcher::TemplateMatcher(Mat templ, string targetPath, Mat* target, Size templSize) {
	TemplateMatcher(targetPath, target, templSize);
	setTempl(templ);
}

TemplateMatcher::TemplateMatcher(string path, string targetPath, Mat* target, Size templSize) {
	TemplateMatcher(targetPath, target, templSize);
	setTempl(path);
}

void TemplateMatcher::setTempl(string path) {
	m_templ = imread(path, 1);
	resize(m_templ, m_templ, m_templSize);
}

void TemplateMatcher::setTempl(Mat templ) {
	m_templ = templ;
	resize(m_templ, m_templ, m_templSize);
}


void TemplateMatcher::run() {
	matchTemplate(m_target, m_templ, m_out, CV_TM_SQDIFF);
	minMaxLoc(m_out, NULL, NULL, m_min, m_max);
}

Point TemplateMatcher::getMin() {
	return *m_min;
}

Point TemplateMatcher::getMax() {
	return *m_max;
}
