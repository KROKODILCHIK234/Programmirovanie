#ifndef FIGURIES_POLYGON_H
#define FIGURIES_POLYGON_H

#pragma once
#include "../figure.h"
#include "../../vector/vector.h"

class Polygon : public Geometric_Figure {
public:
    Polygon(const Vector<std::pair<double, double>>& vertices);
    void addVertex(const std::pair<double, double>& vertex);

    double calc_perimetr() override;
    double calc_area() override;
    void name() override;

private:
    Vector<std::pair<double, double>> vertices;
};

#endif //FIGURIES_POLYGON_H
