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
        //Classe & função construtora do retângulo (LM)
    Rectangle::Rectangle(const Point &upperL, 
                         const int width,
                         const int height,
                         const Color &fill )
        : fill(fill), width(width), height(height), upperL(upperL)
    {
    }
    void Rectangle::draw(PNGImage &img) const
    { //não existe draw_rectangle; UNFINISHED (LM)
        img.draw_polygon(upperL, width, height, fill);
    }
    //Classe & função construtora do retângulo (LM)
    
}
