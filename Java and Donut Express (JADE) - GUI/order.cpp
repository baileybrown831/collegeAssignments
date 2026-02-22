#include "order.h"

Order::Order() {}

void Order::add_product(Product* product, int quantity) { 
	_products.push_back(product); 
	_quantity.push_back(quantity);
	}

bool Order::is_paid() {
	if(_is_paid) return true;
	else return false;
}

void Order::pay() { _is_paid = true; }

bool Order::is_filled() {
	if(_is_filled) return true;
	else return false;
}

void Order::fill() { _is_filled = true; }

std::string Order::to_string() {
	std::ostringstream oss;
	int i = 0;
	for(auto p : _products) {oss << "  " << p->to_string() << " x " << _quantity[i] << std::endl; i++;}
	return oss.str();
}