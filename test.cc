#include <iostream>
#include "geometry.h"

int main() {
    Vector v = Vector(4, 5);
    std::cout << v.x() << std::endl;
    std::cout << v.y() << std::endl;
}
