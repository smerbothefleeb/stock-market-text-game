#pragma once

class User {
public:
	double money;
	int stocksHeld;
	double totalValue;

	double calculateValue();
	User(double _money) {
		money = _money;
	}
};