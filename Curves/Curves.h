#ifndef CURVES_CURVES_H
#define CURVES_CURVES_H


#include <cmath>


struct Curve
{
    struct Point
    {
        double x;
        double y;
        double z;
    };

    virtual Point point (double t) const = 0;
    virtual Point deriv (double t) const = 0;
};


struct Helix : Curve, private Curve::Point
{
    using typename Curve::Point;

    Helix (double radius_x, double radius_y, double step_z) : Curve::Point { radius_x, radius_y, step_z / M_PI / 2.0 } {}

    Point point (double t) const final { return { + x * std::cos(t), + y * std::sin(t), + z * t }; }
    Point deriv (double t) const final { return { - x * std::sin(t), + y * std::cos(t), + z     }; }
};


struct Ellipse : Helix
{
    Ellipse (double radius_x, double radius_y) : Helix (radius_x, radius_y, 0.0) {}
};


struct Circle : Ellipse
{
    explicit Circle (double radius) : Ellipse (radius, radius) {}
};


#endif //CURVES_CURVES_H
