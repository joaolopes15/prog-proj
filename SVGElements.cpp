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
    //circle
    Circle::Circle(const Color &fill,
                   const Point &center,
                   const int &radius)
        : Ellipse(fill, center, {radius, radius})
    {
    }
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, {radius, radius}, fill);
    }
    // ############################################################################################################
    //  @todo provide the implementation of SVGElement derived classes
    //  HERE -->
    // Retângulo (LM)
    Rectangle::Rectangle(const Point &upperL,
                         const int width,
                         const int height,
                         const Color &fill)
        : Polygon({upperL,
                   {upperL.x + width, upperL.y},
                   {upperL.x, upperL.y - height},
                   {upperL.x + width, upperL.y - height}},
                  fill),
          fill(fill), width(width), height(height), upperL(upperL)
    {
    }
    void Rectangle::draw(PNGImage &img) const
    {
        std::vector<Point> rectPoints = get_rect_coordinates();
        img.draw_polygon(rectPoints, fill);
    }
    // ############################################################################################################
    // Polígono (LM)
    Polygon::Polygon(std::vector<svg::Point> all_points,
                     const svg::Color &fill)
        : fill(fill), all_points(all_points)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(all_points, fill);
    }   
    /* Line::Line(double x1, double y1, double x2, double y2, const std::string &stroke) : x1(x1), y1(y1), x2(x2), y2(y2), stroke(stroke) {}
    Line::~Line() {}

    void Line::draw(PNGImage &image) const
    {
        // image.drawLine(x1, y1, x2, y2, stroke);
    }
    Polyline::Polyline(const std::vector<Point> &points, const std::string &stroke) : points(points), stroke(stroke) {}
    Polyline::~Polyline() {}
    void Polyline::draw(PNGImage &image) const
    {
        for (size_t i = 0; i < points.size() - 1; ++i)
        {
            // image.drawLine(points[i].x, points.y, points[i+1].x, points[i+1].y, stroke);
        }
    } */
}
