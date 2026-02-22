#include "java.h"

Java::Java(std::string name, double price, double cost, Roast darkness) : Product{name, price, cost}, _roast{darkness} {}

Java::Java(std::istream& ist) : Product{ist} {
	int roast;
	ist >> roast; ist.ignore();
	_roast = static_cast<Roast>(roast);
	int shots;
	int shotType;
    ist >> shots; ist.ignore();
    while(shots-- > 0) {
		ist >> shotType; ist.ignore();
		_shots.push_back(static_cast<Shot>(shotType));
	}
}

void Java::save(std::ostream& ost) {
	ost << "java" << std::endl;
	Product::save(ost);
	ost << _roast << std::endl;
	ost << _shots.size() << '\n';
    for (auto& s : _shots) ost << s << std::endl;
}
	

std::string Java::to_string() {
	
	std::string result = Product::to_string() + " (" + darkness_to_string[_roast] + ")";
	
	if(!_shots.empty()) {
		std::string seperator = "";
		result += " Add: ";
		for(auto s : _shots) { result += (seperator + shot_to_string[s]); seperator = ", ";}
	}
	
	return result;	
}

void Java::add_shot(Shot shot) { _shots.push_back(shot); }
	
