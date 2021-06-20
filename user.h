#pragma once

class User {
public:
	double money= 100;
	int stocksHeld = 0;
	double totalValue = 0;

	void calculateValue();
	User(double _money) {
		money = _money;
	}
};