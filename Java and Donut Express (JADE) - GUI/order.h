#ifndef __ORDER_H
#define __ORDER_H

#include <vector>
#include "product.h"

class Order {
  public:
	Order();
	void add_product(Product* product, int quantity);
	bool is_paid();
	void pay();
	bool is_filled();
	void fill();
	std::string to_string();
	
  protected:
	std::vector<Product*> _products;
	std::vector<int> _quantity;
	
  private:
	int _next_order_number;
	int _order_number;
	bool _is_paid;
	bool _is_filled;
};
#endif
	