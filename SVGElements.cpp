#include "SVGElements.hpp"

namespace svg
/**
 * @file SVGElements.cpp
 * @brief Implementation of SVGElement derived classes.
 */

{
    /**
     * @brief Base class for SVG elements.
     * 
     * This class represents the base class for all SVG elements.
     * It provides default constructors and destructors.
     */
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    /**
     * @brief Constructs an Ellipse object.
     * 
     * This constructor initializes an Ellipse object with the given fill color, center point, and radius.
     * 
     * @param fill The fill color of the ellipse.
     * @param center The center point of the ellipse.
     * @param radius The radius of the ellipse.
     */
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill_(fill), center_(center), radius_(radius)
    {
    }

    /**
     * @brief Transforms the ellipse.
     * 
     * This function applies the given transformation to the ellipse.
     * 
     * @param t The transformation to be applied.
     */
    void Ellipse::transform(Transformation t)
    {
        center_ = center_.translate(t.traslate);
        center_ = center_.rotate(t.origin, t.rotate);
        center_ = center_.scale(t.origin, t.scale);
        radius_ = radius_.scale(Point{0, 0}, t.scale);
    }

    /**
     * @brief Draws the ellipse on the PNG image.
     * 
     * This function draws the ellipse on the given PNG image using the specified fill color.
     * 
     * @param img The PNG image to draw on.
     */
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center_, radius_, fill_);
    }

    /**
     * @brief Constructs a Circle object.
     * 
     * This constructor initializes a Circle object with the given fill color, center point, and radius.
     * 
     * @param fill The fill color of the circle.
     * @param center The center point of the circle.
     * @param radius The radius of the circle.
     */
    Circle::Circle(const Color &fill,
                   const Point &center,
                   const int &radius)
        : Ellipse(fill, center, {radius, radius})
    {
    }

    /**
     * @brief Constructs a Rectangle object.
     * 
     * This constructor initializes a Rectangle object with the given upper left corner, width, height, and fill color.
     * 
     * @param upperL The upper left corner of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param fill The fill color of the rectangle.
     */
    Rectangle::Rectangle(const Point &upperL,
                         const int &width,
                         const int &height,
                         const Color &fill)
        : Polygon(get_rect_coordinates(upperL, width, height), fill)
    {
    }

    /**
     * @brief Returns the coordinates of the four corners of a rectangle.
     * 
     * This function calculates and returns the coordinates of the four corners of a rectangle.
     * 
     * @param point The coordinates of the upper left corner of the rectangle.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     * @return A vector containing the coordinates of the four corners of the rectangle.
     */
    std::vector<Point> Rectangle::get_rect_coordinates(Point point, const int &w, const int &h) const
    {
        std::vector<Point> all_rect_points;
        all_rect_points.push_back(point);                                  // Upper Left
        all_rect_points.push_back({(point.x + w - 1), point.y});           // Upper Right
        all_rect_points.push_back({(point.x + w - 1), (point.y + h - 1)}); // Lower Right
        all_rect_points.push_back({point.x, (point.y + h - 1)});           // Lower Left
        return all_rect_points;
    }

    /**
     * @brief Constructs a Polygon object.
     * 
     * This constructor initializes a Polygon object with the given points and fill color.
     * 
     * @param all_points The points that define the polygon.
     * @param fill The fill color of the polygon.
     */
    Polygon::Polygon(const std::vector<svg::Point> &all_points,
                     const svg::Color &fill)
        : fill_(fill), all_points_(all_points)
    {
    }

    /**
     * @brief Draws the polygon on the PNG image.
     * 
     * This function draws the polygon on the given PNG image using the specified fill color.
     * 
     * @param img The PNG image to draw on.
     */
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(all_points_, fill_);
    }

    /**
     * @brief Transforms the polygon.
     * 
     * This function applies the given transformation to the polygon.
     * 
     * @param t The transformation to be applied.
     */
    void Polygon::transform(Transformation t)
    {
        for (Point &p : all_points_)
        {
            p = p.translate(t.traslate);
            p = p.rotate(t.origin, t.rotate);
            p = p.scale(t.origin, t.scale);
        }
    }

    /**
     * @brief Constructs a Polyline object.
     * 
     * This constructor initializes a Polyline object with the given points and stroke color.
     * 
     * @param polyl_points The points that define the polyline.
     * @param stroke The stroke color of the polyline.
     */
    Polyline::Polyline(const std::vector<Point> &polyl_points, const Color &stroke)
        : polyl_points_(polyl_points), stroke_(stroke)
    {
    }

    /**
     * @brief Draws the polyline on the PNG image.
     * 
     * This function draws the polyline on the given PNG image using the specified stroke color.
     * 
     * @param img The PNG image to draw on.
     */
    void Polyline::draw(PNGImage &img) const
    {
        for (int i = 0; i < int(polyl_points_.size()) - 1; i++)
        {
            img.draw_line(polyl_points_[i], polyl_points_[i + 1], stroke_);
        }
    }

    /**
     * @brief Transforms the polyline.
     * 
     * This function applies the given transformation to the polyline.
     * 
     * @param t The transformation to be applied.
     */
    void Polyline::transform(Transformation t)
    {
        for (Point &p : polyl_points_)
        {
            p = p.translate(t.traslate);
            p = p.rotate(t.origin, t.rotate);
            p = p.scale(t.origin, t.scale);
        }
    }

    /**
     * @brief Constructs a Line object.
     * 
     * This constructor initializes a Line object with the given start point, end point, and stroke color.
     * 
     * @param start The start point of the line.
     * @param end The end point of the line.
     * @param stroke The stroke color of the line.
     */
    Line::Line(const Point &start, const Point &end, const Color &stroke)
        : Polyline({start, end}, stroke)
    {
    }
}
