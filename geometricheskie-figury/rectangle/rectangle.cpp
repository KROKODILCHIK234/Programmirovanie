#include "rectangle.h"

double Rectangle::calc_area()
{
	return width * height;
}

double Rectangle::calc_perimetr()
{
	return 2 * (width + height);
}

void Rectangle::name() {
    std::cout << "Rectangle\n";
}

Rectangle::Rectangle() {
    height = width = 0;
}

Rectangle::Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double side1 = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double side2 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    double side3 = sqrt((x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3));
    double side4 = sqrt((x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4));

    // Проверка на равенство диагоналей и перпендикулярность
    if (side1 == side3 && side2 == side4 && (x1 - x3) * (x2 - x4) + (y1 - y3) * (y2 - y4) == 0) {
        height = std::max(side1, side2);
        width = std::min(side1, side2);
    } else {
        std::cerr << "Неправильные стороны прямоугольника! Такого прямоугольника не существует." << std::endl;
        exit(1);
    }
}

Rectangle::Rectangle(double l, double w) : height(l), width(w) {
    if (height <= 0 || width <= 0) {
        std::cerr << "Неправильные стороны прямоугольника! Такого прямоугольника не существует." << std::endl;
        exit(1);
    }
}
