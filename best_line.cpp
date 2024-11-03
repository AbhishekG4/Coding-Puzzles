#include "best_line.h"

// Additional constructors for the Line class
Line::Line(double slope,
           Point point) {  // constructor for point-slope form of line
  Line::slope = slope;
  intercept = point.y - slope * point.x;
  if (slope == 0)
    isHorizontal = true;
  else
    x_intercept = -1 * intercept / slope;
}
Line::Line(bool isVertical, Point point) {  // constructor for vertical lines
  Line::isVertical = isVertical;
  slope = DBL_MAX;
  x_intercept = point.x;
}

SlopeInfo GetFrequentSlope(const std::vector<Point> &points, size_t i) {
  absl::flat_hash_map<double, int> slope_counts;  // maps slope -> frequency
  int vertical_count = 0;  // To keep track of frequency of vertical slopes as
                           // it can't be tracked by slope_counts

  // We iterate through every other point j that forms an unseen(new) pair,
  // calculate slope with i and add to hashmap
  for (size_t j = i + 1; j < points.size(); j++) {
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
  bool isVertical = false;
  for (auto s : slope_counts) {
    if (max_slope_count < s.second) {
      max_slope_count = s.second;
      frequent_slope = s.first;
    }
  }
  if (vertical_count > max_slope_count) {  // considering vertical lines
    max_slope_count = vertical_count;
    isVertical = true;
  }

  return {.value = frequent_slope,
          .freq = max_slope_count,
          .isVertical = isVertical};
}

Line GetBestLine(const std::vector<Point> &points) {
  SlopeInfo best_slope{.value = 0, .freq = INT_MIN, .isVertical = false};
  int best_idx = -1;

  // we iterate through every point and keep track of the most frequent slope
  // passing through any point
  for (size_t i = 0; i < points.size(); i++) {
    SlopeInfo point_info = GetFrequentSlope(points, i);

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