#include "Runner.h"
#include "FaceFinder.h"
#include "TemplateMatcher.h"

int main() {
	Mat target = imread("/home/cgs/school/edd/test2.jpg");
	FaceFinder f = FaceFinder(target);
	f.run();
	f.displayLocs();
	Mat templ = imread("/home/cgs/school/edd/testtmp2.jpg");
	TemplateMatcher t = TemplateMatcher(templ);
	//t.run(target, f.getLocs()[0]);
	t.run(target, Rect_<int>(Point(0,0), Point(1,1)));
	return 0;
}
