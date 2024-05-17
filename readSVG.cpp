#include <iostream>
#include <sstream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include "Color.hpp"
#include <string>
using namespace std;
using namespace tinyxml2;

namespace svg
{

    void comma_remover(string &old_str)

    {
        for (char &c : old_str)
        {
            if (c == ',')
            {
                c = ' ';
            }
        }
    }

    bool translate(const string& translate){
        return translate.substr(0, 9) == "translate";
    }

    bool rotate(const string& rotate){
        return rotate.substr(0, 6) == "rotate";
    }

    bool scale(const string& scale){
        return scale.substr(0, 5) == "scale";
    }
    void iterating_tranformations(vector<Transformation> t_vector, SVGElement* svg_elem){
        for (long unsigned int i = 0; i< t_vector.size(); i++){
            svg_elem->transform(t_vector[i]);
        }
    }

    Transformation getTransformation(const XMLElement *elem)
    {
        int translationX = 0;
        int translationY = 0;
        int rotation = 0;
        int s_factor = 1;
        int originX = 0;
        int originY = 0;

        if (elem != nullptr){
            const char *p = elem->Attribute("transform");

            if (p != nullptr){   
                const char *trans_point = elem->Attribute("transform-origin"); 
                if (trans_point != nullptr){
                        istringstream ss(trans_point); 
                        ss >> originX >> originY;
                }

                string transform_str = p;
                comma_remover(transform_str);

                if (translate(transform_str)){
                    // Extract translation values
                    int pos1 = transform_str.find('(') + 1;
                    int pos2 = transform_str.find(' ');
                    translationX = stoi(transform_str.substr(pos1, pos2 - pos1));
                    pos1 = pos2 + 1;
                    pos2 = transform_str.find(')');
                    translationY = stoi(transform_str.substr(pos1, pos2 - pos1));
                }
                else if (rotate(transform_str))
                {
                    // Extract rotation value
                    int pos1 = transform_str.find('(') + 1;
                    int pos2 = transform_str.find(')');
                    rotation = stoi(transform_str.substr(pos1, pos2 - pos1));
                }
                else if(scale(transform_str))
                {
                    int pos1 = transform_str.find('(') + 1;
                    int pos2 = transform_str.find(')');
                    s_factor = stoi(transform_str.substr(pos1, pos2 - pos1));
                }
            }
        }
        return Transformation{Point{translationX, translationY}, rotation, s_factor, Point{originX, originY}};
    }
    void create_elems(XMLElement* xml_elem, vector<SVGElement *> &svg_elements, vector<Transformation> &t_vector){
        for (XMLElement *child_elem = xml_elem->FirstChildElement(); child_elem != nullptr; child_elem = child_elem->NextSiblingElement())
        {
            const char *elem_name = child_elem->Value();

            if (strcmp(elem_name, "rect") == 0)
            {
                int x = child_elem->IntAttribute("x");
                int y = child_elem->IntAttribute("y");
                int width = child_elem->IntAttribute("width");
                int height = child_elem->IntAttribute("height");
                string fill = child_elem->Attribute("fill");

                SVGElement *rect = new Rectangle({x, y}, width, height, parse_color(fill));
                rect->transform(getTransformation(child_elem));
                iterating_tranformations(t_vector,rect);
        
                svg_elements.push_back(rect);
            }

            else if (strcmp(elem_name, "circle") == 0)
            {
                int cx = child_elem->IntAttribute("cx");
                int cy = child_elem->IntAttribute("cy");
                int r = child_elem->IntAttribute("r");
                string fill = child_elem->Attribute("fill");

                SVGElement *circle = new Circle(parse_color(fill), {cx, cy}, r);
                circle->transform(getTransformation(child_elem));
                iterating_tranformations(t_vector,circle);

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
                line->transform(getTransformation(child_elem));
                iterating_tranformations(t_vector,line);

                svg_elements.push_back(line);
            }

            else if (strcmp(elem_name, "ellipse") == 0)
            {
                int cx = child_elem->IntAttribute("cx");
                int cy = child_elem->IntAttribute("cy");
                int rx = child_elem->IntAttribute("rx");
                int ry = child_elem->IntAttribute("ry");
                string fill = child_elem->Attribute("fill");

                SVGElement *ellipse = new Ellipse(parse_color(fill), {cx, cy}, {rx, ry});
                ellipse->transform(getTransformation(child_elem));
                iterating_tranformations(t_vector,ellipse);

                svg_elements.push_back(ellipse);
            }

            else if (strcmp(elem_name, "polyline") == 0)
            {
                vector<Point> polyl_points;
                string points_str = child_elem->Attribute("points");
                comma_remover(points_str);
                std::istringstream str_ss(points_str);
                Point temp;
                while (str_ss >> temp.x)
                {
                    str_ss >> temp.y;
                    polyl_points.push_back(temp);
                }
                string stroke = child_elem->Attribute("stroke");

                SVGElement *polyline = new Polyline(polyl_points, parse_color(stroke));
                polyline->transform(getTransformation(child_elem));
                iterating_tranformations(t_vector,polyline);

                svg_elements.push_back(polyline);
            }

            else if (strcmp(elem_name, "polygon") == 0)
            {
                vector<Point> all_points;
                string points_str = child_elem->Attribute("points");
                comma_remover(points_str);
                std::istringstream str_ss(points_str);
                Point temp;
                while (str_ss >> temp.x)
                {
                    str_ss >> temp.y;
                    all_points.push_back(temp);
                }

                string fill = child_elem->Attribute("fill");

                SVGElement *polygon = new Polygon(all_points, parse_color(fill));
                polygon->transform(getTransformation(child_elem));
                iterating_tranformations(t_vector,polygon);

                svg_elements.push_back(polygon);
            }
            else if (strcmp(elem_name,"g")== 0)
            {
                t_vector.push_back(getTransformation(child_elem));
                create_elems(child_elem,svg_elements,t_vector);
                t_vector.pop_back();
            }
        }
    }
    void readSVG(const string &svg_file, Point &dimensions, vector<SVGElement *> &svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();
        vector <Transformation > transformations = {getTransformation(nullptr)};

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
              
        create_elems(xml_elem,svg_elements, transformations);

    }
}
