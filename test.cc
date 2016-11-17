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
    a = a;
	Position p(3, 4);
	p = p;
	Rectangle r(3, 4, p);
	r = r;
   
    std::cout << a.x() << " " << a.y() << std::endl;
    std::cout << p.x() << " " << p.y() << std::endl;
    std::cout << r.width() << " " << r.height() <<" "<< r.pos().x() <<" "<<r.pos().y() << std::endl;
//    std::cout << x <<" " << y << " " << z << std::endl;
}
