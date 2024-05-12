//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

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
    
    /*############################################################################################################
    Implementação da classe Rectangle (LM)*/
    class Rectangle : public SVGElement{
        public:
        Rectangle(const Point &upperL, const int width, const int height, const Color &fill);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        int width;
        int height;
        Point upperL;
    };
    //Implementação da classe Polygon (LM)
    class Polygon : public SVGElement{
        public:
        Polygon(const Point point_pol, const Color &fill);
        void draw(PNGImage &image) const override;
    private:
        Color fill;
        Point point_pol;
    };
    //Implementação da classe Line (LM)
}
#endif
