#include "Runner.h"
#include "FaceFinder.h"
#include "TemplateMatcher.h"

int main() {
//	FaceFinder f = FaceFinder("/home/cgs/school/edd/card6.jpg");
//	f.run();
//	f.displayLocs();
	TemplateMatcher t = TemplateMatcher("/home/cgs/school/edd/card6.jpg");
	return 0;
}
