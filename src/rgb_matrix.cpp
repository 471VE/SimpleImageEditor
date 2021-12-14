#include "rgb_matrix.h"
#include <iomanip>
#include <iostream>

RGBMatrix::RGBMatrix()
    : Matrix(0, 0, 3)
{}

RGBMatrix::RGBMatrix(const RGBMatrix& mat)
    : Matrix(mat)
{}

RGBMatrix::RGBMatrix(size_t rows, size_t cols)
    : Matrix(rows, cols, 3)
{}

RGBMatrix::RGBMatrix(size_t rows, size_t cols, int initVal)
    : Matrix(rows, cols, 3, initVal)
{}

void RGBMatrix::print() const
{
    std::cout << *this << std::endl;
}

void RGBMatrix::fromOpenCV(const cv::Mat& mat)
{
    if (mat.channels() != 3 || mat.depth() != CV_8U)
        return;
    m_rows = mat.rows;
    m_cols = mat.cols;
    m_data.resize(mat.total() * mat.channels());
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            auto val = mat.at<cv::Vec3b>(static_cast<int>(r), static_cast<int>(c));
            at(r, c, 0) = val[2];
            at(r, c, 1) = val[1];
            at(r, c, 2) = val[0];
        }
    }
}

cv::Mat RGBMatrix::toOpenCV() const
{
    cv::Mat mat(static_cast<int>(m_rows), static_cast<int>(m_cols), CV_8UC3);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            cv::Vec3b val;
            val[0] = at(r, c, 2);
            val[1] = at(r, c, 1);
            val[2] = at(r, c, 0);
            mat.at<cv::Vec3b>(static_cast<int>(r), static_cast<int>(c)) = val;
        }
    }
    return mat;
}

bool RGBMatrix::readImage(const std::string& path)
{
    cv::Mat rgbImage = cv::imread(path, cv::IMREAD_COLOR);
    if (rgbImage.empty())
        return false;
    fromOpenCV(rgbImage);
    return true;
}

BWMatrix RGBMatrix::toBW() const
{
    BWMatrix res(m_rows, m_cols);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            int gray = 0;
            for (size_t ch = 0; ch < m_channels; ++ch) {
                gray += at(r, c, ch);
            }
            res.at(r, c) = gray / static_cast<int>(m_channels);
        }
    }
    return res;
}

RGBMatrix& RGBMatrix::operator=(const RGBMatrix& mat)
{
    Matrix::operator=(mat);
    return *this;
}


RGBMatrix RGBMatrix::add(int val) const
{
    RGBMatrix res(m_rows, m_cols);
    Matrix::add(res, val);
    return res;
}

RGBMatrix RGBMatrix::multiply(int val) const
{
    RGBMatrix res(m_rows, m_cols);
    Matrix::multiply(res, val);
    return res;
}

RGBMatrix RGBMatrix::subtract(int val) const
{
    RGBMatrix res(m_rows, m_cols);
    Matrix::subtract(res, val);
    return res;
}

RGBMatrix RGBMatrix::operator+(int val) const
{
    return add(val);
}

RGBMatrix RGBMatrix::operator-(int val) const
{
    return subtract(val);
}

RGBMatrix RGBMatrix::operator*(int val) const
{
    return multiply(val);
}

std::ostream& operator<<(std::ostream& out, const RGBMatrix& mat)
{
    static const std::vector<std::string> names = {"r", "g", "b"};
    for (size_t r = 0; r < mat.m_rows; ++r) {
        for (size_t c = 0; c < mat.m_cols; ++c) {
            out << (c > 0 ? " " : "") << std::setw(2);
            out << "[";
            for (size_t ch = 0; ch < mat.m_channels; ++ch) {
                out << (ch > 0 ? ", " : "") << std::setw(3);
                out << names[ch] << ": " << mat.at(r, c, ch);
            }
            out << "]";
        }
        out << std::endl;
    }
    return out;
}

void RGBMatrix::draw(const Rectangle &rectangle) {
    auto color = rectangle.getColor()->getRGBColor();
    int width = rectangle.getWidth();
    int height = rectangle.getHeight();
    Point corner = rectangle.getCorner();

    int min_y = std::max(0, corner.y);
    int min_x = std::max(0, corner.x);
    int max_y = std::min(static_cast<int>(m_rows), corner.y + height);
    int max_x = std::min(static_cast<int>(m_cols), corner.x + width);

    std::vector<int> color_vector((max_x - min_x) * m_channels, 0);
    for (size_t idx = 0; idx < color_vector.size(); idx += m_channels) {
        color_vector[idx] = color[0];
        color_vector[idx + 1] = color[1];
        color_vector[idx + 2] = color[2];
    }

    for (size_t y = min_y; y < max_y; y++) {
        std::copy(color_vector.begin(), color_vector.end(),
                  m_data.begin() + y * m_cols * m_channels + min_x * m_channels);
    }
}

void RGBMatrix::draw(const Circle &circle) {
    auto color = circle.getColor()->getRGBColor();
    Point center = circle.getCenter();
    int radius = circle.getRadius();

    int min_x = std::max(0, center.x - radius);
    int max_x = std::min(static_cast<int>(m_cols), center.x + radius);
    int min_y = std::max(0, center.y - radius);
    int max_y = std::min(static_cast<int>(m_rows), center.y + radius);

    for (int x = min_x; x < max_x; ++x) {
        for (int y = min_y; y < max_y; ++y) {
            if (circle.includes({x, y})) {
                at(y, x, 0) = color[0];
                at(y, x, 1) = color[1];
                at(y, x, 2) = color[2];
            }
        }
    }
}

void RGBMatrix::draw(const Triangle &triangle) {
    auto color = triangle.getColor()->getRGBColor();
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
                at(y, x, 0) = color[0];
                at(y, x, 1) = color[1];
                at(y, x, 2) = color[2];
            }
        }
    }
}