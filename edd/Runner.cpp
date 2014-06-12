#include "Runner.h"

int main() {
	//main1();
//	main2();
	main3();
	//main4();
	return 0;
}
//standard main
int main1() {
	string targetPath = TARGET_PATH;
	string templPath = TEMPL_PATH;

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

	process(target, target, genBlurSize(target));
	testutils::showImg(target);
	Mat templ = imread(templPath);
	resizeTemplate(templ, avgRect);
	process(templ, templ, genBlurSize(target));
	testutils::showImg(templ);

	Mat1f matcherOutput;
	Point* max = new Point();
	matchTemplate(target, templ, matcherOutput, CV_TM_CCORR);
	normalize(matcherOutput, matcherOutput, 1, 0, NORM_MINMAX, -1);
	//testutils::showImg(matcherOutput);
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
	string targetPath = TARGET_PATH;
	string templPath = TEMPL_PATH; 

	Mat target = imread(targetPath);
	resizeTarget(target);
	cvtColor(target, target, CV_BGR2GRAY);

	std::vector<Rect> locs;
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
	 
	std::cout << "generating template graph \n";
	//generating template graph
	vector<Rect> parts;
	divImg(templ, DIVROWS, DIVCOLS, parts);
	Graph templGraph = Graph(parts, -1);
	
	std::cout << "searching for regions \n";
	//search for each region, taking top three location matches from each
	std::vector<std::vector<Point> > matches = std::vector<std::vector<Point> >(DIVROWS*DIVCOLS);
	for(int i = 0; i < matches.size(); i++) {
		Mat1f matcherOutput;
		matchTemplate(target, Mat(templ, templGraph[i].region), matcherOutput, CV_TM_CCORR);
		normalize(matcherOutput, matcherOutput, 1, 0, NORM_MINMAX, -1);
		for(int j = 0; j < TOPN; j++) {
			Point* max = new Point();
			minMaxLoc(matcherOutput, NULL, NULL, NULL, max);
			circle(matcherOutput, *max, COVERFAC*std::max(templGraph[i].height(), templGraph[i].width()), Scalar(0,0,0), -1);
			max->x += (templ.cols+1)/2;
			max->y += (templ.rows+1)/2;
			matches[i].push_back(*max);
			//testutils::showImg(matcherOutput);
		}
	}
	
	std::cout << "showing matches \n";
	//show matches
	std::vector<Point> ms = std::vector<Point>();	
	for(int i = 0; i < matches.size(); i++) {
		for(int j = 0; j < TOPN; j++)
			ms.push_back(matches[i][j]);	
	}
	dispLoc(target, ms);

	std::cout << "making combinations \n";
	//make combinations 
	int numCombos = pow(TOPN, DIVCOLS * DIVROWS); 
	std::cout << numCombos << "\n";
	std::vector<Graph> graphs = std::vector<Graph>(numCombos);
	BaseNCounter b = BaseNCounter(TOPN, matches.size(), numCombos);
	for(int i = 0; i < numCombos; i++) { 
		std::vector<Node> tempNodes = std::vector<Node>();
		for(int k = 0; k < matches.size(); k++)
			tempNodes.push_back(Node(matches[k][ b[k] ]));
		graphs[i] = Graph(tempNodes, templGraph.genMax());
		b.incr(); 
	}

	std::cout << "Done with combinations" << "\n";
	std::cout << "Finding best match \n";

	//find best match
	Graph& best = graphs[0];
	int bestInd = 0;
	bool okay = false;
	while(!okay) { 
		int bestSim;
		Graph& best = graphs[0];
		for(int i = 1; i <graphs.size(); i++){ 
			int similarity = compareGraph(templGraph, graphs[i]);
			if(bestSim > similarity) {
				best= graphs[i];
				bestInd = i;
				bestSim = similarity;
			}
		}
		okay = checkGraph(best, std::max(templ.rows, templ.cols), 0); //PROBLEM HERE
		if(!okay){
			std::cout << "checking" << bestInd << "\n" ;
			graphs.erase(graphs.begin() + bestInd); 
		}
	}
	
	std::cout << "Found best match \n";
	std::cout << "Displaying best graph points \n";

	//display best graph points
	std::vector<Point> bestGraphPoints = std::vector<Point>();
	for(int i = 0; i < best.size(); i++) 
		bestGraphPoints.push_back(best[i].location());
	dispLoc(target, bestGraphPoints);

	std::cout << "Best graph points displayed \n";
	std::cout << "Finding and displaying avg point \n";
	
	std::vector<Point> result = std::vector<Point>();
	Point avg = Point(0,0);
	for(int i = 0; i < bestGraphPoints.size(); i++)
		avg += bestGraphPoints[i];
	avg.x = avg.x /  bestGraphPoints.size();
	avg.y = avg.y / bestGraphPoints.size();
	result.push_back(avg);
	dispLoc(target, result);

	std::cout << "Best match avg displayed \n";

	return 0;
}

