#ifndef BEST_LINE_H
#define BEST_LINE_H

#include <float.h>
#include <limits.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*Object to represent a point with x,y coordinates*/
struct Point {
  double x;
  double y;

  Point(double a, double b) : x(a), y(b) {}
};

/*Class for all info necessary to describe a line.
NOTE: It is assumed that if line is vertical or horizontal, intercept and
x_intercept respectively will not be considered.*/
class Line {
 public:
  double slope;
  double intercept = 0;  // y-intercept
  double x_intercept = 0;
  bool isVertical = 0;
  bool isHorizontal = 0;

  Line() : slope(0), intercept(0) {}  // default constructor
  Line(double s, Point point);
  Line(bool iV, Point point);
};

/*A medium of slope related info between getFrequentSlope and getBestLine*/
struct SlopeInfo {
  int freq;
  double value;
  bool isVertical;
};

/*For a point i, this function returns info about the most frequent slope
 * passing through that point*/
SlopeInfo getFrequentSlope(vector<Point> points, int i);

/*This function iterates through every point i and keeps track of the most
 * frequently seen line*/
Line getBestLine(vector<Point> points);

#endif