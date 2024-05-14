//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include<vector> //usado (pelo menos) na classe Polygon

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point center;
        Point radius;
    };
    
    class Circle : public Ellipse 
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point center;
        int radius;
    };
    
    //############################################################################################################
    //Implementação da classe Polygon (LM)
    class Polygon : public SVGElement{
        public:
        Polygon(const std::vector <Point> all_points, const Color &fill);
        void draw(PNGImage &image) const override;
    private:
        Color fill;
        std::vector <Point> all_points;
    };

    //Implementação da classe Rectangle (classe derivada de polygon)(LM)
    class Rectangle : public Polygon{ 
        public:
        Rectangle(const Point &upperL, const int width, const int height, const Color &fill);

        void draw(PNGImage &img) const override;

        //função que dá return do vetor all_rect_points - necessário neste formato p/ draw_polygon
        std::vector<Point> get_rect_coordinates() const { 
        std::vector<Point> all_rect_points;
        all_rect_points.push_back(upperL); // Upper Left
        all_rect_points.emplace_back(upperL.x + width, upperL.y); // Upper Right
        all_rect_points.emplace_back(upperL.x, upperL.y - height); // Lower Left
        all_rect_points.emplace_back(upperL.x + width, upperL.y - height); // Lower Right
        return all_rect_points;}

        private:
            Color fill;
            int width;
            int height;
            Point upperL;
    };

    //Implementação da classe Line 
    class Line: public SVGElement {
        public: 
        Line(double x1, double y1, double x2, double y2, const std::string& stroke);
        virtual ~Line();
        virtual void draw(PNGImage& image) const;
    private:
        double x1, y1, x2, y2;
        std::string stroke;
    };
    //Implementação da classe Polyline 
    class Polyline: public SVGElement {
        public: 
        Polyline(const std::vector<Point>& points, const std::string& stroke);
        virtual ~Polyline();
        virtual void draw(PNGImage& image) const;
    private:
        std::vector<Point> points;
        std::string stroke;
    };
}
#endif
