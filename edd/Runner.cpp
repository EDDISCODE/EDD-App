#include "Runner.h"
#include "FaceFinder.h"

int main() {
	FaceFinder f = FaceFinder("/home/cgs/school/edd/head1.jpg");
	f.run();
	f.displayLocs();
	return 0;
}
