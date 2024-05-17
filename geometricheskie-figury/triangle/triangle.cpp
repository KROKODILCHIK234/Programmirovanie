#include "triangle.h"

double Triangle::calc_perimetr()
{
	return side1 + side2 + side3;
}

double Triangle::calc_area()
{
	double half_of_perimetr = calc_perimetr() / 2;
	return 	sqrt(half_of_perimetr * (half_of_perimetr - side1) * (half_of_perimetr - side2) * (half_of_perimetr - side3));
}

void Triangle::name()
{
	std::cout << "Triangle\n";

}

bool Triangle::isValid(double s1, double s2, double s3) {
    return (s1 + s2 > s3 && s2 + s3 > s1 && s1 + s3 > s2);
}

Triangle::Triangle() {
    side1 = side2 = side3 = 0;
}

Triangle::Triangle(double w1,double w2,double w3) {
    if (isValid(w1, w2, w3)) {
        side1 = w1;
        side2 = w2;
        side3 = w3;
    } else {
        std::cerr << "Неправильные стороны треугольника! Такого треугольника не существует." << std::endl;
        exit(1);
    }
}

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3):
        Triangle((sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))),
                 (sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2))),
                 (sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)))) {}
