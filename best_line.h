// Engineer: Abhishek Gautam
// Last Updated: 11-1-2024
//
// Problem: Given a two-dimensional graph with points on it, find a line which
//          passes the most number of points. ("Best Line" from Cracking the
//          Coding Interview)
//
// Approach:
// 1) For every point i, iterate through every unvisited point j. Each pair of
//    points
//    defines a line, thus each slope defines a line in association with the
//    point i.
// 2) For every point i, keep track of the frequency of slopes of point pairs
//    i,j using a
//    hashmap and find the most frequent.
// 3) Across all points i keep track of highest frequency slope found in the
//    previous step and that particular point.
// 4) The highest frequency slope along with its corresponding point will define
//    the best line being asked for.
//
// Time Complexity = O(n^2)
// Space Complexity = O(n)
//
// Other considerations:
// - Vertical lines (slope is inf). [Taken into account]
// - Managing floating point precision related inaccuracies. [Not taken into
// account for simplicity]
//
// Format Used:
// - points are represented as a struct with x and y.
// - Graph represented as vector of points
// - Lines are represented in slope + intercept form.
//=========================================================================================

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
  bool isVertical = false;
  bool isHorizontal = false;

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