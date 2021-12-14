#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "shapes.h"

class Matrix {
    public:
        Matrix();
        Matrix(const Matrix &mat);
        Matrix(size_t rows, size_t cols, size_t channels);
        Matrix(size_t rows, size_t cols, size_t channels, int initValue);
        Matrix(int num_rows, int num_cols);

        inline size_t getRows() const { return m_rows; }
        inline size_t getCols() const { return m_cols; }
        inline size_t getChannels() const { return m_channels; }
        
        inline const int& at(size_t row, size_t col, size_t channel = 0) const {
            return m_data[row * m_cols * m_channels + col * m_channels + channel];
        }
        inline int& at(size_t row, size_t col, size_t channel = 0) {
            return m_data[row * m_cols * m_channels + col * m_channels + channel];
        }

        virtual void print() const = 0;
        virtual void fromOpenCV(const cv::Mat& mat) = 0;
        virtual cv::Mat toOpenCV() const = 0;
        virtual bool readImage(const std::string& path) = 0;
        void display() const;

        Matrix& operator=(const Matrix &mat);

        virtual void draw(const Rectangle& shape) = 0;
        virtual void draw(const Circle& shape) = 0;
        virtual void draw(const Triangle& shape) = 0;

    protected:
        void add(Matrix& res, int val) const;
        void multiply(Matrix& res, int val) const;
        void subtract(Matrix& res, int val) const;

    protected:
        size_t m_rows;
        size_t m_cols;
        size_t m_channels;
        std::vector<int> m_data;
};

#endif // MATRIX_H