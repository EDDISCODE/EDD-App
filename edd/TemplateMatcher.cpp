/*
 * TemplateMatcher.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: cgs
 */

#include "TemplateMatcher.h"

TemplateMatcher::TemplateMatcher(string targetPath, Mat* target) {
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

TemplateMatcher::TemplateMatcher(Mat templ, string targetPath, Mat* target) {
	TemplateMatcher(targetPath, target);
	setTempl(templ);
}

TemplateMatcher::TemplateMatcher(string path, string targetPath, Mat* target) {
	TemplateMatcher(targetPath, target);
	setTempl(path);
}

void TemplateMatcher::setTempl(string path) {
	m_templ = imread(path, 1);
}

void TemplateMatcher::setTempl(Mat templ) {
	m_templ = templ;
}

void TemplateMatcher::templSize(Size sz) {
	resize(m_templ, m_templ, sz);
}

void run() {

}
