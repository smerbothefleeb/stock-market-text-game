#pragma once

class User 
{
public:
	double money= 100;
	unsigned int day = 0;
	int stocksHeld = 0;
	double totalValue = 0;

	void calculateValue();
};