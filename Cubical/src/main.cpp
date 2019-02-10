#include "Matrix.h"
#include "Vector.h"

using namespace Cubical;

int main()
{
   
    Matrix<double> m(array<double>({{1,2,0},{0,1,0},{0,0,1}}));
    m.print();

    Matrix<double> m2 = columnMultiply(m, 0,-1.0);
    m.print();
    m2.print();

    return 0;
}