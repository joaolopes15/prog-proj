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
        : fill_(fill), center_(center), radius_(radius)
    {
    }
    void Ellipse::transform(Transformation t)
    {
        center_ = center_.translate(t.traslate);
        center_ = center_.rotate(t.origin, t.rotate);
        center_ = center_.scale(t.origin, t.scale);
        radius_ = radius_.scale(Point{0, 0}, t.scale);
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center_, radius_, fill_);
    }

    // circle
    Circle::Circle(const Color &fill,
                   const Point &center,
                   const int &radius)
        : Ellipse(fill, center, {radius, radius})
    {
    }

    // ############################################################################################################
    //  @todo provide the implementation of SVGElement derived classes
    //  HERE -->
    // Retângulo (LM)
    Rectangle::Rectangle(const Point &upperL,
                         const int &width,
                         const int &height,
                         const Color &fill)
        : Polygon(get_rect_coordinates(upperL, width, height), fill)
    {
    }
    std::vector<Point> Rectangle::get_rect_coordinates(Point point, const int &w, const int &h) const
    {
        std::vector<Point> all_rect_points;
        all_rect_points.push_back(point);                                  // Upper Left
        all_rect_points.push_back({(point.x + w - 1), point.y});           // Upper Right
        all_rect_points.push_back({(point.x + w - 1), (point.y + h - 1)}); // Lower Right
        all_rect_points.push_back({point.x, (point.y + h - 1)});           // Lower Left
        return all_rect_points;
    }

    // ############################################################################################################
    // Polígono (LM)
    Polygon::Polygon(const std::vector<svg::Point> &all_points,
                     const svg::Color &fill)
        : fill_(fill), all_points_(all_points)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(all_points_, fill_);
    }
    void Polygon::transform(Transformation t)
    {
        for (Point &p : all_points_)
        {
            p = p.translate(t.traslate);
            p = p.rotate(t.origin, t.rotate);
            p = p.scale(t.origin, t.scale);
        }
    }

    // Polylinha (LM)
    Polyline::Polyline(const std::vector<Point> &polyl_points, const Color &stroke)
        : polyl_points_(polyl_points), stroke_(stroke)
    {
    }
    void Polyline::draw(PNGImage &img) const
    {
        for (int i = 0; i < int(polyl_points_.size()) - 1; i++)
        {
            img.draw_line(polyl_points_[i], polyl_points_[i + 1], stroke_);
        }
    }
    void Polyline::transform(Transformation t)
    {
        for (Point &p : polyl_points_)
        {
            p = p.translate(t.traslate);
            p = p.rotate(t.origin, t.rotate);
            p = p.scale(t.origin, t.scale);
        }
    }

    // Linha (LM)
    Line::Line(const Point &start, const Point &end, const Color &stroke)
        : Polyline({start, end}, stroke)
    {
    }
}
