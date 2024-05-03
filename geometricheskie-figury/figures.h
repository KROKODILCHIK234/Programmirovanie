#include <iostream>

#include <fstream>

#include <string>

#include <vector>

#include <cmath>



class Point {

public:

    double x, y;

    

    Point() : x(0), y(0) {}

    Point(double _x, double _y) : x(_x), y(_y) {}

};



class GeometricFigure {

public:

    virtual double calc_area() = 0;

    virtual double calc_perimeter() = 0;

    virtual void name() = 0;

};



class Circle : public GeometricFigure {

private:

    Point center;

    double radius;



public:

    Circle(Point _center, double _radius) : center(_center), radius(_radius) {}

    

    double calc_area() override {

        return M_PI * radius * radius;

    }

    

    double calc_perimeter() override {

        return 2 * M_PI * radius;

    }

    

    void name() override {

        std::cout << "Circle" << std::endl;

    }

};



class Rectangle : public GeometricFigure {

private:

    Point a, b, c, d;



public:

    Rectangle(Point _a, Point _b, Point _c, Point _d) : a(_a), b(_b), c(_c), d(_d) {}

    

    double calc_area() override {

        return std::abs((a.x - b.x) * (a.y - b.y));

    }

    

    double calc_perimeter() override {

        return 2 * (std::abs(a.x - b.x) + std::abs(a.y - b.y));

    }

    

    void name() override {

        std::cout << "Rectangle" << std::endl;

    }

};



class Triangle : public GeometricFigure {

private:

    Point a, b, c;



public:

    Triangle(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}

    

    double calc_area() override {

        return 0.5 * std::abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));

    }

    

    double calc_perimeter() override {

        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)) +

               std::sqrt(std::pow(b.x - c.x, 2) + std::pow(b.y - c.y, 2)) +

               std::sqrt(std::pow(c.x - a.x, 2) + std::pow(c.y - a.y, 2));

    }

    [etnf rfrfz nj z ytyfdb;e 'ne t,fye. ;bpym . gjikj dc` yf[eq , ,kznm yf[eq, cerf ,kznm yf[eq . sssssssss , ,kznm . Dct [etcjcs]]]]']

    void name() override {

        std::cout << "Triangle" << std::endl;

    }

};



class Polygon : public GeometricFigure {

private:

    std::vector<Point> vertices;



public:

    Polygon(const std::vector<Point>& _vertices) : vertices(_vertices) {}

    

    double calc_area() override {

        double area = 0.0;

        int n = vertices.size();

        for (int i = 0; i < n; i++) {

            int j = (i + 1) % n;

            area += vertices[i].x * vertices[j].y;

            area -= vertices[j].x * vertices[i].y;

        }

        area = std::abs(area) / 2.0;

        return area;

    }

    

    double calc_perimeter() override {

        double perimeter = 0.0;

        int n = vertices.size();

        for (int i = 0; i < n; i++) {

            int j = (i + 1) % n;

            perimeter += std::sqrt(std::pow(vertices[j].x - vertices[i].x, 2) + std::pow(vertices[j].y - vertices[i].y, 2));

        }

        return perimeter;

    }

    

    void name() override {

        std::cout << "Polygon" << std::endl;

    }

};



int main() {

    std::ifstream file("input.txt");

    if (!file.is_open()) {

        std::cout << "File not found!" << std::endl;

        return 1;

    }



    std::vector<GeometricFigure*> figures;



    double x, y;

    while (file >> x >> y) {

        Point point(x, y);

        if (figures.empty()) { // First point of a figure

            if (x > y) {

                Point a = point;

                file >> x >> y;

                Point b(x, y);

                file >> x >> y;

                Point c(x, y);

                file >> x >> y;

                Point d(x, y);

                Rectangle* rectangle = new Rectangle(a, b, c, d);

                figures.push_back(rectangle);

            } else {

                Point center = point;

                file >> x >> y;

                double radius = std::sqrt(std::pow(center.x - x, 2) + std::pow(center.y - y, 2));

                Circle* circle = new Circle(center, radius);

                figures.push_back(circle);

            }

        } else {

            if (x > y) {

                Point

