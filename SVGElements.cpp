#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->
            //Retângulo (LM)
    Rectangle::Rectangle(const Point &upperL, 
                         const int width,
                         const int height,
                         const Color &fill )
        : fill(fill), width(width), height(height), upperL(upperL)
    {
    }
    void Rectangle::draw(PNGImage &img) const
    { //não existe draw_rectangle; UNFINISHED (LM)
        //img.draw_polygon(upperL, width, height, fill);
    }
        //Polígono (LM)
    Polygon::Polygon(const Point point_pol, 
                     const Color &fill)
        : fill(fill), point_pol(point_pol)
    {    
    }
    void Polygon::draw(PNGImage &img) const 
        {
            std::vector<svg::Point> points = {point_pol}; //vetor para armazenar os pontos do polígono
            img.draw_polygon(points, fill);
        }
    
    Circle::Circle(const Color &fill,
                    const Point &center,
                    const int &radius)
        : fill(fill), center(center), radius(radius) 
    {
    }
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
}
