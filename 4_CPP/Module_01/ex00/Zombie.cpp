
#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name): _name(name) {
    std::cout << _name << " started to exist" << std::endl;
}

Zombie::~Zombie() {
    std::cout << _name << " is dead (finally)" << std::endl;
}

void Zombie::announce() {
    std::cout << _name << " BraiiiiiiinnnzzzZ..." << std::endl;
}