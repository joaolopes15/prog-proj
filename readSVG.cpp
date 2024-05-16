
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include "Color.hpp"
using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        XMLElement *child_elem = xml_elem->FirstChildElement();
        while (child_elem != nullptr){
            const char *elem_name = child_elem->Value();
            if (strcmp(elem_name, "rect") == 0)
            {
            int x = child_elem->IntAttribute("x");
            int y = child_elem->IntAttribute("y");
            int width = child_elem->IntAttribute("width");
            int height = child_elem->IntAttribute("height");
            string fill = child_elem->Attribute("fill");
            SVGElement *rect = new Rectangle({x, y}, width, height, parse_color(fill));
            svg_elements.push_back(rect);
            }
            else if (strcmp(elem_name, "circle") == 0)
            {
            int cx = child_elem->IntAttribute("cx");
            int cy = child_elem->IntAttribute("cy");
            int r = child_elem->IntAttribute("r");
            string fill = child_elem->Attribute("fill");
            SVGElement *circle = new Circle(parse_color(fill), {cx, cy}, r);
            svg_elements.push_back(circle);
            }
            else if (strcmp(elem_name, "line") == 0)
            {
            int x1 = child_elem->IntAttribute("x1");
            int y1 = child_elem->IntAttribute("y1");
            int x2 = child_elem->IntAttribute("x2");
            int y2 = child_elem->IntAttribute("y2");
            string stroke = child_elem->Attribute("stroke");
            SVGElement *line = new Line({x1, y1}, {x2, y2}, parse_color(stroke));
            svg_elements.push_back(line);
            }

            else if (strcmp(elem_name, "polyline") == 0)
            {
                vector<Point> polyl_points;
                const char* points_str = child_elem->Attribute("points");
                //coordinates are separated by "," and points are separated by " "
                char* point = strtok(const_cast<char*>(points_str), " "); //Splits the string in the first space
                while (point != nullptr){ 
                    char* x_str = strtok(point, ","); //Splits the (already splitted) string in the first comma
                    char* y_str = strtok(nullptr, ","); 
                    //stoi - string to int 
                    int x = stoi(x_str);
                    int y = stoi(y_str);
                    //store coordinates in the polyl_points vector
                    polyl_points.push_back({x, y});
                    //next point
                    point = strtok(nullptr, " ");
                }
                    string stroke = child_elem->Attribute("stroke");
                    SVGElement* polyline = new Polyline(polyl_points, parse_color(stroke));
                    svg_elements.push_back(polyline);
            } 

            else if (strcmp(elem_name, "polygon") == 0)
            {
                vector<Point> all_points;
                const char* points_str = child_elem->Attribute("points");
                // coordinates are separated by "," and points are separated by " "
                char* point = strtok(const_cast<char*>(points_str), " "); // Splits the string in the first space
                while (point != nullptr)
                {
                    char* x_str = strtok(point, ","); // Splits the (already splitted) string in the first comma
                    char* y_str = strtok(nullptr, ",");
                    // stoi - string to int
                    int x = stoi(x_str);
                    int y = stoi(y_str);
                    // store coordinates in the all_points vector
                    all_points.push_back({x, y});
                    // next point
                    point = strtok(nullptr, " ");
                }
                string fill = child_elem->Attribute("fill");
                SVGElement* polygon = new Polygon(all_points, parse_color(fill));
                svg_elements.push_back(polygon);
            }
            else if (strcmp(elem_name, "ellipse") == 0){
                int cx = child_elem->IntAttribute("cx");
                int cy = child_elem->IntAttribute("cy");
                int rx = child_elem->IntAttribute("rx");
                int ry = child_elem->IntAttribute("ry");
                string fill = child_elem->Attribute("fill");
                SVGElement* ellipse = new Ellipse(parse_color(fill), {cx, cy}, {rx, ry});
                svg_elements.push_back(ellipse);
            }
            else if (strcmp(elem_name, "use") == 0){
                string href = child_elem->Attribute("href");
                string transform = child_elem->Attribute("transform");
                string id = child_elem->Attribute("id");
            }
        }
            child_elem = child_elem->NextSiblingElement();
        } 
    }


