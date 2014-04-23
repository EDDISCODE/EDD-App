#include "Segmentation.h"
namespace segmentation {
//Cuts image into ROIs
void divImg(Mat img, int rows, int cols, matVec& rois) {
	int dx = img.cols/cols;
	int dy = img.rows/rows;

	for(int i = 0; i < img.rows; i += dy){
		rois.push_back(vector<Mat>());
		for(int j = 0; j < img.cols; j += dx){
			rois[i].push_back(Mat(img, Rect(Point(j, i), Point(j+dx, i+dy))));
		}
	}
}
//Computes adjacency matrix for matVec of ROIs
adjacencyMat genAdjacencyMat(matVec rois){
	adjacencyMat adj = std::vector<std::vector<bool> >(0); //rows of adj
	int dx = rois[0][0].cols;
	int dy = rois[0][0].rows;

	for(int i = 0; i < rois.size()*rois[0].size(); i++){
		adj.push_back(std::vector<bool>()); //contents of one row
		for(int j = 0; j < rois[0])
			}
	}
	return adj;
}
//Gets distance between 2 points
double getDist(cv::Point a, cv::Point b) {
	return std::sqrt(std::pow(a.x-b.x, 2) + std::pow(a.y-b.y, 2));
}

}
