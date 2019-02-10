#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace Cubical
{
    //  array typedef
    template<typename T>
    using array = std::vector<std::vector<T> >;
    
    template<typename T>
    class Matrix
    {
        public:
            Matrix<T>();
            virtual ~Matrix<T>();
            Matrix<T>(unsigned int n, unsigned int m);
            Matrix<T>(array<T> mat);
            Matrix<T>(const std::string& filename);

            //  getters and setters
            unsigned int getN() const { return m_N; }
            unsigned int getM() const { return m_M; }
            array<T> getMat() const { return m_Mat; }

            //  operator overloads
            T operator()(unsigned int i, unsigned int j) const;
            T& operator()(unsigned int i, unsigned int j);
            //  addition
            Matrix<T> operator+(const Matrix<T>& other) const;
            void operator+=(const Matrix<T>& other);
            //  substraction
            Matrix<T> operator-(const Matrix<T>& other) const;
            void operator-=(const Matrix<T>& other);
            //  multiplication
            Matrix<T> operator*(const Matrix<T>& other) const;
            void operator*=(const Matrix<T>& other);
            //  scalar multiplication
            Matrix<T> operator*(const T scalar) const;
            void operator*=(const T scalar);

            //  basic linear algebra
            void rowExchange(unsigned int i, unsigned int j);
            void rowMultiply(unsigned int i, const T value);
            void rowAdd(unsigned int i, unsigned int j, const T value);

            void columnExchange(unsigned int i, unsigned int j);
            void columnMultiply(unsigned int i, const T value);
            void columnAdd(unsigned int i, unsigned int j, const T value);

            void print();

        private:
            //  size
            unsigned int m_N;
            unsigned int m_M;
            //  array
            array<T> m_Mat;
            
    };
    template<typename T>
    Matrix<T> rowExchange(const Matrix<T>& other, unsigned int i, unsigned int j)
    {
        array<T> temp = other.getMat();
        if( i >= other.getN() || j >= other.getN())
        {
            std::cout << "ERROR! Rows (" << i << "," << j << ") exceed matrix of size (" << other.getN() << "," << other.getM() << ")!" << std::endl;
        }
        else
        {
            temp[i] = other.getMat()[j];
            temp[j] = other.getMat()[i];
        }
        return Matrix<T>(temp);
    }
    template<typename T>
    Matrix<T> rowMultiply(const Matrix<T>& other, unsigned int i, const T value)
    {
        array<T> temp = other.getMat();
        if( i >= other.getN())
        {
            std::cout << "ERROR! Row " << i << " exceed matrix of size (" << other.getN() << "," << other.getM() << ")!" << std::endl;
        }
        else
        {
            for(unsigned int j = 0; j < other.getM(); j++)
            {
                temp[i][j] *= value;
            }
        }
        return Matrix<T>(temp);
    }
    template<typename T>
    Matrix<T> rowAdd(const Matrix<T>& other, unsigned int i, unsigned int j, const T value)
    {
        array<T> temp = other.getMat();
        if( i >= other.getN() || j >= other.getN())
        {
            std::cout << "ERROR! Rows (" << i << "," << j << ") exceed matrix of size (" << other.getN() << "," << other.getM() << ")!" << std::endl;
        }
        else
        {
            for(unsigned int k = 0; k < other.getM(); k++)
            {
                temp[i][k] += value * other.getMat()[j][k];
            }
        }
        return Matrix<T>(temp);
    }
    
    template<typename T>
    Matrix<T> columnExchange(const Matrix<T>& other, unsigned int i, unsigned int j)
    {
        array<T> temp = other.getMat();
        if( i >= other.getM() || j >= other.getM())
        {
            std::cout << "ERROR! columns (" << i << "," << j << ") exceed matrix of size (" << other.getN() << "," << other.getM() << ")!" << std::endl;
        }
        else
        {
            for(unsigned int k = 0; k < other.getN(); k++)
            {
                temp[k][i] = other.getMat()[k][j];
                temp[k][j] = other.getMat()[k][i];
            }
        }
        return Matrix<T>(temp);
    }

    template<typename T>
    Matrix<T> columnMultiply(const Matrix<T>& other, unsigned int i, const T value)
    {
        array<T> temp = other.getMat();
        if(i >= other.getM())
        {
            std::cout << "ERROR! column " << i << " exceed matrix of size (" << other.getN() << "," << other.getM() << ")!" << std::endl;
        }
        else
        {
            for(unsigned int j = 0; j < other.getN(); j++)
            {
                temp[j][i] *= value;
            }
        }
        return Matrix<T>(temp);
    }

    template<typename T>
    Matrix<T> columnAdd(const Matrix<T>& other, unsigned int i, unsigned int j, const T value)
    {
        array<T> temp = other.getMat();
        if( i >= other.getM() || j >= other.getM())
        {
            std::cout << "ERROR! columns (" << i << "," << j << ") exceed matrix of size (" << other.getN() << "," << other.getM() << ")!" << std::endl;
        }
        else
        {
            for(unsigned int k = 0; k < other.getN(); k++)
            {
                temp[k][i] += value * other.getMat()[k][j];
            }
        }
        return Matrix<T>(temp);
    }


    template<typename T>
    Matrix<T>::Matrix() : m_N(0), m_M(0)
    {

    }

    template<typename T>
    Matrix<T>::~Matrix()
    {

    }

    template<typename T>
    Matrix<T>::Matrix(unsigned int n, unsigned int m) : m_N(n), m_M(m)
    {

    }

    template<typename T>
    Matrix<T>::Matrix(array<T> mat) : m_Mat(std::move(mat))
    {
        m_N = m_Mat.size();
        m_M = m_Mat[0].size();
    }

    template<typename T>
    Matrix<T>::Matrix(const std::string& filename)
    {

    }

    template<typename T>
    T Matrix<T>::operator()(unsigned int i, unsigned int j) const
    {
        if(i >= m_N || j >= m_M)
        {
            std::cout << "ERROR! Indices (" << i << "," << j 
                      << ") exceeds matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return m_Mat[0][0];
        }
        return m_Mat[i][j];
    }

    template<typename T>
    T& Matrix<T>::operator()(unsigned int i, unsigned int j)
    {
        if(i >= m_N || j >= m_M)
        {
            std::cout << "ERROR! Indices (" << i << "," << j 
                      << ") exceeds matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return m_Mat[0][0];
        }
        return m_Mat[i][j];
    }
    
    template<typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
    {
        array<T> temp;
        if((m_N != other.getN()) || (m_M != other.getM()))
        {
            std::cout << "ERROR! Matrices are not compatible!" << std::endl;
            temp = m_Mat;
        }
        else
        {
           for(unsigned int i = 0; i < m_N; i++)
           {
               std::vector<T> tempRow;
               for(unsigned int j = 0; j < m_M; j++)
               {
                   tempRow.push_back(m_Mat[i][j] + other(i,j));
               }
               temp.push_back(tempRow);
           }
        }
        return Matrix<T>(temp);
    }

    template<typename T>
    void Matrix<T>::operator+=(const Matrix<T>& other)
    {
        if((m_N != other.getN()) || (m_M != other.getM()))
        {
            std::cout << "ERROR! Matrices are not compatible!" << std::endl;
            return;
        }
        else
        {
           for(unsigned int i = 0; i < m_N; i++)
           {
               for(unsigned int j = 0; j < m_M; j++)
               {
                   m_Mat[i][j] += other(i,j);
               }
           }
        }
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
    {
        array<T> temp;
        if((m_N != other.getN()) || (m_M != other.getM()))
        {
            std::cout << "ERROR! Matrices are not compatible!" << std::endl;
            temp = m_Mat;
        }
        else
        {
           for(unsigned int i = 0; i < m_N; i++)
           {
               std::vector<T> tempRow;
               for(unsigned int j = 0; j < m_M; j++)
               {
                   tempRow.push_back(m_Mat[i][j] - other(i,j));
               }
               temp.push_back(tempRow);
           }
        }
        return Matrix<T>(temp);
    }

    template<typename T>
    void Matrix<T>::operator-=(const Matrix<T>& other)
    {
        if((m_N != other.getN()) || (m_M != other.getM()))
        {
            std::cout << "ERROR! Matrices are not compatible!" << std::endl;
            return;
        }
        else
        {
           for(unsigned int i = 0; i < m_N; i++)
           {
               for(unsigned int j = 0; j < m_M; j++)
               {
                   m_Mat[i][j] -= other(i,j);
               }
           }
        }
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
    {
        array<T> temp;
        if(m_M != other.getN())
        {
            std::cout << "ERROR! Matrices are not compatible!" << std::endl;
            temp = m_Mat;
        }
        else
        {
           for(unsigned int i = 0; i < m_N; i++)
           {
               std::vector<T> tempRow;
               for(unsigned int j = 0; j < other.getM(); j++)
               {
                   T tempVal = 0.0;
                   for(unsigned int k = 0; k < m_M; k++)
                   {
                       tempVal += m_Mat[i][k]*other(k,j);
                   }
                   tempRow.push_back(tempVal);
               }
               temp.push_back(tempRow);
           }
        }
        return Matrix<T>(temp);
    }

    template<typename T>
    void Matrix<T>::operator*=(const Matrix<T>& other)
    {
        array<T> temp;
        if(m_M != other.getN())
        {
            std::cout << "ERROR! Matrices are not compatible!" << std::endl;
            return;
        }
        else
        {
           for(unsigned int i = 0; i < m_N; i++)
           {
               std::vector<T> tempRow;
               for(unsigned int j = 0; j < other.getM(); j++)
               {
                   T tempVal = 0.0;
                   for(unsigned int k = 0; k < m_M; k++)
                   {
                       tempVal += m_Mat[i][k]*other(k,j);
                   }
                   tempRow.push_back(tempVal);
               }
               temp.push_back(tempRow);
           }
        }
        m_Mat = temp;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator*(const T scalar) const
    {
        array<T> temp;
        for(unsigned int i = 0; i < m_N; i++)
        {
            std::vector<T> tempRow;
            for(unsigned int j = 0; j < m_M; j++)
            {
                tempRow.push_back(m_Mat[i][j]*scalar);
            }
            temp.push_back(tempRow);
        }
        return Matrix<T>(temp);
    }

    template<typename T>
    void Matrix<T>::operator*=(const T scalar)
    {
        for(unsigned int i = 0; i < m_N; i++)
        {
            for(unsigned int j = 0; j < m_M; j++)
            {
                m_Mat[i][j] *= scalar;
            }
        }
    }

    template<typename T>
    void Matrix<T>::rowExchange(unsigned int i, unsigned int j)
    {
        if( i >= m_N || j >= m_N)
        {
            std::cout << "ERROR! Rows (" << i << "," << j << ") exceed matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return;
        }
        else
        {
            std::vector<T> temp = m_Mat[j];
            m_Mat[j] = m_Mat[i];
            m_Mat[i] = temp;
        }
    }

    template<typename T>
    void Matrix<T>::rowMultiply(unsigned int i, const T value)
    {
        if( i >= m_N)
        {
            std::cout << "ERROR! Row " << i << " exceed matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int j = 0; j < m_M; j++)
            {
                m_Mat[i][j] *= value;
            }
        }
    }

    

    template<typename T>
    void Matrix<T>::rowAdd(unsigned int i, unsigned int j, const T value)
    {
        if( i >= m_N || j >= m_N)
        {
            std::cout << "ERROR! Rows (" << i << "," << j << ") exceed matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int k = 0; k < m_M; k++)
            {
                m_Mat[i][k] += value * m_Mat[j][k];
            }
        }
    }

    template<typename T>
    void Matrix<T>::columnExchange(unsigned int i, unsigned int j)
    {
        if( i >= m_M || j >= m_M)
        {
            std::cout << "ERROR! columns (" << i << "," << j << ") exceed matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int k = 0; k < m_N; k++)
            {
                T temp = m_Mat[k][j];
                m_Mat[k][j] = m_Mat[k][i];
                m_Mat[k][i] = temp;
            }
        }
    }

    template<typename T>
    void Matrix<T>::columnMultiply(unsigned int i, const T value)
    {
        if( i >= m_M)
        {
            std::cout << "ERROR! column " << i << " exceed matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int j = 0; j < m_N; j++)
            {
                m_Mat[j][i] *= value;
            }
        }
    }

    template<typename T>
    void Matrix<T>::columnAdd(unsigned int i, unsigned int j, const T value)
    {
        if( i >= m_M || j >= m_M)
        {
            std::cout << "ERROR! columns (" << i << "," << j << ") exceed matrix of size (" << m_N << "," << m_M << ")!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int k = 0; k < m_N; k++)
            {
                m_Mat[k][i] += value * m_Mat[k][j];
            }
        }
    }

    template<typename T>
    void Matrix<T>::print()
    {
        std::cout << "\n[ ";
        for(unsigned int i = 0; i < m_N; i++)
        {
            for(unsigned int j = 0; j < m_M; j++)
            {
                std::cout << m_Mat[i][j] << " ";
            }
            if(i < m_N - 1) std::cout << "\n  ";
        }
        std::cout << "]\n";
    }

}