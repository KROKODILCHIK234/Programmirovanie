#include "polygon.h"
#pragma once

double distance(const std::pair<double, double>& p1, const std::pair<double, double>& p2) {
    return sqrt((p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second));
}

double Polygon::calc_perimetr() {
    double perimeter = 0;
    for (size_t i = 0; i < vertices.getSize(); ++i) {
        perimeter += distance(vertices[i], vertices[(i + 1) % vertices.getSize()]);
    }
    return perimeter;
}

// Метод для вычисления площади многоугольника
double Polygon::calc_area() {
    double area = 0;
    for (size_t i = 0; i < vertices.getSize(); ++i) {
        area += vertices[i].first * vertices[(i + 1) % vertices.getSize()].second -
                vertices[(i + 1) % vertices.getSize()].first * vertices[i].second;
    }
    return abs(area) / 2.0;
}

void Polygon::name()
{
    std::cout << "Polygon\n";
}

void Polygon::addVertex(const std::pair<double, double>& vertex) {
    vertices.push_back(vertex);
}

Polygon::Polygon(const Vector<std::pair<double, double>>& vertices) : vertices(vertices) {}
