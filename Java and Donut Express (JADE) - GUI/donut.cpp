#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling)
             :Product{name, price, cost}, _frosting{frosting}, _sprinkles{sprinkles}, _filling{filling} {}

Donut::Donut(std::istream& ist) : Product{ist} {
	int frosting;
    ist >> frosting; ist.ignore();
	_frosting = static_cast<Frosting>(frosting);
	int sprinkles;
	ist >> sprinkles; ist.ignore();
	_sprinkles = sprinkles;
	int filling;
	ist >> filling; ist.ignore();
	_filling = static_cast<Filling>(filling);
}
void Donut::save(std::ostream& ost) {
	ost << "donut" << std::endl;
	Product::save(ost);
    ost << _frosting << std::endl;
    ost << _sprinkles << std::endl;
	ost << _filling << std::endl;
}
			 
std::string Donut::to_string() {
	std::string result = Product::to_string();
	std::string seperator = " (";
	std::string terminator = "";
	
	if(_frosting != Unfrosted) {
		result += seperator + frosting_to_string[_frosting] + " Frosting";
		if(_sprinkles) result += " with sprinkles";
		seperator = ", ";
		terminator = ")";
	}
	
	if(_filling != Unfilled) {
		result += seperator + filling_to_string[_filling] + " Filling";
		terminator = ")";
	}
	
	result += terminator;
	return result;
}


