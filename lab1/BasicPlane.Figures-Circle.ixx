export module BasicPlane.Figures:Circle;

import :Point;

export struct Circle {
	Point point, center;
};

export double radius(const Circle&);
export double area(const Circle&);