#include "Runner.h"
#include "FaceFinder.h"
#include "TemplateMatcher.h"

int main() {
//	FaceFinder f = FaceFinder("/home/cgs/school/edd/card6.jpg");
//	f.run();
//	f.displayLocs();
	Mat tp = imread("/home/cgs/school/edd/card6.jpg");
	TemplateMatcher t = TemplateMatcher(tp);
	TemplateMatcher t2 = TemplateMatcher("/home/cgs/school/edd/card6.jpg");
	return 0;
}
