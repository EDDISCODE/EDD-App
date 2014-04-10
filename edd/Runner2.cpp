#include "Runner2.h"

int main() {
	Mat target = imread("/home/cgs/school/edd/test7.jpg");
	resizeTarget(target);
	cvtColor(target, target, CV_BGR2GRAY);

	vector<Rect> locs;
	findComparator(target, locs);
	Rect avgRect;
	if(locs.size() > 1) {
		getAvgRect(locs, avgRect);
	}
	else avgRect = locs[0];

	Mat templ = imread("/home/cgs/school/edd/testtmp1.jpg");
	resizeTemplate(templ, avgRect);
	process(templ, templ);


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
bool findComparator(Mat img, vector<Rect> locs, string classifierPath) {
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
void process(Mat in, Mat& out) {
	if(in.channels() > 1)
		cvtColor(in, in, CV_BGR2GRAY);
	Size blurSize;
	int xs, ys;
	xs = in.cols / 100;
	ys = in.rows / 100;
	if(xs % 2 == 0) xs++;
	if(ys % 2 == 0) ys++;
	blurSize = Size(xs, ys);
	GaussianBlur(in, out, blurSize,0, 0, 1);
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
bool getAvgRect(vector<Rect> rects, Rect& out) {
	if(rects.size() < 1) return false;
	int width = 0;
	int height = 0;
	for(int i = rects.size() - 1; i >= 0; i--) {
		width += rects[i].width;
		height += rects[i].height;
	}
	width /= rects.size();
	height /= rects.size();
	out = Rect();
	out.height = height;
	out.width = width;
	return true;

}
//Resize template according to target size
void resizeTemplate(Mat& templ, Rect comparator) {

}
