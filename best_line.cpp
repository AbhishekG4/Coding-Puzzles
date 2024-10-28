// Engineer: Abhishek Gautam
// Last Updated: 10-27-2024
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

#include "best_line.h"

/*Additional constructors for the Line class*/
Line::Line(double s, Point point) {  // constructor for point-slope form of line
  slope = s;
  intercept = point.y - s * point.x;
  if (s == 0)
    isHorizontal = 1;
  else
    x_intercept = -1 * intercept / s;
}
Line::Line(bool iV, Point point) {  // constructor for vertical lines
  isVertical = iV;
  slope = DBL_MAX;
  x_intercept = point.x;
}

SlopeInfo getFrequentSlope(vector<Point> points, int i) {
  unordered_map<double, int> slope_counts;  // maps slope -> frequency
  int vertical_count = 0;  // To keep track of frequency of vertical slopes as
                           // it can't be tracked by slope_counts

  // We iterate through every other point j that forms an unseen(new) pair,
  // calculate slope with i and add to hashmap
  for (int j = i + 1; j < points.size(); j++) {
    if (points[j].x == points[i].x) {  // for vertical lines
      vertical_count++;
      continue;
    }
    double m =
        (points[j].y - points[i].y) / (points[j].x - points[i].x);  // slope
    slope_counts[m]++;
  }

  // Retrieving most frequent line
  double frequent_slope = 0;
  int max_slope_count = INT_MIN;
  bool isVertical = 0;
  for (auto s : slope_counts) {
    if (max_slope_count < s.second) {
      max_slope_count = s.second;
      frequent_slope = s.first;
    }
  }
  if (vertical_count > max_slope_count) {  // considering vertical lines
    max_slope_count = vertical_count;
    isVertical = 1;
  }

  SlopeInfo info;
  info.value = frequent_slope;
  info.freq = max_slope_count;
  info.isVertical = isVertical;
  return info;
}

Line getBestLine(vector<Point> points) {
  SlopeInfo best_slope;
  best_slope.value = 0;
  best_slope.freq = INT_MIN;
  best_slope.isVertical = 0;
  int best_idx = -1;

  // we iterate through every point and keep track of the most frequent slope
  // passing through any point
  for (int i = 0; i < points.size(); i++) {
    SlopeInfo point_info = getFrequentSlope(points, i);

    if (point_info.freq > best_slope.freq) {
      best_slope.value = point_info.value;
      best_slope.freq = point_info.freq;
      best_slope.isVertical = point_info.isVertical;
      best_idx = i;
    }
  }

  if (best_slope.isVertical)
    return Line(true, points[best_idx]);
  else
    return Line(best_slope.value, points[best_idx]);
}