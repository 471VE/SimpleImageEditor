#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <array>


class Color
{
    public:
        virtual ~Color() = default;
        virtual std::array<unsigned char, 3> getRGBColor() const = 0;
        virtual unsigned char getBWColor() const = 0;
};


class BWColor: public Color
{
    public:
        explicit BWColor(unsigned char color) : m_color(color) {}
        void changeColor(unsigned char color) { m_color = color; }
        std::array<unsigned char, 3> getRGBColor() const override {
            return {m_color, m_color, m_color};
        }
        unsigned char getBWColor() const override { return m_color; }
    private:
        unsigned char m_color;
};


class RGBColor: public Color
{
    public:
        explicit RGBColor(unsigned char r, unsigned char g, unsigned char b): m_r(r), m_g(g), m_b(b) {}
        void changeColor(unsigned char r, unsigned char g, unsigned char b) { 
            m_r = r; m_g = g; m_b = b;
        }
        std::array<unsigned char, 3> getRGBColor() const override {return {m_r, m_g, m_b}; }
        unsigned char getBWColor() const override { return (m_r + m_g + m_b) / 3; }
    private:
        unsigned char m_r;
        unsigned char m_g;
        unsigned char m_b;
};

#endif // COLOR_H