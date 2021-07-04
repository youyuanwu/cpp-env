#include <iostream>
#include <cstdlib>
#include <charconv> // number parsing
#include "refl.hpp"
#include "env.hpp"
struct Point
{
    std::string x;
    std::string y;
};

REFL_TYPE(Point, bases<>)
    REFL_FIELD(x, serializable()) // here we use serializable only as a maker
    REFL_FIELD(y, serializable())
REFL_END

struct MyStruct
{
    std::string PATH;
    std::string HOME;
    int Age;
};

REFL_TYPE(MyStruct, bases<>)
    REFL_FIELD(PATH, serializable())
    REFL_FIELD(HOME, serializable())
    REFL_FIELD(Age, serializable())
REFL_END

int main()
{
    // bool exists;
    // std::string env = getEnv("PATH", exists);
    // if(exists)
    //     std::cout << "Your PATH is: " << env << '\n';
    
    MyStruct ms;
    Parse(ms);

    std::cout << "Your PATH is: " << ms.PATH << '\n';
    std::cout << "Your HOME is: " << ms.HOME << '\n';
    std::cout << "Your Age is: " << ms.Age << '\n';
}