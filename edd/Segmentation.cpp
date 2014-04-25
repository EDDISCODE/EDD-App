#include "Segmentation.h"
namespace segmentation {
//Cuts image into ROIs
void divImg(Mat img, int rows, int cols, matVec& rois) {
	int dx = img.cols/cols;
	int dy = img.rows/rows;
	for(int i = 0; i < img.rows; i += dy) {
		rois.push_back(vector<Mat>());
		for(int j = 0; j < img.cols; j += dx) {
			rois[i].push_back(Mat(img, Rect(Point(j, i), Size(dx, dy))));
		}
	}
}
//Computes adjacency matrix for matVec of ROIs
adjacencyMat genAdjacencyMat(matVec rois, double upperLim, double lowerLim){
	adjacencyMat adj = std::vector<std::vector<bool> >(rois.size()*rois[0].size());
	for(int i = 0; i < rois.size()*rois[0].size(); i++){
		adj.push_back(std::vector<bool>(adj.size()));
	}
	int dx = rois[0][0].cols;
	int dy = rois[0][0].rows;
	for(unsigned int ai = 0; ai < adj.size(); ai++)
		for(unsigned int aj = 0; aj < adj[0].size(); aj++){
			Point current = Point(aj % rois[0].size() * dx, ai % rois.size() *dy);
			for(unsigned int i = 0; i < rois.size(); i++)
				for(unsigned int j = 0; j < rois[0].size(); j++){
					Point other = Point(j*dx, i*dy);
					double distance = getDist(current, other);
					if(distance < upperLim && distance > lowerLim)
						adj[ai][aj] = true;
				}
		}
	return adj;
}
//Gets distance between 2 points
double getDist(cv::Point a, cv::Point b) {
	return std::sqrt(std::pow(a.x-b.x, 2) + std::pow(a.y-b.y, 2));
}
//returns a vector of row indices sorted by connectedness
std::vector<int> sortByConnections(adjacencyMat adj){
	//constructing a list of row indices and the sums of their connections
	std::vector<Point> list = std::vector<Point>(adj.size());
	for(unsigned int i = 0; i < adj.size(); i++){
		int sum = 0;
		for(unsigned int j = 0; j < adj[0].size(); j++){
			if(adj[i][j] == true)
				sum++;
		}
		list[i] = Point(i, sum);
	}
	//sorting the list by number of connections from greatest to least to get list of indices
	std::vector<int> sortedList = std::vector<int>();
	for(int k = list.size(); k > 0; k++){
		int maxInd = 0;
		int maxVal = list[maxInd].y;
		for(unsigned int n = 0; n < list.size(); n++)
			if(list[n].y > maxVal) {
				maxInd = n;
				maxVal = list[n].y;
			}
		sortedList.push_back(list[maxInd].x);
		list.erase(list.begin() + maxInd);
	}
	return sortedList;
}

}
