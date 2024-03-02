#include <iostream>
#include "eigen-3.4.0/Eigen/Eigen"

using std::cout;
using std::endl;

int main()
{
    Eigen::Matrix<int, 2, 3> ma{};
    Eigen::MatrixXd mb(3,4);
    Eigen::MatrixXd mc(2,2);
    ma <<   -2,  4,  3,
            1, -2,  4;

    mb <<   2,  4,  6,  8,
            2,  4,  6,  8,
            -3, -6, -9, -12;

    mc <<   1, -2,
            3, 4;

    Eigen::VectorXd va(3);
    va << 1,2,3;
 
    cout << ma << endl;
    cout << "------" << endl;
    cout << mb.transpose() << endl;
    cout << "------" << endl;
    cout << mc.inverse() << endl;
    cout << "------" << endl;
    cout << mc.conjugate() << endl;

    return 0;
}   

