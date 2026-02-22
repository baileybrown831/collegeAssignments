#ifndef __DONUT_H
#define __DONUT_H

#include <sstream>
#include <iostream>
#include <vector>
#include "product.h"

enum Frosting {Unfrosted, Chocolate_top, Vanilla_top, Pink_top};
const std::vector<std::string> frosting_to_string = {"Unfrosted", "Chocolate", "Vanilla", "Pink"};

enum Filling {Unfilled, Creme, Bavarian, Strawberry};
const std::vector<std::string> filling_to_string = {"Unfilled", "Creme", "Bavarian", "Strawberry"};

class Donut: public Product {
  public:
	Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling);
	Donut(std::istream& ist);
	void save(std::ostream& ost);
 
  protected:
	std::string to_string() override;
	Frosting _frosting;
	bool _sprinkles;
	Filling _filling;
};

#endif