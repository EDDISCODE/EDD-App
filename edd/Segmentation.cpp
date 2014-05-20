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
//returns a vector of indices sorted greatest to least by the connectedness of their nodes
vector<int> Graph::getSortedIndices() {
	std::vector<int> indices = std::vector<int>();
	std::vector<std::vector<int> > counter = std::vector<std::vector<int> >();
	for(int i = 0; i < nodes.size(); i++)
		counter.push_back(std::vector<int>());
	for(int i = 0; i < nodes.size(); i++)
		counter[nodes[i].adj.size()].push_back(i);
	for(int i = counter.size()-1; i >= 0; i--)
		for(int j = counter[i].size()-1; j >= 0; j--)
			indices.push_back(counter[i][j]);
	return indices;
}
//returns a vector of Node* sorted from greatest to least by connectedness
std::vector<Node*> Graph::getSorted() {
	std::vector<int> ind = getSortedIndices();
	std::vector<Node*> n = std::vector<Node*>();
	for(int i = 0; i < ind.size(); i++)
		n.push_back(&(nodes[ind[i]]));
	return n;
}
Node::Node(Rect r) {
	region = r;
}
Node::Node(Point p) {
	region = Rect(p, Size(1,1));
}
Node::Node() {
	region = Rect(Point(0,0), Size(1,1));
}
//some constructors`
Graph::Graph(){
	adjMin = 0;
	adjMax = 1;
	nodes = std::vector<Node>();
}
Graph::Graph(std::vector<Node> n, double max, double min){
	adjMin = min;
	nodes = std::vector<Node>();
	for(int i = 0; i < n.size(); i++)
		nodes.push_back(n[i]);
	adjMax = genMax(max);
	computeAdj();
}
Graph::Graph(std::vector<Rect> r, double max, double min) {
	adjMin = min;
	nodes = std::vector<Node>();
	for(int i = 0; i < r.size(); i++)
		nodes.push_back(Node(r[i]));
	adjMax = genMax(max);
	computeAdj();
}
//some default max distances
double Graph::genMax(double max) {
	if(-1 == (int)(max)) //diagonal distance
			return getDist(Point(0,0), Point(nodes[0].width(), nodes[0].height()) + Point(1,1));
		else if(-2 == (int)(max)) //horizontal distance
			return nodes[0].width();
		else if(-3 == (int(max))) //vertical distance
			return nodes[0].height();
		else
			return max;
}
//adds a node to the graph
void Graph::addNode(Node n) {
	nodes.push_back(n);
	computeAdj(nodes.size()-1);
}
//adds a node to the graph
void Graph::addNode(Rect r) {
	this->addNode(Node(r));
}
//computes adjacencies
void Graph::computeAdj(int index) {
	if(index >= 0) {
		Point a = Point(nodes[index].x(), nodes[index].y());
		for(int i = 0; i < nodes.size()-1; i++) {
			if(i == index) continue;
			else {
				Point b = Point(nodes[i].x(), nodes[i].y());
				if(getDist(a, b) < adjMax && getDist(a,b) > adjMin)
					nodes[index].adj.push_back(&nodes[i]);
			}
		}
	}
	else {
		for(int i = 0; i < nodes.size(); i++) {
			nodes[i].adj.clear();
			computeAdj(i);
		}
	}
}

Node& Graph::operator[](int i) {
		return nodes[i];
}

//BaseNCounter for iterating nicely to make combinations
BaseNCounter::BaseNCounter(int base, int size, int max) {
	m_max = max;
	m_base = base;
	digits = vector<int>(size);
}

int BaseNCounter::operator[](int i) {
	return digits[i];
}

void BaseNCounter::incr(){
	digits[digits.size() - 1]++;
	check(digits.size() -1 );
}


int BaseNCounter::check(int index) {
	if(digits[index] >= m_base){
		digits[index] = 0;
		int sum = 0;
		for(int i = digits.size() - 1; i >= 0; i--)
			sum += digits[i]*(pow(m_base, (digits.size() - 1 - i)));
		if(index != 0 && sum <= m_max) {
			digits[index-1]++;
			check(index-1);
		}
		else return -5;
	}
	return -1;
}

int factorial(int n) {
	if(n < 0) return -1;
	return (n == 1 || n==0) ? 1 : n*factorial(n-1);
}
//lower return val => better match
int compareGraph(Graph g, Graph h) {
	int * countsg  = new int[g.size()];
	int * countsh = new int[h.size()];
	for(int i = 0; i < g.size(); i++)
		countsg[g[i].adj.size()]++;
	for(int i = 0; i < h.size(); i++)
		countsh[h[i].adj.size()]++;
	int sum = 0;
	for(int i = 0; i < std::min(g.size(), h.size()); i++)
		sum += std::abs(countsg[i]-countsh[i]);	
	return sum;
}

int combos(int n, int k) {
	return factorial(n) / (factorial(k) * factorial(n-k));
}

bool checkGraph(Graph g, int max, int min) {
	for(int i = 0; i < g.size(); i++)
		for(int j = i+1; j < g.size(); j++)
			if(getDist(g[i].location(), g[j].location()) > max || getDist(g[i].location(), g[j].location()) <= min) return false;
	return true;
}

}
