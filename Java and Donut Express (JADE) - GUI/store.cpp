#include "store.h"

Store::Store(std::string name) : _name{name} {}
Store::Store() {}

Store::Store(std::istream& ist) {
	getline(ist, _name);
	int products;
    ist >> products; ist.ignore();
	std::string pname;
    while(products-- > 0) {
		getline(ist, pname);
		if(pname == "donut")
			_products.push_back(new Donut{ist});
		else
			_products.push_back(new Java{ist});
	}
    int customers;
    ist >> customers; ist.ignore();
    while(customers-- > 0) _customers.push_back(new Customer{ist});
	
}

std::string Store::name() const {return _name;}

void Store::add_product(Product* product) {_products.push_back(product);}

Product* Store::get_product(int p) { 
	return _products[p]; }

int Store::number_of_products() const {return _products.size();}

std::string Store::product_to_string(int product) const {
	std::ostringstream oss;
	oss	<< _products[product];
	return oss.str();
}

void Store::add_customer(Customer* customer) {_customers.push_back(customer);}

int Store::number_of_customers() const {return _customers.size();}

std::string Store::customer_to_string(int customer) const {
	std::ostringstream oss;
	int i = 1;
	for(auto c : _customers) {oss << "(" << i << ") " << c->to_string() << std::endl; i++;}
	return oss.str();
	
}

void Store::add_order(Order* order, int customer) {_orders[customer] = order; }

int Store::number_of_orders() const {return _orders.size();}

std::string Store::order_to_string(int customer) const {
	std::ostringstream oss;
	oss << "Order for: " << _customers[customer]->to_string() << std::endl;
	Order* order =  _orders.at(customer);
	oss << order->to_string() << std::endl;
	return oss.str();
}


void Store::save (std::ostream& ost) {
	ost << _name << std::endl;
	ost << _products.size() << '\n';
    for (auto& p : _products) p->save(ost);
    ost << _customers.size() << '\n';
    for (auto& c : _customers) c->save(ost);
}

std::ostream& operator<<(std::ostream& ost, const Store& store) {
	ost << "Store " << store.name() << std::endl << std::endl;
	ost << "Products:" << std::endl;
	int i = 0;
    for (auto p : store._products) {
		ost << "  (" << i+1 << ") " << p->to_string() << std::endl;
		i++;
	}
    return ost;
}