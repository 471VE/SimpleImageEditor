#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <array>
#include "color.h"
#include "point.h"
#include "helper_functions.h"


class Shape
{
    public:
        virtual ~Shape() { delete m_color; }
        std::vector<Point> getPoints() const { return m_points; }
        const Color* getColor() const { return m_color; }

    protected:
        template<typename T, std::enable_if_t<std::is_base_of<Color, T>::value, bool> = true>
        Shape(const T& color) { m_color = new T(color); }

    protected:
        std::vector<Point> m_points;
        Color* m_color;
};


class Rectangle : public Shape
{
    public:
        template<typename T, std::enable_if_t<std::is_base_of<Color, T>::value, bool> = true>
        Rectangle(const Point& corner, const int& width, const int& height, const T& color)
            : Shape(color)
            , m_corner(corner)
            , m_width(width)
            , m_height(height)
        {}

        unsigned int getWidth() const { return m_width; }
        unsigned int getHeight() const { return m_height; }
        Point getCorner() const { return m_corner; }

    protected:
        Point m_corner;
        int m_width;
        int m_height;
};


class Circle : public Shape
{
    public:
        template<typename T, std::enable_if_t<std::is_base_of<Color, T>::value, bool> = true>
        Circle(const Point& center, const int& radius, const T& color)
            : Shape(color)
            , m_center(center)
            , m_radius(radius)
        {}
        
        Point getCenter() const { return m_center; }
        unsigned int getRadius() const { return m_radius; }
        bool includes(Point P) const {
            return ((m_center.x - P.x) * (m_center.x - P.x) +
                    (m_center.y - P.y) * (m_center.y - P.y) <=
                    m_radius * m_radius);
        }

    protected:
        Point m_center;
        int m_radius;
};


class Triangle : public Shape
{
    public:
        template<typename T, std::enable_if_t<std::is_base_of<Color, T>::value, bool> = true>
        Triangle(const Point& vertexA, const Point& vertexB, const Point& vertexC, const T& color)
            : Shape(color)
            , A(vertexA)
            , B(vertexB)
            , C(vertexC)
        {   area_doubled = TriangleAreaDoubled(A, B, C); }

        int getAreaDoubled() const { return area_doubled; }

        Point getA() const { return A; }
        Point getB() const { return B; }
        Point getC() const { return C; }

        bool includes(const Point &P) const {
            double ABP2 = TriangleAreaDoubled(A, B, P);
            double BCP2 = TriangleAreaDoubled(B, C, P);
            double CAP2 = TriangleAreaDoubled(C, A, P);
            bool includes = (area_doubled == (ABP2 + BCP2 + CAP2));
            return includes;
        }

    protected:
        Point A;
        Point B;
        Point C;
        int area_doubled;
};

#endif // SHAPE_H