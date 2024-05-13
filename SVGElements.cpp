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
    //############################################################################################################
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
    //############################################################################################################
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
        : Ellipse(fill, center, {radius, radius})
    {
    }
    void Circle::draw(PNGImage &img) const
    {
        //img.draw_ellipse(center, radius, fill);
    }
    Line::Line(double x1, double y1, double x2, double y2, const std::string& stroke): x1(x1), y1 (y1), x2(x2), y2(y2), stroke(stroke){}
    Line::~Line() {}

    void Line::draw(PNGImage& image)const {
        image.drawLine(x1, y1, x2, y2, stroke);
    }
    Polyline::Polyline(const std::vector<Point>& points, const std::string& stroke):points(points), stroke(stroke){}
    Polyline::~Polyline(){}
    void Polyline::draw(PNGImage& image) const {
        for (size_t i= 0; i <points.size() -1; ++i) {
            image.drawLine(points[i].x, points.y, points[i+1].x, points[i+1].y, stroke);
        }
