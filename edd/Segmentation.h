/*
 * Segmentation.h
 *
 *  Created on: Apr 22, 2014
 *      Author: cgs
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_
#include "TestUtils.h"
typedef std::vector<std::vector<cv::Mat> > matVec;
typedef std::vector<std::vector<bool> > adjacencyMat;

using namespace cv;
namespace segmentation {
void divImg(int rows, int cols, matVec& rois);
adjacencyMat genAdjacencyMat(matVec rois, double upperLim, double lowerLim = 0);
std::vector<int> sortByConnections(adjacencyMat adj);
std::vector<cv::Point*> getTopN(int n);
double getDist(cv::Point a, cv::Point b);
}




#endif /* SEGMENTATION_H_ */
