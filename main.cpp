#include <Curves.h>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <random>


auto random_curves (size_t count) -> std::vector <std::shared_ptr <Curve>>
{
    std::vector <std::shared_ptr <Curve>> curves;

    enum
    {
        HELIX   = 0,
        ELLIPSE = 1,
        CIRCLE  = 2,
        SIZE    = 3,
    };

    std::random_device device;

    std::default_random_engine random(device());

    std::uniform_int_distribution <int> type;

    std::uniform_real_distribution <double> real(0.0, 10.0);

    while (count --)

        switch (type(random) % SIZE)
        {
            case HELIX:
                curves.emplace_back(new Helix(real(random), real(random), real(random)));
                break;
            case ELLIPSE:
                curves.emplace_back(new Ellipse(real(random), real(random)));
                break;
            case CIRCLE:
                curves.emplace_back(new Circle(real(random)));
                break;
        }

    return curves;
}

auto sorted_circles (const std::vector <std::shared_ptr <Curve>> & curves) -> std::vector <std::shared_ptr <Circle>>
{
    std::vector <std::shared_ptr <Circle>> circles;

    for (const auto & curve : curves)
    {
        auto circle = dynamic_cast <Circle *> (curve.get());

        if (circle)

            circles.emplace_back(curve, circle);
    }

    auto order = [] (const std::shared_ptr <Circle> & l, const std::shared_ptr <Circle> & r)
    {
        return l -> point(0.0).x < r -> point(0.0).x;
    };

    std::sort(circles.begin(), circles.end(), order);

    return circles;
}


int main ()
{
    auto curves = random_curves(100);

    for (const auto & curve : curves)
    {
        auto p = curve -> point(M_PI_4);
        auto d = curve -> deriv(M_PI_4);

        std::cout << std::setprecision(16) << std::fixed << std::showpos
                  << p.x << "," << p.y << "," << p.z << ","
                  << d.x << "," << d.y << "," << d.z << std::endl;
    }

    auto circles = sorted_circles(curves);

    double radii_sum = 0.0;

    for (const auto & circle : circles)

        radii_sum += circle -> point(0.0).x;

    return 0;
}
