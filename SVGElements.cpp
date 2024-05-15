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
    void Ellipse::draw(PNGImage &img) const {
        img.draw_ellipse(center, radius, fill);
    }
    void Ellipse::translate(int x, int y) const {
        center.translate({x, y});
    }
    void Ellipse::rotate(const Point &origin, int &angle) const {
        center.rotate(origin,angle);
    }
    void Ellipse::scale(const Point &origin, int &factor) const {
        center.scale(origin,factor); //not sure how an ellipse scales, bit confused 
        radius.scale(origin,factor);
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
                         const int &width,
                         const int &height,
                         const Color &fill)
                : Polygon(get_rect_coordinates(), fill),
          fill(fill), width(width), height(height), upperL(upperL)
    {
    }
    void Rectangle::draw(PNGImage &img) const {
            std::vector<Point> rectPoints = get_rect_coordinates();
            img.draw_polygon(rectPoints, fill);   
    }
    std::vector<Point> Rectangle::get_rect_coordinates() const {
            std::vector<Point> all_rect_points;
            all_rect_points.push_back(upperL);                                 // Upper Left
            all_rect_points.push_back({upperL.x + width, upperL.y});          // Upper Right
            all_rect_points.push_back({upperL.x, upperL.y - height});         // Lower Left
            all_rect_points.push_back({upperL.x + width, upperL.y - height}); // Lower Right
            return all_rect_points;
    }
    // ############################################################################################################
    // Polígono (LM)
    Polygon::Polygon(const std::vector<svg::Point> &all_points,
                     const svg::Color &fill)
        : fill(fill), all_points(all_points)
    {
    }
    void Polygon::draw(PNGImage &img) const {
        img.draw_polygon(all_points, fill);
    }   
    void Polygon::translate(int x,int y) const{
        for(int i = 0; i < int(all_points.size()); i++){
            all_points[i].translate({x,y});
        }
    }
    void Polygon::rotate(const Point &origin, int &angle) const{
        for(int i = 0; i < int(all_points.size()); i++){
            all_points[i].rotate(all_points[i],angle);
        }
    }

    //Polylinha (LM)
    Polyline::Polyline(const std::vector<Point> &polyl_points, const Color &stroke)
            :polyl_points(polyl_points),stroke(stroke)
    {
    }
    void Polyline::draw(PNGImage &img) const {
        for (int i = 0; i<int(polyl_points.size()) - 1; i++){
            img.draw_line(polyl_points[i], polyl_points[i+1], stroke);
        }
    }
    void Polyline::translate(int x, int y) const {
        for (int i = 0; i<int(polyl_points.size()) - 1; i++){
        polyl_points[i].translate({x,y});   
        }
    }
    void Polyline::rotate(const Point &origin, int &angle) const {
        for (int i = 0; i<int(polyl_points.size()) - 1; i++){
        polyl_points[i].rotate(polyl_points[i],angle);   
        }
    }


    //Linha (LM)
    Line::Line(const Point &start, const Point &end, const Color &stroke)
        :Polyline({start,end},stroke),
        start(start),end(end),stroke(stroke)
    {
    }
    void Line::draw(PNGImage &img) const {
        img.draw_line(start,end,stroke);
    }   
}
