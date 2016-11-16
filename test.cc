#include <iostream>
#include <vector>
#include "geometry.h"
using namespace std;

vector<int> fun() {
    return vector<int>(2);
};

int abc() {
    return 3;
}

int main() {
    Vector v = Vector(4, 5);
    std::cout << v.x() << std::endl;
    std::cout << v.y() << std::endl;
    Vector a(3, 4), b(6, 7), c(0,0);
//    (a + b) = v;
    a = v;
    v = a + b;
//    int x, y, z;
//    int i = 10;
//    x = (y + z) = i;

    vector<int> t = fun();
    fun() = t;
    int x = 2;
//    abc() = x;
   
    std::cout << a.x() << " " << a.y() << std::endl;
    std::cout << b.x() << " " << b.y() << std::endl;
    std::cout << c.x() << " " << c.y() << std::endl;
//    std::cout << x <<" " << y << " " << z << std::endl;
}