int main3() {
	using namespace segmentation;
	string targetPath = TARGET_PATH;
	string templPath = TEMPL_PATH; 

	Mat target = imread(targetPath);
	resizeTarget(target);
	cvtColor(target, target, CV_BGR2GRAY);

	std::vector<Rect> locs;
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
	
	std::cout << avgRect.width << ", " <<avgRect.height;
	resizeTemplate(templ, avgRect);
	process(templ, templ, genBlurSize(target), true);		
	testutils::showImg(templ);
	 
	std::cout << "generating template graph \n";
	//generating template graph
	vector<Rect> parts;
	divImg(templ, DIVROWS, DIVCOLS, parts);
	Graph templGraph = Graph(parts, -1);
	
	std::cout << "searching for regions \n";
	//search for each region, taking top n location matches from each
	Rect headRect = Rect(Point(avgRect.x, avgRect.y), Size((int)(avgRect.width*1.2), (int)(avgRect.height*1.2)));
	std::vector<std::vector<Point> > matches = std::vector<std::vector<Point> >(DIVROWS*DIVCOLS);
	for(int i = 0; i < matches.size(); i++) {
		Mat1f matcherOutput;
		matchTemplate(target, Mat(templ, templGraph[i].region), matcherOutput, CV_TM_CCORR);
		normalize(matcherOutput, matcherOutput, 1, 0, NORM_MINMAX, -1);
		for(int j = 0; j < TOPN; j++) {
			Point* max = new Point();
			minMaxLoc(matcherOutput, NULL, NULL, NULL, max);
			circle(matcherOutput, *max, COVERFAC*std::max(templGraph[i].height(), templGraph[i].width()), Scalar(0,0,0), -1);
			max->x += (templ.cols+1)/2;
			max->y += (templ.rows+1)/2;
			if(headRect.contains(*max))
				--j;
			else
				matches[i].push_back(*max);
		}
	}
	
	std::cout << "showing matches \n";
	//show matches
	std::vector<Point> ms = std::vector<Point>();	
	for(int i = 0; i < matches.size(); i++) {
		for(int j = 0; j < TOPN; j++)
			ms.push_back(matches[i][j]);	
	}
	dispLoc(target, ms);

	std::cout << "finding best \n";
	//find place with most matches
	cv::Rect *slider;
	int xincr = target.rows/XDIV ;
	int yincr = target.cols/YDIV ;
	std::vector<int> sliderCounts;
	for(int i = 0; i < YDIV; i++) {
		for(int ii = 0; ii < XDIV; ii++) {
			int count = 0;
			slider = new cv::Rect(Point(ii*xincr, i*yincr), Size(xincr, yincr));
			for(int j = 0; j < matches.size(); j++) {
				for(int k = 0; k < TOPN; k++) {
					if(slider->contains(matches[j][k]) && !(avgRect.contains(matches[j][k])))
							count++;
				}	
			}
			sliderCounts.push_back(count);
		}
	}

	//find max count
	int maxCount = 0;
	int bestInd = 0;
	for(int i = 0; i < sliderCounts.size(); i++) {
		if(sliderCounts[i] > maxCount) {
			maxCount = sliderCounts[i];
			bestInd = i;
		}
	}

	std::cout << "Showing best  \n";
	//best rect
	cv::Rect *best = new Rect(Point(xincr*(bestInd % XDIV),yincr*(bestInd / YDIV)), Size(xincr, yincr));
	std::vector<cv::Rect> bestR = std::vector<cv::Rect>();
	bestR.push_back(*best);
	dispLoc(target, bestR);


	

	return 0;
}

