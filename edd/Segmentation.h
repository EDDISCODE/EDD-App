/*
 * Segmentation.h
 *
 *  Created on: Apr 22, 2014
 *      Author: cgs
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_
#include "TestUtils.h"
#include <cmath>
#include "math.h"

using namespace cv;
namespace segmentation {
void divImg(Mat img, int rows, int cols, std::vector<Rect>& rois);
std::vector<cv::Point*> getTopN(int n);
double getDist(cv::Point a, cv::Point b);
struct Node{
public:
	Node();
	Node(Rect r);
	Node(Point p);
	vector<Node*> adj;
	Rect region;
	Point location() { return Point(region.x, region.y); }
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
	double genMax(double max = -1.0);
private:
	vector<Node> nodes;
	double adjMin;
	double adjMax;
	void computeAdj(int index=-1);
};

struct BaseNCounter{
private:
	int m_max;
	int m_base;
	vector<int> digits;
	int check(int index);
public:
	BaseNCounter(int base, int size, int max);
	int size() { return digits.size(); }
	int max() { return m_max; }
	int base() { return m_base; }
	int operator[](int i);
	void incr();
	void print() { for(int i = 0; i < digits.size(); i++) std::cout << digits[i] << "\n"; std::cout << "- \n";}
};

int compareGraph(Graph g, Graph h);
int choose(int n, int k);
int factorial(int n);
int combos(int n, int k);
bool checkGraph(Graph g, int max=1, int min=0);

}
#endif /* SEGMENTATION_H_ */
