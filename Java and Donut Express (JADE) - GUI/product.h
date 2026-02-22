#ifndef __PRODUCT_H
#define __PRODUCT_H

#include <sstream>
#include <iomanip>

class Product {
  public:
    Product(std::string name, double price, double cost);
	Product();
	Product(std::istream& ist);
	std::string name() const;
	virtual void save(std::ostream& ost);
	virtual std::string to_string();
  protected:
	std::string _name;
	double _price;
	double _cost;
};

#endif