int main4() {
	string targetPath = TARGET_PATH;
	string templPath = TEMPL_PATH;

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

	process(target, target, genBlurSize(target));
	testutils::showImg(target);
	Mat templ = imread(templPath);
	resizeTemplate(templ, avgRect);
	process(templ, templ, genBlurSize(target));
	testutils::showImg(templ);
	
	Rect headRect = Rect(Point(avgRect.x, avgRect.y), Size((int)(avgRect.width*1.2), (int)(avgRect.height*1.2)));

	Mat1f matcherOutput;
	Point* max = new Point();
	matchTemplate(target, templ, matcherOutput, CV_TM_CCORR);
	normalize(matcherOutput, matcherOutput, 1, 0, NORM_MINMAX, -1);

	//find matches
	std::vector<Point> matches = std::vector<Point>();
	for(int j = 0; j < 100; j++) {
		Point* max = new Point();
		minMaxLoc(matcherOutput, NULL, NULL, NULL, max);
		circle(matcherOutput, *max, COVERFAC*templ.rows*.5, Scalar(0,0,0), -1);
		max->x += (templ.cols+1)/2;
		max->y += (templ.rows+1)/2;
		if(headRect.contains(*max))
			--j;
		else
			matches.push_back(*max);
		//if(j%10 == 0)
		//testutils::showImg(matcherOutput);
	}

	std::cout << "showing matches \n";
	//show matches
	std::vector<Point> ms = std::vector<Point>();	
	for(int i = 0; i < matches.size(); i++) {
			ms.push_back(matches[i]);	
	}
	dispLoc(target, ms);

	
	cv::Rect *slider;
	int xincr = target.rows/XDIV - 1;
	int yincr = target.cols/YDIV - 1;
	std::vector<int> sliderCounts;
	for(int i = 0; i < XDIV; i++) {
		for(int ii = 0; ii < YDIV; ii++) {
			int count = 0;
			slider = new cv::Rect(Point(i*xincr, ii*yincr), Size(xincr, yincr));
			for(int j = 0; j < matches.size(); j++) {
				if(slider->contains(matches[j]) && !(avgRect.contains(matches[j])))
					count++;
			}	
			sliderCounts.push_back(count);
		}
	}
	

	//find max count
	int maxCount = 0;
	int bestInd = 0;
	for(int i = 0; i < sliderCounts.size(); i++) {
		if(sliderCounts[i] > maxCount) {
			maxCount = sliderCounts[i];
			bestInd = i;
		}
	}

	//best rect
	cv::Rect *best = new Rect(Point(xincr*(bestInd / XDIV), yincr*(bestInd % YDIV)), Size(xincr, yincr));
	std::vector<cv::Rect> bestR = std::vector<cv::Rect>();
	bestR.push_back(*best);
	dispLoc(target, bestR);
	
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
void process(Mat in, Mat& out, Size blurSize, bool isTempl) {
	if(in.channels() > 1)
		cvtColor(in, in, CV_BGR2GRAY);
	if(blurSize.width <= 0 || blurSize.height <= 0)
		blurSize = genBlurSize(in);
	else {
		if(blurSize.width % 2 == 0) blurSize.width++;
		if(blurSize.height % 2 == 0) blurSize.height++;
	}
	GaussianBlur(in, out, blurSize, 0, 0, 1);

	if(isTempl) {
		//GaussianBlur(out, out,Size(blurSize.width*2+1, blurSize.height*2+1), 0, 0, 1);
	}

	Laplacian(in, out, 0, 11);
	Mat structure = getStructuringElement(MORPH_ELLIPSE, Size(2, 4));
	erode(out, out, structure);
	Mat structure1 = getStructuringElement(MORPH_ELLIPSE, Size(4, 2));
	erode(out, out, structure1);
	threshold(out, out, LOWERTHRESH, UPPERTHRESH, THRESH_TOZERO);

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
		rectangle(img, points[i], points[i]+Point(10, 10), Scalar(0,255,0), 3);
	testutils::showImg(img);
	static int counter = 100;
	counter++;
	std::stringstream s;
	s<< counter << ".jpg";
	imwrite(s.str() , img);
}
//Displays the rectangles
void dispLoc(Mat img, vector<Rect> rects) {
	if(img.channels() == 1)
		cvtColor(img, img, CV_GRAY2BGR);

	for(int i = 0; i < rects.size(); i++){
		Rect r = rects[i];
		Point p1 = Point(r.x + r.width, r.y + r.height);
		Point p2 = Point(r.x, r.y);
		rectangle(img, p1, p2, Scalar(0,0,255), (int)(img.rows*0.005)+2);
	}
	testutils::showImg(img);
	static int counter = 0;
	counter++;
	std::stringstream s;
	s<< counter << ".jpg";
	imwrite(s.str() , img);
}
//Weights things based on distance from the vertical line running through the comparator
void distanceWeight(Mat& img, Rect comparator){
	if(img.channels() > 1)
		std::cout << "TOO MANY CHANNELS" << std::endl;
	//Iterate over pixels, subtract k*distance from line from each
}
