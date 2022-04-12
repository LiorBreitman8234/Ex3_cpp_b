//
// Created by bravo8234 on 03/04/2022.
//
#include "Matrix.hpp"

#include <utility>
namespace zich{
    std::vector<double> Matrix::getMatrixAsVector() const {
        std::vector<double> toRet;
        for(size_t i =0; i < this->rowsNum;i++)
        {
            for(size_t j =0; j < this->colNum ;j++) {
                toRet.push_back(this->mat.at(i).at(j));
            }
        }
        return toRet;
    }

    Matrix::Matrix(std::vector<double> vector, int rowNum, int colNum) {
        if(vector.size() != rowNum*colNum)
        {
            throw std::invalid_argument("vector wrong size");
        }
        if(rowNum <= 0 || colNum <= 0)
        {
            throw std::invalid_argument("matrix col or row must be positive");
        }
        for(size_t i =0; i < rowNum;i++)
        {
            this->mat.emplace_back();
            std::copy(vector.begin()+((long)(i*(unsigned long)colNum)),vector.begin()+((long)(i*(unsigned long)colNum))+(int)colNum, std::back_inserter(this->mat.at(i)));
        }
        this->colNum = colNum;
        this->rowsNum = rowNum;
    }
    bool operator==(const Matrix& first, const Matrix& other)
    {
        if(first.getRowsNum() != other.getRowsNum() || first.getColsNum() != other.getColsNum()){
            throw std::invalid_argument("matrices have to be same size");
        }
        std::vector<double> firstVect = first.getMatrixAsVector();
        std::vector<double> secondVect = other.getMatrixAsVector();
        return (firstVect == secondVect);
    }
    bool operator!=(const Matrix& first,const Matrix& other)
    {
        return !(first == other);
    }

    bool operator>(const Matrix& first,const  Matrix& other){
        if( first.colNum!= other.colNum || first.rowsNum != other.rowsNum)
        {
            throw std::invalid_argument("matrices not the same size");
        }
        if(first.getRowsNum() != other.getRowsNum() || first.getColsNum() != other.getColsNum())
        {
            throw std::invalid_argument("matrices have to be same size");
        }
        std::vector<double> firstVec = first.getMatrixAsVector();
        std::vector<double> secondVec = other.getMatrixAsVector();
        double sum1 = 0;
        double sum2 = 0;
        for(double i : firstVec)
        {
            sum1 += i;
        }
        for(double i : secondVec)
        {
            sum2 += i;
        }
        return sum1>sum2;
    }

    bool operator<(const Matrix& first,const Matrix& other)
    {
        return other>first;
    }

    bool operator<=(const Matrix& first,const Matrix& other)
    {
        return !(first>other);
    }

    bool operator>=(const Matrix& first,const Matrix& other)
    {
        return !(first<other);
    }

