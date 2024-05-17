//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <vector> //used (at least) in the Polygon class

/**
 * @namespace svg
 * @brief Contains classes and functions related to SVG elements.
 */
namespace svg
{
    /**
     * @brief Represents a transformation to be applied to an SVG element.
     */
    struct Transformation
    {
        Point traslate; //!< The translation vector.
        int rotate;     //!< The rotation angle in degrees.
        int scale;      //!< The scaling factor.
        Point origin;   //!< The origin point for rotation and scaling.
    };

    /**
     * @brief Base class for SVG elements.
     */
    class SVGElement
    {

    public:
        /**
         * @brief Default constructor.
         */
        SVGElement();

        /**
         * @brief Virtual destructor.
         */
        virtual ~SVGElement();

        /**
         * @brief Draws the SVG element on the given PNG image.
         * @param img The PNG image to draw on.
         */
        virtual void draw(PNGImage &img) const = 0;

        /**
         * @brief Applies a transformation to the SVG element.
         * @param t The transformation to apply.
         */
        virtual void transform(Transformation t) = 0;
    };

    /**
     * @brief Reads an SVG file and extracts its dimensions and SVG elements.
     * @param svg_file The path to the SVG file.
     * @param dimensions The dimensions of the SVG file.
     * @param svg_elements The vector to store the SVG elements.
     */
    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);

    /**
     * @brief Converts an SVG file to a PNG file.
     * @param svg_file The path to the SVG file.
     * @param png_file The path to the PNG file to be created.
     */
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    /**
     * @brief Represents an ellipse SVG element.
     */
    class Ellipse : public SVGElement
    {
    public:
        /**
         * @brief Constructor.
         * @param fill The fill color of the ellipse.
         * @param center The center point of the ellipse.
         * @param radius The radius of the ellipse.
         */
        Ellipse(const Color &fill, const Point &center, const Point &radius);

        /**
         * @brief Draws the ellipse on the given PNG image.
         * @param img The PNG image to draw on.
         */
        void draw(PNGImage &img) const override;

        /**
         * @brief Applies a transformation to the ellipse.
         * @param t The transformation to apply.
         */
        void transform(Transformation t) override final;

    protected:
        Color fill_;    //!< The fill color of the ellipse.
        Point center_;  //!< The center point of the ellipse.
        Point radius_;  //!< The radius of the ellipse.
    };

    /**
     * @brief Represents a circle SVG element.
     */
    class Circle : public Ellipse
    {
    public:
        /**
         * @brief Constructor.
         * @param fill The fill color of the circle.
         * @param center The center point of the circle.
         * @param radius The radius of the circle.
         */
        Circle(const Color &fill, const Point &center, const int &radius);
    };

    /**
     * @brief Represents a polygon SVG element.
     */
    class Polygon : public SVGElement
    {
    public:
        /**
         * @brief Constructor.
         * @param all_points The points that define the polygon.
         * @param fill The fill color of the polygon.
         */
        Polygon(const std::vector<Point> &all_points, const Color &fill);

        /**
         * @brief Draws the polygon on the given PNG image.
         * @param image The PNG image to draw on.
         */
        void draw(PNGImage &image) const override;

        /**
         * @brief Applies a transformation to the polygon.
         * @param t The transformation to apply.
         */
        void transform(Transformation t) override final;

    protected:
        Color fill_;                    //!< The fill color of the polygon.
        std::vector<Point> all_points_; //!< The points that define the polygon.
    };

    /**
     * @brief Represents a rectangle SVG element.
     */
    class Rectangle : public Polygon
    {
    public:
        /**
         * @brief Constructor.
         * @param upperL The upper-left corner of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         * @param fill The fill color of the rectangle.
         */
        Rectangle(const Point &upperL, const int &width, const int &height, const Color &fill);

        /**
         * @brief Returns the coordinates of the rectangle.
         * @param point The upper-left corner of the rectangle.
         * @param w The width of the rectangle.
         * @param h The height of the rectangle.
         * @return The coordinates of the rectangle.
         */
        std::vector<Point> get_rect_coordinates(Point point, const int &w, const int &h) const;
    };

    /**
     * @brief Represents a polyline SVG element.
     */
    class Polyline : public SVGElement
    {
    public:
        /**
         * @brief Constructor.
         * @param polyl_points The points that define the polyline.
         * @param stroke The stroke color of the polyline.
         */
        Polyline(const std::vector<Point> &polyl_points, const Color &stroke);

        /**
         * @brief Draws the polyline on the given PNG image.
         * @param img The PNG image to draw on.
         */
        void draw(PNGImage &img) const override;

        /**
         * @brief Applies a transformation to the polyline.
         * @param t The transformation to apply.
         */
        void transform(Transformation t) override final;

    protected:
        std::vector<Point> polyl_points_;   //!< The points that define the polyline.
        Color stroke_;                      //!< The stroke color of the polyline.
    };

    /**
     * @brief Represents a line SVG element.
     */
    class Line : public Polyline
    {
    public:
        /**
         * @brief Constructor.
         * @param start The starting point of the line.
         * @param end The ending point of the line.
         * @param stroke The stroke color of the line.
         */
        Line(const Point &start, const Point &end, const Color &stroke);
    };
}
#endif