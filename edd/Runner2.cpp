#include "Runner2.h"

int main() {
	Mat target = imread("/home/cgs/school/edd/test1.jpg");
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
	Mat templ = imread("/home/cgs/school/edd/testtmp1.jpg");
	resizeTemplate(templ, avgRect);
	process(templ, templ, genBlurSize(target));

	Mat1f matcherOutput;
	Point* max;
	matchTemplate(target, templ, matcherOutput, CV_TM_CCORR);
	normalize(matcherOutput, matcherOutput, 1, 0, NORM_MINMAX, -1);
	minMaxLoc(matcherOutput, NULL, NULL, NULL, max);
	max->x += (templ.cols+1)/2;
	max->y += (templ.rows+1)/2;
	dispLoc(target, vector<Point>(1, *max));


}

//Scales image so that largest dimension is 1024 px
void resizeTarget(Mat& img) {
	if(img.cols > 1024 && img.cols > img.rows) {
		double scaleFac = 1024.0/img.cols;
		resize(img, img, Size(0,0), scaleFac, scaleFac);
	}
	else if(img.rows > 1024){
		double scaleFac = 1024.0/img.rows;
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
	cc.detectMultiScale(img, locs, 1.1, 3, 0, Size(128,128), Size(512,512));
	if(locs.size() < 1){
		std::cout << "NO FACES DETECTED" << std::endl;
		return false;
	}
	return true;
}
//Processing function for template and target
void process(Mat in, Mat& out, Size blurSize) {
	if(in.channels() > 1)
		cvtColor(in, in, CV_BGR2GRAY);
	if(blurSize.width <= 0 && blurSize.height <= 0)
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
	threshold(out, out, 235, 255, THRESH_TOZERO);
}
//Outputs a rectangle of average size
Rect getAvgRect(vector<Rect> rects) {
	if(rects.size() < 1) return rects[0];
	int width = 0;
	int height = 0;
	for(int i = rects.size() - 1; i >= 0; i--) {
		width += rects[i].width;
		height += rects[i].height;
	}
	width /= rects.size();
	height /= rects.size();
	Rect out = Rect();
	out.height = height;
	out.width = width;
	return out;

}
//Resize template according to target size
void resizeTemplate(Mat& templ, Rect comparator, double scaleX, double scaleY) {
	Size sz = comparator.size();
	sz.width *= scaleX;
	sz.height *= scaleY;
	resize(templ, templ, sz);
}
//Generates a blur size
Size genBlurSize(Mat& img) {
	Size sz = Size(img.cols / 100, img.rows / 100);
	if(sz.width % 2 == 0) sz.width++;
	if(sz.height % 2 == 0) sz.height++;
	return sz;
}

void dispLoc(Mat img, vector<Point> points) {
	if(img.channels() == 1)
		cvtColor(img, img, CV_GRAY2BGR);
	for(int i = 0; i < points.size(); i++)
		circle(img, points[i], 25, Scalar(0, 0, 255), 5);
	showImg(img);
}

void dispLoc(Mat img, vector<Rect> rects) {
	if(img.channels() == 1)
		cvtColor(img, img, CV_GRAY2BGR);
	for(int i = 0; i < rects.size(); i++){
		Rect r = rects[i];
		Point p1 = Point(r.x + r.width, r.y + r.height);
		Point p2 = Point(r.x, r.y);
		rectangle(img, p1, p2, Scalar(0,0,255), 2);
	}
	showImg(img);
}
