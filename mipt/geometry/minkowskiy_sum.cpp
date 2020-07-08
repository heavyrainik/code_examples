#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

class Vector {
public:
  Vector(double x, double y, double z) : x(x), y(y), z(z) {};

  Vector operator-() {
    return Vector(-x, -y, -z);
  }

  friend void FixOrder(const size_t amount_of_points, std::vector<Vector>& polygon);
  friend bool LesserPolarAngle(const Vector& vector1, const Vector& vector2);
  friend bool ContainsZero(const std::vector<Vector>& polygon);

  friend Vector operator*(double constant, const Vector& vector) {
    return Vector(constant * vector.x, constant * vector.y, constant * vector.z);
  }

  friend Vector operator+(const Vector& vector1, const Vector& vector2) {
    return Vector(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
  }

  friend Vector operator-(const Vector& vector1, const Vector& vector2) {
    return Vector(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
  }

  friend Vector operator/(double constant, const Vector& vector) {
    return Vector(constant * vector.x, constant * vector.y, constant * vector.z);
  }

  double Normalization() {
    return sqrt(ScalarProduct(*this, *this));
  }

  friend double ScalarProduct(const Vector& vector1, const Vector& vector2) {
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
  }

private:
  double x;
  double y;
  double z;
};

void FixOrder(const size_t amount_of_points, std::vector<Vector>& polygon) {
  std::vector<Vector> polygon_with_correct_order;

  int min = 0;
  const double epsilon = 0.00001;

  for (int i = 1; i < amount_of_points; ++i) {
    if ((polygon[i].x < polygon[min].x) || ((std::abs(polygon[i].x - polygon[min].x) < epsilon) && (polygon[i].y < polygon[min].y))) {
      min = i;
    }
  }

  for (int i = 0; i < amount_of_points; ++i) {
    polygon_with_correct_order.push_back(polygon[(min + i + 1) % amount_of_points]);
  }

  std::reverse(polygon_with_correct_order.begin(), polygon_with_correct_order.end());

  polygon = polygon_with_correct_order;
}

void GetPolygon(const size_t amount_of_points, std::vector<Vector>& polygon) {
  for (int i = 0; i < amount_of_points; ++i) {
    double x;
    double y;

    std::cin >> x >> y;

    polygon.push_back(Vector(x, y, 0.0));
  }

  FixOrder(amount_of_points, polygon);
}

void GetAntipolygon(const size_t amount_of_points, std::vector<Vector>& polygon) {
  for (int i = 0; i < amount_of_points; ++i) {
    double x;
    double y;

    std::cin >> x >> y;

    polygon.push_back(Vector(-x, -y, 0.0));
  }

  FixOrder(amount_of_points, polygon);
}

bool LesserPolarAngle(const Vector& vector1, const Vector& vector2) {
  if (vector1.x > 0 && vector2.x < 0) {
    return true;
  }
  if (vector1.x < 0 && vector2.x > 0) {
    return false;
  }

  const double epsilon = 0.00001;

  double tg1 = vector1.y / vector1.x;
  double tg2 = vector2.y / vector2.x;

  if (std::abs(vector1.x) < epsilon) {
    if (vector1.y > 0) {
      return vector2.x < 0;
    }
    else {
      return false;
    }
  }

  if (std::abs(vector2.x) < epsilon) {
    if (vector2.y > 0) {
      return vector1.x > 0;
    }
    else {
      return std::abs(tg1 - tg2) > epsilon;
    }
  }

  if (std::abs(tg1 - tg2) < epsilon) {
    return false;
  }

  return tg1 < tg2;
}

void GetMinkowskiySum(size_t amount_of_points_in_the_first_polygon, size_t amount_of_points_in_the_second_polygon, std::vector<Vector>& first_polygon, std::vector<Vector>& second_polygon, std::vector<Vector>& minkowskiy_sum) {
  int i = 0;
  int j = 0;

  first_polygon.push_back(first_polygon[0]);
  second_polygon.push_back(second_polygon[0]);

  while (i < amount_of_points_in_the_first_polygon && j < amount_of_points_in_the_second_polygon) {
    minkowskiy_sum.push_back(first_polygon[i] + second_polygon[j]);

    if (LesserPolarAngle(first_polygon[i + 1] - first_polygon[i], second_polygon[j + 1] - second_polygon[j])) {
      ++i;
    }
    else if (LesserPolarAngle(second_polygon[j + 1] - second_polygon[j], first_polygon[i + 1] - first_polygon[i])) {
      ++j;
    }
    else {
      ++i;
      ++j;
    }
  }
}

bool DifferentSigns(double a, double b) {
  return a < 0 && b > 0 || a > 0 && b < 0;
}

bool ContainsZero(const std::vector<Vector>& polygon) {
  const double epsilon = 0.00001;
  size_t amount_of_angles = polygon.size();

  std::vector<double> probable_angle;

  if (DifferentSigns(polygon[0].y, polygon[polygon.size() - 1].y)) {
    probable_angle.push_back((polygon[0].x + polygon[polygon.size() - 1].x) / 2);
  }

  for (int i = 0; i < amount_of_angles - 1; ++i) {
    if (DifferentSigns(polygon[i].y, polygon[i + 1].y)) {
      probable_angle.push_back((polygon[i].x + polygon[i + 1].x) / 2);
    }
  }

  for (int i = 0; i < amount_of_angles; ++i) {
    if (fabs(polygon[i].y) < epsilon) {
      probable_angle.push_back(polygon[i].x);
    }
  }

  if (probable_angle.empty()) {
    return false;
  }

  double min = probable_angle[0];
  double max = probable_angle[0];

  for (double sector : probable_angle) {
    if (sector > max) {
      max = sector;
    }
    if (sector < min) {
      min = sector;
    }
  }

  return fabs(max) < epsilon || fabs(min) < epsilon || DifferentSigns(max, min);
}

bool CheckIfPolygonsIntersect(size_t amount_of_points_in_the_first_polygon, size_t amount_of_points_in_the_second_polygon, std::vector<Vector>& first_polygon, std::vector<Vector>& second_polygon) {
  std::vector<Vector> minkowskiy_sum;

  GetMinkowskiySum(amount_of_points_in_the_first_polygon, amount_of_points_in_the_second_polygon, first_polygon, second_polygon, minkowskiy_sum);

  return ContainsZero(minkowskiy_sum);
}

int main() {
  size_t amount_of_points_in_the_first_polygon;
  size_t amount_of_points_in_the_second_polygon;

  std::vector<Vector> first_polygon;
  std::vector<Vector> second_polygon;

  std::cin >> amount_of_points_in_the_first_polygon;

  GetPolygon(amount_of_points_in_the_first_polygon, first_polygon);

  std::cin >> amount_of_points_in_the_second_polygon;

  GetAntipolygon(amount_of_points_in_the_second_polygon, second_polygon);

  if (CheckIfPolygonsIntersect(amount_of_points_in_the_first_polygon, amount_of_points_in_the_second_polygon, first_polygon, second_polygon)) {
    std::cout << "YES";
  }
  else {
    std::cout << "NO";
  }

  return 0;
}