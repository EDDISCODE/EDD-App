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
	Node(Point p);
	vector<Node*> adj;
	Rect region;
	int x() { return region.x; }
	int y() { return region.y; }
	int width() { return region.width; }
	int height() {return region.height; }
};

class Graph{
public:
	Node& operator[](int i);
	Graph(vector<Node> n, double max=-1.0, double min=0);
	Graph(vector<Rect> r, double max=-1.0, double min = 0);
	Graph();
	vector<int> getSortedIndices();
	vector<Node*> getSorted();
	void addNode(Node n);
	void addNode(Rect m);
	int size() { return nodes.size(); }
private:
	vector<Node> nodes;
	double adjMin;
	double adjMax;
	void computeAdj(int index=-1);
	double genMax(double max = -1.0);
};

struct BaseNCounter{
	int max;
	int base;
	vector<int> digits;
public:
	BaseNCounter(int base, int size, int max);
	int operator[](int i);
	void operator++();
private:
	int check(int index);
};

}
#endif /* SEGMENTATION_H_ */
