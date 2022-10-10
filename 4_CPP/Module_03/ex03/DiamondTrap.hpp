
#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : virtual public ScavTrap, virtual public FragTrap{
private:
    std::string _name;
public:
    DiamondTrap();
    DiamondTrap(std::string name);
    DiamondTrap(DiamondTrap const &old);
    ~DiamondTrap();

    DiamondTrap &operator=(DiamondTrap const &old);
    virtual void attack(const std::string &target);
    void whoAmI();
};


#endif
