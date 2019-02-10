#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace Cubical
{
    template<typename T>
    class Vector
    {
        public:
            Vector<T>();
            virtual ~Vector<T>();
            Vector<T>(std::vector<T> vec);

            //  getters and setters
            unsigned int getDim() const { return m_Dim; }

            //  operator overloads
            T operator()(unsigned int i) const;
            T& operator()(unsigned int i);
            //  addition
            Vector<T> operator+(const Vector<T>& other) const;
            void operator+=(const Vector<T>& other);
            //  subtraction
            Vector<T> operator-(const Vector<T>& other) const;
            void operator-=(const Vector<T>& other);
            //  scalar multiplication
            Vector<T> operator*(const T scalar) const;
            void operator*=(const T scalar);
            //  is equal
            bool operator==(const Vector<T>& other) const;
            //  dot product
            T operator*(const Vector<T>& other) const;
            //  norm
            void findNorm();
            void normalize();
            T const getNorm();
            //  cross product 
            Vector<T> cross(const Vector<T>& other) const;
            //  projection
            Vector<T> projection(const Vector<T>& other) const;

            void print();

        private:
            //  size
            unsigned int m_Dim;
            //  vector
            std::vector<T> m_Vec;
            //  norm
            T m_Norm;
    };

    template<typename T>
    Vector<T>::Vector() : m_Dim(0)
    {

    }

    template<typename T>
    Vector<T>::~Vector()
    {

    }

    template<typename T>
    Vector<T>::Vector(std::vector<T> vec) : m_Vec(std::move(vec))
    {
        m_Dim = m_Vec.size();
    }

    template<typename T>
    T Vector<T>::operator()(unsigned int i) const
    {
        if(i >= m_Dim)
        {
            std::cout << "ERROR! Index " << i << " exceed vector of size " << m_Dim << std::endl;
            return 0;
        }
        else
        {
            return m_Vec[i];
        }  
    }

    template<typename T>
    T& Vector<T>::operator()(unsigned int i)
    {
        if(i >= m_Dim)
        {
            std::cout << "ERROR! Index " << i << " exceed vector of size " << m_Dim << std::endl;
            return 0;
        }
        else
        {
            return m_Vec[i];
        }  
    }

    template<typename T>
    Vector<T> Vector<T>::operator+(const Vector<T>& other) const
    {
        std::vector<T> temp;
        if(m_Dim != other.getDim())
        {
            std::cout << "ERROR! Vectors are not compatible!" << std::endl;
            temp = m_Vec;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                temp.push_back(m_Vec[i] + other(i));
            }
        }
        return Vector<T>(temp);
    }

    template<typename T>
    void Vector<T>::operator+=(const Vector<T>& other)
    {
        if(m_Dim != other.getDim())
        {
            std::cout << "ERROR! Vectors are not compatible!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                m_Vec[i] += other(i);
            }
        }
    }

    template<typename T>
    Vector<T> Vector<T>::operator-(const Vector<T>& other) const
    {
        std::vector<T> temp;
        if(m_Dim != other.getDim())
        {
            std::cout << "ERROR! Vectors are not compatible!" << std::endl;
            temp = m_Vec;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                temp.push_back(m_Vec[i] - other(i));
            }
        }
        return Vector<T>(temp);
    }

    template<typename T>
    void Vector<T>::operator-=(const Vector<T>& other)
    {
        if(m_Dim != other.getDim())
        {
            std::cout << "ERROR! Vectors are not compatible!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                m_Vec[i] -= other(i);
            }
        }
    }

    template<typename T>
    Vector<T> Vector<T>::operator*(const T scalar) const
    {
        std::vector<T> temp;
        for(unsigned int i = 0; i < m_Dim; i++)
        {
            temp.push_back(m_Vec[i] * scalar);
        }
        return Vector<T>(temp);
    }

    template<typename T>
    void Vector<T>::operator*=(const T scalar)
    {
        for(unsigned int i = 0; i < m_Dim; i++)
        {
            m_Vec[i] *= scalar;
        }
    }

    template<typename T>
    bool Vector<T>::operator==(const Vector<T>& other) const
    {
        if(m_Dim != other.getDim())
        {
            return false;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                if(m_Vec[i] != other(i))
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T>
    T Vector<T>::operator*(const Vector<T>& other) const
    {
        T dot;
        if(m_Dim != other.getDim())
        {
            std::cout << "ERROR! Vectors are not compatible!" << std::endl;
            return 0;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                dot += m_Vec[i] * other(i);
            }
        }
        return dot;
    }

    template<typename T>
    void Vector<T>::findNorm()
    {
        T norm;
        for(unsigned int i = 0; i < m_Dim; i++)
        {
            norm += m_Vec[i] * m_Vec[i];
        }
        m_Norm = sqrt(norm);
    }

    template<typename T>
    void Vector<T>::normalize()
    {
        if(!m_Norm)
        {
            findNorm();
        }
        if(m_Norm == 0)
        {
            std::cout << "ERROR! Vector is the zero vector!" << std::endl;
            return;
        }
        else
        {
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                m_Vec[i] /= m_Norm;
            }
        }
    }

    template<typename T>
    T const Vector<T>::getNorm()
    {
        if(!m_Norm)
        {
            findNorm();
        }
        return m_Norm;
    }

    template<typename T>
    Vector<T> Vector<T>::cross(const Vector<T>& other) const
    {
        std::vector<T> temp;
        if(m_Dim != 3 || other.getDim() != 3)
        {
            std::cout << "ERROR! Cross product not defined for vectors of dimension " << m_Dim << " and " << other.getDim() << std::endl;
            temp = m_Vec;
        }
        else
        {
            temp.push_back(m_Vec[1] * other(2) - m_Vec[2] * other(1));
            temp.push_back(m_Vec[2] * other(0) - m_Vec[0] * other(2));
            temp.push_back(m_Vec[0] * other(1) - m_Vec[1] * other(0));
        }
        return Vector<T>(temp);
    }

    template<typename T>
    Vector<T> Vector<T>::projection(const Vector<T>& other) const
    {
        std::vector<T> temp;
        temp = m_Vec;
        if(m_Dim != other.getDim())
        {
            std::cout << "ERROR! Vectors are not compatible!" << std::endl;
        }
        else
        {
            T dot = (*this) * other;
            T norm_s = (*this) * (*this);
            dot /= norm_s;
            for(unsigned int i = 0; i < m_Dim; i++)
            {
                temp[i] *= dot;
            }
        }
        return Vector<T>(temp);
    }

    template<typename T>
    void Vector<T>::print()
    {
        std::cout << "\n[ ";
        for(unsigned int i = 0; i < m_Dim; i++)
        {
            std::cout << m_Vec[i] << " ";
        }
        std::cout << "]\n";
    }

}