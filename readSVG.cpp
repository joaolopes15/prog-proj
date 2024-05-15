
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
        
        /* XMLElement *child_elem = xml_elem->FirstChildElement();
        while (child_elem != nullptr)
        {
            const char *elem_name = child_elem->Value();
            if (strcmp(elem_name, "rect") == 0)
            {
            int x = child_elem->IntAttribute("x");
            int y = child_elem->IntAttribute("y");
            int width = child_elem->IntAttribute("width");
            int height = child_elem->IntAttribute("height");
            string fill = child_elem->Attribute("fill");
            SVGElement *rect = new Rectangle(x, y, width, height, parse_color(fill));
            svg_elements.push_back(rect);
            }
            else if (strcmp(elem_name, "circle") == 0)
            {
            int cx = child_elem->IntAttribute("cx");
            int cy = child_elem->IntAttribute("cy");
            int r = child_elem->IntAttribute("r");
            string fill = child_elem->Attribute("fill");
            SVGElement *circle = new Circle(cx, cy, r, parse_color(fill));
            svg_elements.push_back(circle);
            }
            else if (strcmp(elem_name, "line") == 0)
            {
            int x1 = child_elem->IntAttribute("x1");
            int y1 = child_elem->IntAttribute("y1");
            int x2 = child_elem->IntAttribute("x2");
            int y2 = child_elem->IntAttribute("y2");
            string stroke = child_elem->Attribute("stroke");
            SVGElement *line = new Line(x1, y1, x2, y2, parse_color(stroke));
            svg_elements.push_back(line);
            }
            // Add more conditions for other SVG element types here

            child_elem = child_elem->NextSiblingElement();
        } */
        // TODO complete code -->
        
    }
}