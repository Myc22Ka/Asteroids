export module BasicPlane.Figures:Circle;

import :Point;

export struct Circle {
	Point point, center;
};

export float radius(const Circle& circle);
export float area(const Circle& circle);