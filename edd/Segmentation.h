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
};

class Graph{
public:
	Graph(vector<Rect> r);
	Graph();
	vector<int> getSortedIndices();
	vector<Mat> getSorted();
	void addNode(Node n);
	void addNode(Mat m);
private:
	vector<Node> nodes;
	void computeAdj(int index=-1);
};



}
#endif /* SEGMENTATION_H_ */
