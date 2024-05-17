#ifndef FIGURIES_RECTANGLE_H
#define FIGURIES_RECTANGLE_H

#pragma once
#include "../figure.h"
#include <iostream>

class Rectangle : public Geometric_Figure {

public:
    Rectangle();
    Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    Rectangle(double l, double w);


    double calc_area() override;
	double calc_perimetr() override;
	void name() override;
	
private:
	double width;
	double height;
};

#endif //FIGURIES_RECTANGLE_H
