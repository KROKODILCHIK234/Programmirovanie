#ifndef FIGURIES_FIGURE_H
#define FIGURIES_FIGURE_H

#pragma once

class Geometric_Figure {
public:
	virtual double calc_area()  = 0;
	virtual double calc_perimetr() = 0;
	virtual void name() = 0;
protected:

private:

};

#endif //FIGURIES_FIGURE_H
