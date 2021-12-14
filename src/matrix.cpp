#include "matrix.h"

#include <iostream>
#include <iomanip>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


Matrix::Matrix()
    : m_rows(0)
    , m_cols(0)
{}

Matrix::Matrix(const Matrix& mat)
    : m_rows(mat.m_rows)
    , m_cols(mat.m_cols)
    , m_channels(mat.m_channels)
    , m_data(mat.m_data)
{}

Matrix::Matrix(size_t rows, size_t cols, size_t channels)
    : m_rows(rows)
    , m_cols(cols)
    , m_channels(std::max(channels, static_cast<size_t>(1)))
    , m_data(rows * cols * m_channels)
{}

Matrix::Matrix(size_t rows, size_t cols, size_t channels, int initValue)
    : m_rows(rows)
    , m_cols(cols)
    , m_channels(std::max(channels, static_cast<size_t>(1)))
    , m_data(rows * cols * m_channels, initValue)
{}

Matrix::Matrix(int num_rows, int num_cols)
    : m_rows(num_rows)
    , m_cols(num_cols)
    , m_data(num_rows * num_cols)
{}

void Matrix::display() const
{   
    cv::Mat res = toOpenCV();
    if (m_cols > 850) {
        cv::resize(res, res, cv::Size(), 0.5, 0.5);
        cv::namedWindow("Display image", cv::WINDOW_NORMAL);
    }    
    cv::imshow("Display image", res);
    cv::waitKey(0);
}

Matrix& Matrix::operator=(const Matrix &mat)
{
    if (this != &mat) {
        m_rows = mat.m_rows;
        m_cols = mat.m_cols;
        m_channels = mat.m_channels;
        m_data.assign(mat.m_data.begin(), mat.m_data.end());
    }
    return *this;
}

void Matrix::add(Matrix& res, int val) const
{
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        res.m_data[i] = m_data[i] + val;
    }
}

void Matrix::multiply(Matrix& res, int val) const
{
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        res.m_data[i] = m_data[i] * val;
    }
}

void Matrix::subtract(Matrix& res, int val) const
{
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        res.m_data[i] = m_data[i] - val;
    }
}