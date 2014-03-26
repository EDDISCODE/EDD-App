#include "Runner.h"
#include "FaceFinder.h"
#include "TemplateMatcher.h"

int main() {
	Mat target = imread("/home/cgs/school/edd/test6.jpg");
	FaceFinder f = FaceFinder("/home/cgs/school/edd/test6.jpg");
	f.run();
	//f.displayLocs();
	Mat tp = imread("/home/cgs/school/edd/testTemplate1.jpg");
	TemplateMatcher t = TemplateMatcher(tp);
	t.run(target, f.getLocs()[0]);
	return 0;
}
