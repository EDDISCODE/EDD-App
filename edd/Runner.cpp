#include "Runner.h"
#include "FaceFinder.h"
#include "TemplateMatcher.h"

int main() {
	Mat target = imread("/home/cgs/school/edd/test6.jpg");
	if(target.cols > 1024) {
		double scaleFac = 1024.0/target.cols;
		resize(target, target, Size(0,0), scaleFac, scaleFac);
	}
	else if(target.rows > 1024){
		double scaleFac = 1024.0/target.rows;
		resize(target, target, Size(0,0), scaleFac, scaleFac);
	}

	FaceFinder f = FaceFinder(target);
	f.run();
	f.displayLocs();

	Mat templ = imread("/home/cgs/school/edd/testtmp1.jpg");
	TemplateMatcher t = TemplateMatcher(templ);
	t.run(target, f.getAvgRect());
	return 0;
}

