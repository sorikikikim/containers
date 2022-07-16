#include <iostream>
#include "vector.hpp"
#include <vector>

class Custom{
    public:
        Custom(){
            std::cout<< "default constructor"<<std::endl;
            throw std::length_error("default");
        }

        Custom(Custom& custom){
            std::cout<< "default constructor"<<std::endl;
            throw std::length_error("copy");
        }
};

int main(){
    ft::vector<Custom>
}