#include "Runner.h"
#include "Segmentation.h"

int main() {
	//main1();
	main2();
	return 0;
}
//standard main
int main1() {
	string targetPath = "/home/cgs/school/edd/test1.jpg";
	string templPath = "/home/cgs/school/edd/testtmp1.jpg";

	Mat target = imread(targetPath);
	resizeTarget(target);
	cvtColor(target, target, CV_BGR2GRAY);

	vector<Rect> locs;
	findComparator(target, locs);
	dispLoc(target, locs);
	Rect avgRect;
	if(locs.size() > 1) {
		avgRect = getAvgRect(locs);
	}
	else avgRect = locs[0];

	process(target, target);
	testutils::showImg(target);
	Mat templ = imread(templPath);
	resizeTemplate(templ, avgRect);
	process(templ, templ, genBlurSize(target));
	testutils::showImg(templ);

	Mat1f matcherOutput;
	Point* max = new Point();
	matchTemplate(target, templ, matcherOutput, CV_TM_CCORR);
	normalize(matcherOutput, matcherOutput, 1, 0, NORM_MINMAX, -1);
	testutils::showImg(matcherOutput);
	minMaxLoc(matcherOutput, NULL, NULL, NULL, max);
	max->x += (templ.cols+1)/2;
	max->y += (templ.rows+1)/2;

	target = imread(targetPath);
	resizeTarget(target);
	dispLoc(target, vector<Point>(1, *max));
	return 0;
}
//segmented main
int main2() {
	using namespace segmentation;
	string targetPath = "/home/cgs/school/edd/test1.jpg";
	string templPath = "/home/cgs/school/edd/testtmp1.jpg";

	Mat target = imread(targetPath);
	resizeTarget(target);
	cvtColor(target, target, CV_BGR2GRAY);

	vector<Rect> locs;
	findComparator(target, locs);
	dispLoc(target, locs);
	Rect avgRect;
	if(locs.size() > 1) {
		avgRect = getAvgRect(locs);
	}
	else avgRect = locs[0];

	process(target, target);
	testutils::showImg(target);
	Mat templ = imread(templPath);
	resizeTemplate(templ, avgRect);
	process(templ, templ);
	testutils::showImg(templ);

	matVec parts; //= std::vector< std::vector<Mat> >();
	divImg(templ, 2, 2, parts);
//	adjacencyMat adj = genAdjacencyMat(parts, parts[0][0].rows/2);
//	std::vector<int> sortedList = sortByConnections(adj);

	return 0;
}
//Scales image so that largest dimension is MAXDIM px
void resizeTarget(Mat& img) {
	if(img.cols > MAXDIM && img.cols > img.rows) {
		double scaleFac = MAXDIM/img.cols;
		resize(img, img, Size(0,0), scaleFac, scaleFac);
	}
	else if(img.rows > MAXDIM){
		double scaleFac = MAXDIM/img.rows;
		resize(img, img, Size(0,0), scaleFac, scaleFac);
	}
}
//Locates instances of comparator item
bool findComparator(Mat img, vector<Rect>& locs, string classifierPath) {
	if(img.data == NULL) {
		std::cout << "IMAGE DATA == NULL";
		return false;
	}
	CascadeClassifier cc = CascadeClassifier(classifierPath);
	equalizeHist(img, img);
	cc.detectMultiScale(img, locs, 1.1, 3, 0, Size(img.cols/16, img.rows/16), Size(img.cols/2, img.rows/2));
	if(locs.size() <= 0){
		std::cout << "NO FACES DETECTED" << std::endl;
		return false;
	}
	return true;
}
//Processing function for template and img
void process(Mat in, Mat& out, Size blurSize) {
	if(in.channels() > 1)
		cvtColor(in, in, CV_BGR2GRAY);
	if(blurSize.width <= 0 || blurSize.height <= 0)
		blurSize = genBlurSize(in);
	else {
		if(blurSize.width % 2 == 0) blurSize.width++;
		if(blurSize.height % 2 == 0) blurSize.height++;
	}
	GaussianBlur(in, out, blurSize, 0, 0, 1);
	Mat x, y, x1, y1;
	Scharr(out, x, 0, 1, 0, 1);
	Scharr(out, y, 0, 0, 1, 1);
	Scharr(out, x1, 0, 1, 0, -1);
	Scharr(out, y1, 0, 0, 1, -1);
	double addWeight = 1;
	addWeighted(x, addWeight, y, addWeight, 0, x, -1);
	addWeighted(x1, addWeight, y1, addWeight, 0, x1, -1);
	addWeighted(x, addWeight, x1, addWeight, 0, out, -1);
	threshold(out, out, LOWERTHRESH, UPPERTHRESH, THRESH_TOZERO);
//	Mat structure = getStructuringElement(MORPH_ELLIPSE, Size(3, 5));
//	erode(out, out, structure);

}
//Outputs a rectangle of average size
Rect getAvgRect(vector<Rect> rects) {
	if(rects.size() < 1)
		std::cout << "NO FACE RECTANGLES" << std::endl;
	if(rects.size() <= 1) return rects[0];
	int width = 0;
	int height = 0;
	for(int i = rects.size() - 1; i >= 0; i--) {
		width += rects[i].width;
		height += rects[i].height;
	}
	width /= rects.size();
	height /= rects.size();
	int xpos = 0;
	int ypos = 0;
	for(int i = rects.size() - 1; i >= 0; i--) {
		xpos += rects[i].x;
		ypos += rects[i].y;
	}
	xpos /= rects.size();
	ypos /= rects.size();
	Rect out = Rect();
	out.height = height;
	out.width = width;
	out.x = xpos;
	out.y = ypos;
	return out;

}
//Resize template according to img size
void resizeTemplate(Mat& templ, Rect comparator, double scaleX, double scaleY) {
	Size sz = comparator.size();
	sz.width *= scaleX;
	sz.height *= scaleY;
	resize(templ, templ, sz);
}
//Generates a blur size
Size genBlurSize(Mat& img) {
	Size sz = Size(img.cols / BLURDIVISOR, img.rows / BLURDIVISOR);
	if(sz.width % 2 == 0) sz.width++;
	if(sz.height % 2 == 0) sz.height++;
	return sz;
}
//Displays locations of points
void dispLoc(Mat img, vector<Point> points) {
	if(img.channels() == 1)
		cvtColor(img, img, CV_GRAY2BGR);
	for(int i = 0; i < points.size(); i++)
		rectangle(img, points[i], points[i]+Point(20, 20), Scalar(0,0,255), 3);
	testutils::showImg(img);
}
//Displays the rectangles
void dispLoc(Mat img, vector<Rect> rects) {
	if(img.channels() == 1)
		cvtColor(img, img, CV_GRAY2BGR);
	for(int i = 0; i < rects.size(); i++){
		Rect r = rects[i];
		Point p1 = Point(r.x + r.width, r.y + r.height);
		Point p2 = Point(r.x, r.y);
		rectangle(img, p1, p2, Scalar(0,0,255), 2);
	}
	testutils::showImg(img);
}
//Weights things based on distance from the vertical line running through the comparator
void distanceWeight(Mat& img, Rect comparator){
	if(img.channels() > 1)
		std::cout << "TOO MANY CHANNELS" << std::endl;
	//Iterate over pixels, subtract k*distance from line from each
}
