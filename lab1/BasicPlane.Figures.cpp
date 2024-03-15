module;

#include <cmath>;

module BasicPlane.Figures:Circle;

double radius(const Circle& circle) { return sqrt(pow(circle.point.x - circle.center.x, 2) + pow(circle.point.y - circle.center.y, 2)); }
double area(const Circle& circle) { return 3.14159265358 * (pow(circle.point.x - circle.center.x, 2) + pow(circle.point.y - circle.center.y, 2)); }