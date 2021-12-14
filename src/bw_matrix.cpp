#include "bw_matrix.h"

#include <iomanip>
#include <iostream>
#include <stdexcept> 

BWMatrix::BWMatrix()
    : Matrix(0, 0, 1)
{}

BWMatrix::BWMatrix(const BWMatrix& mat)
    : Matrix(mat)
{}

BWMatrix::BWMatrix(size_t rows, size_t cols)
    : Matrix(rows, cols, 1)
{}

BWMatrix::BWMatrix(size_t rows, size_t cols, int initVal)
    : Matrix(rows, cols, 1, initVal)
{}

void BWMatrix::print() const
{
    std::cout << *this << std::endl;
}

void BWMatrix::fromOpenCV(const cv::Mat& mat)
{
    if (mat.channels() != 1 || mat.depth() != CV_8U)
        return;
    m_rows = mat.rows;
    m_cols = mat.cols;
    m_data.resize(mat.total());
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            at(r, c) = mat.at<uchar>(static_cast<int>(r), static_cast<int>(c));
        }
    }
}

cv::Mat BWMatrix::toOpenCV() const
{
    cv::Mat mat(static_cast<int>(m_rows), static_cast<int>(m_cols), CV_8UC1);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            mat.at<uchar>(static_cast<int>(r), static_cast<int>(c)) = at(r, c);
        }
    }
    return mat;
}

bool BWMatrix::readImage(const std::string& path)
{
    cv::Mat bwImage = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (bwImage.empty())
        return false;
    fromOpenCV(bwImage);
    return true;
}

BWMatrix BWMatrix::invert() const
{
    BWMatrix res = *this -255;
    res = res * (-1);
    return res;
}

BWMatrix& BWMatrix::operator=(const BWMatrix& mat)
{
    Matrix::operator=(mat);
    return *this;
}

BWMatrix BWMatrix::add(int val) const
{
    BWMatrix res(m_rows, m_cols);
    Matrix::add(res, val);
    return res;
}

BWMatrix BWMatrix::multiply(int val) const
{
    BWMatrix res(m_rows, m_cols);
    Matrix::multiply(res, val);
    return res;
}

BWMatrix BWMatrix::subtract(int val) const
{
    BWMatrix res(m_rows, m_cols);
    Matrix::subtract(res, val);
    return res;
}

BWMatrix BWMatrix::operator+(int val) const
{
    return add(val);
}

BWMatrix BWMatrix::operator-(int val) const
{
    return subtract(val);
}

BWMatrix BWMatrix::operator*(int val) const
{
    return multiply(val);
}

std::ostream& operator<<(std::ostream& out, const BWMatrix& mat)
{
    static const std::vector<std::string> names = {"r", "g", "b"};
    for (size_t r = 0; r < mat.m_rows; ++r) {
        for (size_t c = 0; c < mat.m_cols; ++c) {
            out << (c > 0 ? " " : "") << std::setw(2);
            out << "[";
            out << mat.at(r, c);
            out << "]";
        }
        out << std::endl;
    }
    return out;
}

void BWMatrix::draw(const Rectangle &rectangle) {
    auto color = rectangle.getColor()->getBWColor();
    Point corner = rectangle.getCorner();
    int width = rectangle.getWidth();
    int height = rectangle.getHeight();

    int min_y = std::max(0, corner.y);
    int min_x = std::max(0, corner.x);
    int max_y = std::min(static_cast<int>(m_rows), corner.y + height);
    int max_x = std::min(static_cast<int>(m_cols), corner.x + width);
   
    for (size_t y = min_y; y < max_y; y++) {
        std::fill(m_data.begin() + y * m_cols + min_x,
                  m_data.begin() + y * m_cols + max_x, 
                  color);
    }
}

void BWMatrix::draw(const Circle &circle) {
    auto color = circle.getColor()->getBWColor();
    Point center = circle.getCenter();
    int radius = circle.getRadius();

    int min_x = std::max(0, center.x - radius);
    int max_x = std::min(static_cast<int>(m_cols), center.x + radius);
    int min_y = std::max(0, center.y - radius);
    int max_y = std::min(static_cast<int>(m_rows), center.y + radius);

    for (int x = min_x; x < max_x; ++x) {
        for (int y = min_y; y < max_y; ++y) {
            if (circle.includes({x, y})) {
                at(y, x) = color;
            }
        }
    }
}

void BWMatrix::draw(const Triangle &triangle) {
    auto color = triangle.getColor()->getBWColor();
    Point A = triangle.getA();
    Point B = triangle.getB();
    Point C = triangle.getC();

    int min_x = std::max(0, std::min({A.x, B.x, C.x}));
    int max_x = std::min(static_cast<int>(m_cols), std::max({A.x, B.x, C.x}));
    int min_y = std::max(0, std::min({A.y, B.y, C.y}));
    int max_y = std::min(static_cast<int>(m_rows), std::max({A.y, B.y, C.y}));

    for (int x = min_x; x < max_x; ++x) {
        for (int y = min_y; y < max_y; ++y) {
            if (triangle.includes({x, y})) {
                at(y, x) = color;
            }
        }
    }
}