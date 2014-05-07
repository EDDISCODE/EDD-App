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
	std::vector<Node*> nodesCp = std::vector<Node*>();
	for(int j = 0; j < nodes.size(); j++)
		nodesCp.push_back(&(nodes[j]));
	while(nodesCp.size() > 0) {
		int max = nodesCp[0]->adj.size();
		int maxInd = 0;
		for(int i = 0; i < nodesCp.size() - 1; i++)
			if(nodesCp[i]->adj.size() > max) {
				max = nodesCp[i]->adj.size();
				maxInd = i;
			}
		indices.push_back(maxInd);
	}
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
//some constructors`
Graph::Graph(){
	adjMin = 0;
	adjMax = 1;
	nodes = std::vector<Node>();
}
Graph::Graph(std::vector<Node> n, double max, double min){
	adjMin = min;
	adjMax = max;
	nodes = std::vector<Node>();
	for(int i = 0; i < n.size(); i++)
		nodes.push_back(n[i]);
	computeAdj();
}
Graph::Graph(std::vector<Rect> r, double max, double min) {
	adjMin = min;
	adjMax = max;
	nodes = std::vector<Node>();
	for(int i = 0; i < r.size(); i++)
		nodes.push_back(Node(r[i]));
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

}
