#include "Customer.h"

Customer::Customer(const std::string &name, char sex, const std::string &address, int uniqueID)
    : name(name), sex(sex), address(address), uniqueID(uniqueID) {}

std::string Customer::getName() const
{
    return name;
}

char Customer::getSex() const
{
    return sex;
}

std::string Customer::getAddress() const
{
    return address;
}

int Customer::getUniqueID() const
{
    return uniqueID;
}

std::vector<double> Customer::getSales() const
{
    return sales;
}

void Customer::addSale(double amount)
{
    sales.push_back(amount);
}

double Customer::getTotalSales() const
{
    double total = 0.0;
    for (const auto &sale : sales)
    {
        total += sale;
    }
    return total;
}

double Customer::getAverageSales() const
{
    if (sales.empty())
    {
        return 0.0;
    }
    return getTotalSales() / sales.size();
}