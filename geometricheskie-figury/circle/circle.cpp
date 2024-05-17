#include "circle.h"
#include "cmath"
double Circle::calc_area()
{
	return M_PI * radius * radius;;
}

double Circle::calc_perimetr()
{
	return 2 * M_PI * radius;
}

void Circle::name()
{
	std::cout << "Circle\n";
}

Circle::Circle() {
    x = y = radius = 0;
}

Circle::Circle(double x, double y, double r):
        x(x),
        y(y),
        radius(r){}
