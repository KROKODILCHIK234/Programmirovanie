#ifndef FIGURIES_TRIANGLE_H
#define FIGURIES_TRIANGLE_H

#pragma once
#include "../figure.h"
#include <cmath>
#include <iostream>

class Triangle :public Geometric_Figure {
public:
    Triangle();
	Triangle(double w1,double w2,double w3);
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
	double calc_perimetr() override;
	double calc_area() override;
	void name() override;
private:
	double side1 ;
	double side2 ;
	double side3 ;
    static bool isValid(double s1, double s2, double s3);
};

#endif //FIGURIES_TRIANGLE_H
