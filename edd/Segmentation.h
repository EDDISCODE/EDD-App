/*
 * Segmentation.h
 *
 *  Created on: Apr 22, 2014
 *      Author: cgs
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_
#include "TestUtils.h"

using namespace cv;
namespace segmentation {
void divImg(Mat img, int rows, int cols, std::vector<Rect>& rois);
std::vector<cv::Point*> getTopN(int n);
double getDist(cv::Point a, cv::Point b);
struct Node{
public:
	Node(Rect r);
	vector<Node*> adj;
	Rect region;
	int x() { return region.x; }
	int y() { return region.y; }
};

class Graph{
public:
	Graph(vector<Node> n, double max, double min=0);
	Graph(vector<Rect> r, double max, double min = 0);
	Graph();
	vector<int> getSortedIndices();
	vector<Node*> getSorted();
	void addNode(Node n);
	void addNode(Rect m);
private:
	vector<Node> nodes;
	double adjMin;
	double adjMax;
	void computeAdj(int index=-1);
};



}
#endif /* SEGMENTATION_H_ */
