#ifndef __JAVA_H
#define __JAVA_H

#include "product.h"
#include <sstream>
#include <iostream>
#include <vector>

enum Roast {Blonde, Light, Medium, Dark, Very_Dark};
const std::vector<std::string> darkness_to_string = {"Blonde", "Light", "Medium", "Dark", "Extra Dark"};

enum Shot {None, Chocolate, Vanilla, Peppermint, Hazelnut};
const std::vector<std::string> shot_to_string = {"None", "Chocolate", "Vanilla", "Peppermint", "Hazelnut"};

class Java: public Product {
  public:
	Java(std::string name, double price, double cost, Roast darkness);
	Java(std::istream& ist);
	void add_shot(Shot shot);
	void save(std::ostream& ost);
	
  protected:
	std::string to_string() override;
	Roast _roast;
	std::vector<Shot> _shots;
};
#endif