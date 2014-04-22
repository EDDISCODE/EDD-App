/*
 * Segmentation.h
 *
 *  Created on: Apr 22, 2014
 *      Author: cgs
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_
typedef std::vector<std::vector<cv::Rect> > rectMat;
typedef std::vector<std::vector<bool> > adjacencyMat;

using namespace cv;
namespace segmentation {
void divImg(int rows, int cols, rectMat& rois);
adjacencyMat genAdjacencyMat(rectMat rois);
std::vector<int> sortByConnections(adjacencyMat adj);
std::vector<cv::Point*> getTopN(int n);
double getRadius(cv::Point a, cv::Point b);



}




#endif /* SEGMENTATION_H_ */
