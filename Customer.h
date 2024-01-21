#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

class Customer
{
private:
    std::string name;
    char sex;
    std::string address;
    int uniqueID;
    std::vector<double> sales;

public:
    Customer(const std::string &name, char sex, const std::string &address, int uniqueID);

    std::string getName() const;
    char getSex() const;
    std::string getAddress() const;
    int getUniqueID() const;
    std::vector<double> getSales() const;

    void addSale(double amount);
    double getTotalSales() const;
    double getAverageSales() const;
};

#endif // CUSTOMER_H