    Matrix &Matrix::operator+=(double x) {
        for(size_t i =0; i < this->rowsNum;i++)
        {
            for(size_t j =0; j < this->colNum;j++)
            {
                this->mat.at(i).at(j) +=x;
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& mat, double x){
        auto* copy = new Matrix(mat);
        *copy+=x;
        return *copy;
    }

    Matrix& Matrix::operator+=(const Matrix &second) {
        if(this->rowsNum != second.getRowsNum() || this->colNum != second.getColsNum()){
            throw std::invalid_argument("matrices need to be in same size");
        }
        for(size_t i =0; i < this->rowsNum;i++)
        {
            for(size_t j =0; j < this->colNum;j++)
            {
                this->mat.at(i).at(j) += second.mat.at(i).at(j);
            }
        }
        return *this;
    }
    Matrix operator+(const Matrix& first,const Matrix& second){
        Matrix copy = first;
        copy += second;
        return copy;
    }

    Matrix& Matrix::operator+() {
        return *this;
    }

    Matrix &Matrix::operator++() {
        *this+=1;
        return *this;
    }

    Matrix Matrix::operator++(int) {
        Matrix old = *this;
        operator++();
        return old;
    }

    Matrix& Matrix::operator=(Matrix first) {
        if (this == &first) {
            return *this;
        }
        this->mat = std::vector<std::vector<double>>();
        this->rowsNum = first.getRowsNum();
        this->colNum = first.getColsNum();
        for (size_t i = 0; i < this->rowsNum; i++) {
            mat.emplace_back(std::vector<double>());
            for (size_t j = 0; j < this->colNum; j++) {
                this->mat.at(i).push_back(first.getMat().at(i).at(j));
            }
        }
        return *this;
    }

    Matrix &Matrix::operator-=(double x) {
        for(size_t i =0; i < this->rowsNum;i++)
        {
            for(size_t j =0; j < this->colNum;j++)
            {
                this->mat.at(i).at(j) -= x;
            }
        }
        return *this;
    }

    Matrix &Matrix::operator-=(Matrix &second) {
        if(this->rowsNum != second.getRowsNum() || this->colNum != second.getColsNum()){
            throw std::invalid_argument("matrices need to be in same size");
        }
        for(size_t i =0; i < this->rowsNum;i++)
        {
            for(size_t j =0; j < this->colNum;j++)
            {
                this->mat.at(i).at(j) -= second.getMat().at(i).at(j);
            }
        }
        return *this;
    }

    Matrix operator-(double x, Matrix mat) {
        return (mat-=x);
    }
    Matrix operator-(Matrix mat, double x) {
        return (mat-=x);
    }

    Matrix operator-(Matrix first, Matrix &second) {
        Matrix copy = first;
        copy -= second;
        return (copy);
    }

    Matrix &Matrix::operator-() {
        auto* copy = new Matrix(*this);
        return (*copy)*=-1;

    }

    Matrix &Matrix::operator*=(double x) {
        for(int i =0 ; i < this->rowsNum;i++)
        {
            for(int j =0; j < this->colNum;j++)
            {
                if(this->mat.at((unsigned long)i).at((unsigned long)j) == 0)
                {
                    continue;
                }
                this->mat.at((unsigned long)i).at((unsigned long)j)*=x;
            }
        }
        return *this;
    }

    Matrix operator*(Matrix& mat, double x) {
        Matrix copy = Matrix(mat);
        return copy*=x;
    }

    Matrix operator*(double x, Matrix mat) {
        return mat*=x;
    }

    Matrix &Matrix::operator*=(Matrix &other) {
        if(this->colNum!= other.rowsNum)
        {
            throw std::invalid_argument("first matrix columns need to be the same as second matrix rows");
        }
        std::vector<std::vector<double>> newMat;
        for(size_t i =0; i < this->rowsNum;i++)
        {
            newMat.emplace_back(std::vector<double>((unsigned long)other.colNum,0));
            for(size_t j =0; j < other.getColsNum();j++)
            {
                double newValue = 0;
                for(size_t k = 0; k < other.getRowsNum();k++)
                {
                    newValue += this->mat.at(i).at(k) * other.getMat().at(k).at(j);
                }
                newMat.at(i).at(j) = newValue;
            }
        }
        this->mat = newMat;
        this->colNum = other.colNum;
        return *this;
    }

    Matrix operator*(Matrix first, Matrix &second) {
        return first*=second;
    }

    Matrix &Matrix::operator--() {
        *this-=1;
        return *this;
    }

    Matrix Matrix::operator--(int) {
        Matrix copy = *this;
        operator--();
        return copy;
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
        for(size_t i =0; i < mat.getRowsNum();i++)
        {
            os << "[";
            for(size_t j =0; j < mat.getColsNum();j++)
            {
                if(j != mat.getColsNum()-1)
                {
                    os << mat.mat.at(i).at(j) << " ";

                }
                else
                {
                    os << mat.mat.at(i).at(j);
                }
            }
            if(i != mat.getRowsNum()-1)
            {
                os << "]" <<std::endl;

            }
            else
            {
                os << "]";
            }
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Matrix& mat) {
        std::string data;
        while(!is.eof())
        {
            std::string curr;
            is>>curr;
            curr += ' ';
            data += curr;
        }
        if(data.at(data.length()-1) == ' ')
        {
            data.pop_back();
        }
        if(data.at(0) != '[' && data.at(0) != ' ')
        {
            throw std::invalid_argument("wrong input");
        }
        for(size_t i =0; i < data.length()-1;i++)
        {
            if(data.at(i) == ',' && data.at(i+1) != ' ')
            {
                throw std::invalid_argument("wrong input");
            }
            if(i != data.length() -2 && data.at(i) == ']' && data.at(i+1) != ',')
            {
                throw std::invalid_argument("wrong input");
            }
            if(data.at(i) == '[' && data.at(i+1) > '9' && data.at(i+1) < '0')
            {
                throw std::invalid_argument("wrong input");
            }

        }
        std::vector<std::string> rows;
       for(char i: data)
       {
           if(i == ']')
           {
               rows.emplace_back(std::string());
           }
       }
       size_t index = 0;
       size_t stringIndex = 0;
       while(index < rows.size())
       {
           if(data.at(stringIndex) == ']')
           {
               rows.at(index).push_back(data.at(stringIndex));
               index++;
           }
           else
           {
               rows.at(index).push_back(data.at(stringIndex));
           }
           stringIndex++;
       }
       std::vector<std::string> newRows;
       for(std::string row: rows)
       {
           while(row.at(0) != '[')
           {
               row.erase(row.begin());
           }
           row.erase(row.begin());
           row.pop_back();
           newRows.push_back(row);
       }
       std::vector<std::vector<double>> matRows;
       for(size_t i =0; i < newRows.size();i++)
       {
           matRows.emplace_back(std::vector<double>());
           std::string number;
           for(size_t j = 0 ; j < newRows.at(i).size(); j++)
           {
               if(newRows.at(i).at(j) != ' ') {
                   number.push_back(newRows.at(i).at(j));
               }
               else
               {
                   double num = std::stod(number);
                   matRows.at(i).push_back(num);
                   number.clear();
               }
           }
       }
       for(size_t i = 0 ; i < matRows.size() - 1;i++)
       {
           if(matRows.at(i).size() != matRows.at(i+1).size())
           {
               is.setstate(std::ios::failbit);
               return is;
           }
       }
       mat.mat = matRows;
       mat.rowsNum = matRows.size();
       mat.colNum = matRows.at(0).size();
       return is;
    }

    Matrix::Matrix(Matrix &other) {
        this->colNum = other.colNum;
        this->rowsNum = other.rowsNum;
        this->mat = other.mat;
    }

    Matrix::~Matrix() = default;

    Matrix::Matrix(const Matrix &other) {
        this->colNum = other.colNum;
        this->rowsNum = other.rowsNum;
        this->mat = other.mat;
    }

    Matrix operator*(const Matrix &mat, double x) {
        Matrix copy = Matrix(mat);
        return copy*=x;
    }


};