#pragma once
extern const std::string defaultCompany;
extern const std::string defaultUser;
class Company 
{
public:
	std::string companyName;
	int companyNumber;
	double companyStockValue;
	int numberOfStocks;
	float incomePerStock;
	int maximumStocks;
	

	bool belowZero();
	void changeQuantity(int amount, double& userMoney);

	Company(int _companyNumber, std::string _companyName, double _stockValue,
		int numStocks, int maxStocks) 
	{
			companyNumber = _companyNumber;
			companyName = _companyName;
			companyStockValue = _stockValue;
			numberOfStocks = numStocks;
			maximumStocks = maxStocks;
	}
};


