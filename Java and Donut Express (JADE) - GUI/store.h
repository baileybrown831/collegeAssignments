#ifndef __STORE_H
#define __STORE_H

#include "product.h"
#include "customer.h"
#include "java.h"
#include "donut.h"
#include "order.h"
#include <vector>
#include <map>

class Store {
  public:
    Store(std::string name);
	Store();
	Store(std::istream& ist);
	std::string name() const;
	void add_product(Product* product);
	Product* get_product(int p);
	int number_of_products() const;
	std::string product_to_string(int product) const;
	void add_customer(Customer* customer);
	int number_of_customers() const;
	std::string customer_to_string(int customer) const;
	void add_order(Order* order, int customer);
	int number_of_orders () const;
	std::string order_to_string(int customer) const;
	void save(std::ostream& ost);
	friend std::ostream& operator<<(std::ostream& ost, const Store& store);
	
  private:
	std::string _name;
	std::vector<Product*> _products;
	std::vector<Customer*> _customers;
	std::map<int, Order*> _orders;
};
#endif