#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class Point {
public:
  friend class ConvexHull;
  friend void RotatePoint(Point& point, double angle);

  Point(double x = 0, double y = 0, double z = 0, int point_number = -1)
    : x(x), y(y), z(z)
    , point_number_(point_number)
    , next_(nullptr)
    , prev_(nullptr) {}

  bool ConnectSupportingRib() {
    if (prev_->next_ != this) {
      prev_->next_ = this;
      next_->prev_ = this;
      return true;
    }
    else {
      prev_->next_ = next_;
      next_->prev_ = prev_;
      return false;
    }
  }
private:
  double x;
  double y;
  double z;

  int point_number_;
  
  Point* next_;
  Point* prev_;
};

void RotatePoint(Point& point, double angle) {
  double new_x = point.x * cos(angle) + point.z * sin(angle);
  double new_z = -point.x * sin(angle) + point.z * cos(angle);
  point.x = new_x;
  point.z = new_z;

  new_z = point.z * cos(angle) + point.y * sin(angle);
  double new_y = -point.z * sin(angle) + point.y * cos(angle);
  point.z = new_z;
  point.y = new_y;

  new_x = point.x * cos(angle) + point.y * sin(angle);
  new_y = -point.x * sin(angle) + point.y * cos(angle);
  point.x = new_x;
  point.y = new_y;
}

class Face {
public:
  friend class ConvexHull;

  Face(int first_point, int second_point, int third_point)
    : first_point_(first_point)
    , second_point_(second_point)
    , third_point_(third_point) {}

  void fixOrder() {
    if (second_point_ < first_point_ && second_point_ < third_point_) {
      std::swap(first_point_, second_point_);
      std::swap(second_point_, third_point_);
    }
    else if (third_point_ < first_point_ && third_point_ < second_point_) {
      std::swap(second_point_, third_point_);
      std::swap(first_point_, second_point_);
    }
  }

  void Show() {
    std::cout << 3 << " " << first_point_ << " " << second_point_ << " " << third_point_ << "\n";
  }

  friend bool operator<(const Face& f1, const Face& f2) {
    if (f1.first_point_ < f2.first_point_) {
      return true;
    }
    else if (f1.first_point_ > f2.first_point_) {
      return false;
    }
    else {
      if (f1.second_point_ < f2.second_point_) {
        return true;
      }
      else if (f1.second_point_ > f2.second_point_) {
        return false;
      }
      else {
        return f1.third_point_ < f2.third_point_;
      }
    }
  }
private:
  int first_point_;
  int second_point_;
  int third_point_;
};

class ConvexHull {
public:
  ConvexHull(std::vector<Point>& points, size_t amount_of_points) : points_(points) {
    BuildConvexHull(amount_of_points);
  }

  std::vector<Face> GetResult() {
    return convex_hull_;
  }
private:
  double Sign(const Point* a, const Point* b, const Point* c) {
    if (a == nullptr || b == nullptr || c == nullptr) {
      return INF;
    }
    return (b->x - a->x) * (c->y - b->y) - (b->y - a->y) * (c->x - b->x);
  }

  double Time(const Point* a, const Point* b, const Point* c) {
    if (a == nullptr || b == nullptr || c == nullptr) {
      return INF;
    }
    return ((b->x - a->x) * (c->z - b->z) - (b->z - a->z) * (c->x - b->x)) / Sign(a, b, c);
  }

  std::vector<Point*> BuildDownHull(size_t left_border, size_t right_border) {
    if (right_border - left_border == 1) {
      return std::vector<Point*>();
    }

    size_t middle = (left_border + right_border) / 2;
    
    std::vector<std::vector<Point*>> events;
    events.push_back(BuildDownHull(left_border, middle));
    events.push_back(BuildDownHull(middle, right_border));
    
    std::vector<Point*> result;

    left_part_of_rib_ = &points_[middle - 1];
    right_part_of_rib_ = &points_[middle];

    FindSupportingRib(left_part_of_rib_, right_part_of_rib_);
    BuildFigureScan(events, result);

    left_part_of_rib_->next_ = right_part_of_rib_;
    right_part_of_rib_->prev_ = left_part_of_rib_;

    ReflectEvents(result, middle); 

    return result;
  }

  void ReflectEvents(std::vector<Point*>& result, const size_t& middle) {
    for (int i = result.size() - 1; i >= 0; --i) {
      Point* current_event = result[i];

      if (current_event->x > left_part_of_rib_-> x&& current_event->x < right_part_of_rib_->x) {
        left_part_of_rib_->next_ = current_event;
        right_part_of_rib_->prev_ = current_event;
        current_event->prev_ = left_part_of_rib_;
        current_event->next_ = right_part_of_rib_;

        if (current_event->x <= points_[middle - 1].x) {
          left_part_of_rib_ = current_event;
        } else {
          right_part_of_rib_ = current_event;
        }
      } else {
        current_event->ConnectSupportingRib();

        if (current_event == left_part_of_rib_) {
          left_part_of_rib_ = left_part_of_rib_->prev_;
        }

        if (current_event == right_part_of_rib_) {
          right_part_of_rib_ = right_part_of_rib_->next_;
        }
      }
    }

  }

