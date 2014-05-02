#include "Segmentation.h"
namespace segmentation {
//Cuts image into ROIs
void divImg(Mat img, int rows, int cols, std::vector<Rect>& rois ) {
	assert(rows < img.rows && cols < img.cols && cols > 0 && rows > 0);
	int dx = img.cols/cols;
	int dy = img.rows/rows;
	//DEALS WITH MAIN BODY OF IMAGE
	for(int i = 0; i < img.rows - img.rows % dy; i += dy) { //might need img.rows-1
		for(int j = 0; j < img.cols - img.cols % dx; j += dx) {
			rois.push_back(Rect(Point(j, i), Size(dx, dy)));
		}
	}
	//DEALS WITH EXTRA AT THE BOTTOM
	if(img.rows % dy != 0) {
		for(int i = 0; i < img.cols - img.cols % dx; i += dx)
			rois.push_back(Rect(Point(i, img.rows-img.rows % dy),
											Size(dx, img.rows % dy)));
	}
	//DEALS WITH EXTRA AT RIGHT EDGE
	if(img.cols % dx != 0) {
		for(int i = 0; i < img.rows - img.rows % dy; i+=dy){
			rois.push_back(Rect(Point(img.cols-img.cols % dx, i),
									Size(img.cols % dx, dy)));
		}
	}
	//DEALS WITH EXTRA AT BOTTOM RIGHT SQUARE
	if(img.rows % dy != 0 && img.cols % dx != 0){
		rois.push_back(Rect(Point(img.cols-img.cols % dx, img.rows - img.rows % dy),
									Size(img.cols % dx, img.rows % dy)));
	}
}
//Computes adjacency matrix for matVec of ROIs
//Gets distance between 2 points
double getDist(cv::Point a, cv::Point b) {
	return std::sqrt(std::pow(a.x-b.x, 2) + std::pow(a.y-b.y, 2));
}
//returns a vector of row indices sorted by connectedness

Node::Node(Rect r) {
	region = r;
}

Graph::Graph(){
	nodes = std::vector<Node>();
}

Graph::Graph(std::vector<Rect> r){
	nodes = std::vector<Node>();
	for(int i = 0; i < r.size(); i++)
		nodes.push_back(Node(r[i]));
	computeAdj();
}

}
