//
//  Matrix.h
//  face-detection
//
//  Created by Nicolas Meny on 23/06/2014.
//
//

#ifndef face_detection_Matrix_h
#define face_detection_Matrix_h

#include <iostream>
#include <vector>

template<class T>
class Matrix
{
public:
    Matrix(int n, int m, T default_value = 0)
    : _size_n(n),
      _size_m(m)
    {
        int size = n * m;
        for (int i = 0; i < size; ++i){
            _matrix.push_back(default_value);
        }
    };
    
    Matrix()
    : _size_n(0),
      _size_m(0)
    {};
    
    Matrix<T> operator* (Matrix<T> m)
    {
        Matrix<T> Result;
        
        //    for (int i = 0; i < 4; i++){
        //        for (int j = 0; j < 4; j++){
        //            float sum = 0;
        //            for (int k = 0; k < 4; k++){
        //                sum += Matrix[j + k * 4] * m.Matrix[i * 4 + k];
        //            }
        //            Result.Matrix[i * 4 + j] = sum;
        //        }
        //    }
        
        return Result;
    };
    
    
    T& operator[] (int i)
    {
        return _matrix[i];
    };
    
    int get_size_n()
    {
        return _size_n;
    };
    
    int get_size_m()
    {
        return _size_m;
    };
    
private:
    int _size_n;
    int _size_m;
    std::vector<T> _matrix;
};

template<typename T>
std::ostream& operator<< (std::ostream& out, Matrix<T> matrix)
{
    int n = matrix.get_size_n();
    int m = matrix.get_size_m();
    
    for (int i = 0; i < n ; i++){
        for (int j = 0; j < m; j++){
            out << " | " << matrix[i * m + j];
        }
        out << " " << std::endl;
    }
    
    return out;
};

#endif


