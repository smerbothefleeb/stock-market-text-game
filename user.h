#pragma once

class User {
public:
	double money;
	int stocksHeld;
	double totalValue;

	void calculateValue();
	User(double _money) {
		money = _money;
	}
};