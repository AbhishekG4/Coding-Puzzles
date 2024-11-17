#include "best_line.h"

// Additional constructors for the Line class
Line::Line(double slope,
           Point point) {  // constructor for point-slope form of line
  Line::slope_ = slope;
  intercept_ = point.y - slope * point.x;
  if (slope == 0)
    is_horizontal_ = true;
  else
    x_intercept_ = -1 * intercept_ / slope;
}
Line::Line(bool is_vertical, Point point) {  // constructor for vertical lines
  Line::is_vertical_ = is_vertical;
  slope_ = DBL_MAX;
  x_intercept_ = point.x;
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
  bool is_vertical = false;
  for (auto s : slope_counts) {
    if (max_slope_count < s.second) {
      max_slope_count = s.second;
      frequent_slope = s.first;
    }
  }
  if (vertical_count > max_slope_count) {  // considering vertical lines
    max_slope_count = vertical_count;
    is_vertical = true;
  }

  return {.value = frequent_slope,
          .freq = max_slope_count,
          .is_vertical = is_vertical};
}

Line GetBestLine(const std::vector<Point> &points) {
  SlopeInfo best_slope{.value = 0, .freq = INT_MIN, .is_vertical = false};
  int best_idx = -1;

  // we iterate through every point and keep track of the most frequent slope
  // passing through any point
  for (size_t i = 0; i < points.size(); i++) {
    SlopeInfo point_info = GetFrequentSlope(points, i);

    if (point_info.freq > best_slope.freq) {
      best_slope.value = point_info.value;
      best_slope.freq = point_info.freq;
      best_slope.is_vertical = point_info.is_vertical;
      best_idx = i;
    }
  }

  if (best_slope.is_vertical)
    return Line(true, points[best_idx]);
  else
    return Line(best_slope.value, points[best_idx]);
}