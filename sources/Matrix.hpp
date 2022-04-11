//
// Created by bravo8234 on 03/04/2022.
//

#ifndef EX3_CPP_A_MATRIX_HPP
#define EX3_CPP_A_MATRIX_HPP
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
namespace zich {
    class Matrix {
    private:
        std::vector<std::vector<double>> mat;
        size_t rowsNum;
        size_t colNum;
    public:
        Matrix(std::vector<double> vector, size_t rowNum, size_t colNum);
        Matrix(Matrix& other);
        Matrix(const Matrix& other);
        ~Matrix();
        //getters
        std::vector<double> getMatrixAsVector();
        size_t getRowsNum() const{return this->rowsNum;}
        size_t getColsNum() const{return this->colNum;}
        std::vector<std::vector<double>>& getMat() {return this->mat;}
        //addition operators
        Matrix &operator+=(double x);

        Matrix &operator+=(Matrix &second);

        friend Matrix operator+(Matrix& mat, double x);
        friend Matrix operator+(const Matrix& mat, double x);
        friend Matrix operator+(Matrix& first, Matrix &second);

        Matrix &operator+();

        Matrix &operator++();

        Matrix operator++(int);

        Matrix& operator=(Matrix first);

        //subtraction operators
        Matrix &operator-=(double x);

        Matrix &operator-=(Matrix &second);

        friend Matrix operator-(double x, Matrix mat);

        friend Matrix operator-(Matrix mat, double x);

        friend Matrix operator-(Matrix first, Matrix &second);

        Matrix &operator-();

        Matrix &operator--();

        Matrix operator--(int);

        //boolean operators
        friend bool operator<(Matrix& first, Matrix &other);

        friend bool operator>(Matrix& first, Matrix &other);

        friend bool operator<=(Matrix& first, Matrix &other);

        friend bool operator>=(Matrix& first, Matrix &other);

        friend bool operator==(Matrix& first, Matrix &other);

        friend bool operator!=(Matrix& first, Matrix &other);

        //multiplication operators
        Matrix &operator*=(double x);

        friend Matrix operator*(Matrix& mat, double x);
        friend Matrix operator*(const Matrix& mat, double x);

        friend Matrix operator*(double x, Matrix mat);

        Matrix &operator*=(Matrix &other);

        friend Matrix operator*(Matrix first, Matrix &second);

        //input,output operators
        friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);

        friend std::istream &operator>>(std::istream &is,Matrix& mat);

        //helper
        double getCombinationValue(size_t row, size_t column, Matrix& other);
    };



}
#endif //EX3_CPP_A_MATRIX_HPP