  void BuildFigureScan(std::vector<std::vector<Point*>>& events, std::vector<Point*>& result) {
    size_t point_from_left_hull = 0;
    size_t point_from_right_hull = 0;

    for (double current_time = -INF;;) {
      int event_key = -1;
      double min_time = INF;

      Point* left = nullptr;
      Point* right = nullptr;
      
      std::vector<double> time_for_event(6, INF);

      DefineEventsTime(point_from_left_hull, events, left, time_for_event, point_from_right_hull, right);

      for (int i = 0; i < 6; ++i) {
        if (time_for_event[i] > current_time&& time_for_event[i] < min_time) {
          min_time = time_for_event[i];
          event_key = i;
        }
      }

      if (event_key == -1 || min_time >= INF) {
        break;
      }

      ExecuteEvent(event_key, left, result, point_from_left_hull, right, point_from_right_hull);

      current_time = min_time;
    }
  }

  void ExecuteEvent(int event_key, Point*& left, std::vector<Point*>& result, size_t& point_from_left_hull, Point*& right, size_t& point_from_right_hull) {
    switch (event_key) {
    case 0:
      if (left->x < left_part_of_rib_->x) {
        result.push_back(left);
      }
      left->ConnectSupportingRib();
      ++point_from_left_hull;
      
      break;
    case 1:
      if (right->x > right_part_of_rib_->x) {
        result.push_back(right);
      }
      right->ConnectSupportingRib();
      point_from_right_hull++;
      
      break;
    case 2:
      result.push_back(right_part_of_rib_);
      right_part_of_rib_ = right_part_of_rib_->next_;
      
      break;
    case 3:
      right_part_of_rib_ = right_part_of_rib_->prev_;
      result.push_back(right_part_of_rib_);
      break;
    case 4:
      result.push_back(left_part_of_rib_);
      left_part_of_rib_ = left_part_of_rib_->prev_;
      
      break;
    case 5:
      left_part_of_rib_ = left_part_of_rib_->next_;
      result.push_back(left_part_of_rib_);
     
      break;
    default:
      break;
    }
  }

  void DefineEventsTime(const size_t& point_from_left_hull, std::vector<std::vector<Point*>>& events, Point*& left, std::vector<double>& next_t, const size_t& point_from_right_hull, Point*& right) {
    if (point_from_left_hull < events[0].size()) {
      left = events[0][point_from_left_hull];
      next_t[0] = Time(left->prev_, left, left->next_);
    }

    if (point_from_right_hull < events[1].size()) {
      right = events[1][point_from_right_hull];
      next_t[1] = Time(right->prev_, right, right->next_);
    }

    next_t[2] = Time(left_part_of_rib_, right_part_of_rib_, right_part_of_rib_->next_);
    next_t[3] = Time(left_part_of_rib_, right_part_of_rib_->prev_, right_part_of_rib_);
    next_t[4] = Time(left_part_of_rib_->prev_, left_part_of_rib_, right_part_of_rib_);
    next_t[5] = Time(left_part_of_rib_, left_part_of_rib_->next_, right_part_of_rib_);
  }

  void FindSupportingRib(Point*& u, Point*& v) {
    bool rib_is_building = true;

    while (rib_is_building) {
      if (Sign(u, v, v->next_) < 0) {
        v = v->next_;
      } else if (Sign(u->prev_, u, v) < 0) {
        u = u->prev_;
      } else {
        rib_is_building = false;
      }
    }
  }

  void BuildConvexHull(size_t amount_of_points) {
    for (auto& point : points_) {
      RotatePoint(point, 0.01);
    }

    std::sort(points_.begin(), points_.end(), [](const Point& point1, const Point& point2) {return point1.x < point2.x; });

    std::vector<Point*> events = BuildDownHull(0, amount_of_points);

    for (Point* event : events) {
      Face current(event->prev_->point_number_, event->point_number_, event->next_->point_number_);

      if (!event->ConnectSupportingRib()) {
        std::swap(current.first_point_, current.second_point_);
      }
      convex_hull_.push_back(current);
    }

    for (Point& point : points_) {
      point.next_ = nullptr;
      point.prev_ = nullptr;
      point.z = -point.z;
    }

    events = BuildDownHull(0, amount_of_points);

    for (Point* event : events) {
      Face current(event->prev_->point_number_, event->point_number_, event->next_->point_number_);

      if (event->ConnectSupportingRib()) {
        std::swap(current.first_point_, current.second_point_);
      }
      convex_hull_.push_back(current);
    }
  }

  double const INF = 1e9;

  Point* left_part_of_rib_;
  Point* right_part_of_rib_;

  std::vector<Point> points_;
  std::vector<Face> convex_hull_;
};

void PrintAnswer(ConvexHull& convex_hull) {

  std::vector<Face> convex_hull_faces = convex_hull.GetResult();
  for (Face& face : convex_hull_faces) {
    face.fixOrder();
  }

  std::sort(convex_hull_faces.begin(), convex_hull_faces.end());

  std::cout << convex_hull_faces.size() << "\n";
  for (Face& face : convex_hull_faces) {
    face.Show();
  }
}


int main() {
  int amount_of_tests;
  int amount_of_points;

  std::cin >> amount_of_tests;

  for (size_t i = 0; i < amount_of_tests; ++i) {
    std::vector<Point> points;

    std::cin >> amount_of_points;
    for (int number_of_point = 0; number_of_point < amount_of_points; ++number_of_point) {
      int x, y, z;

      std::cin >> x >> y >> z;
      
      Point p(x, y, z, number_of_point);

      points.push_back(p);
    }

    ConvexHull convex_hull(points, amount_of_points);

    PrintAnswer(convex_hull);
  }

  return 0;
}