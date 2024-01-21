#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>
#include "Customer.h"

// Function Prototypes
void registerCustomer(std::vector<Customer> &customers);
void recordPurchase(std::vector<Customer> &customers);
void generateReport(const std::vector<Customer> &customers);
void searchCustomerByID(const std::vector<Customer> &customers);
void searchCustomerByName(const std::vector<Customer> &customers);

int main()
{
    std::vector<Customer> customers;

    int choice;
    while (true)
    {
        // Display menu options
        std::cout << "==== Customer Tracker ====" << std::endl;
        std::cout << "1. Register a customer" << std::endl;
        std::cout << "2. Record a purchase" << std::endl;
        std::cout << "3. Generate end-of-day report" << std::endl;
        std::cout << "4. Search for a customer by ID" << std::endl;
        std::cout << "5. Search for a customer by name" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Perform action based on user's choice
        switch (choice)
        {
        case 1:
            registerCustomer(customers);
            break;
        case 2:
            recordPurchase(customers);
            break;
        case 3:
            generateReport(customers);
            break;
        case 4:
            searchCustomerByID(customers);
            break;
        case 5:
            searchCustomerByName(customers);
            break;
        case 6:
            std::cout << "Thanks for using the program. Bye bye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl;
    }

    return 0;
}

void registerCustomer(std::vector<Customer> &customers)
{
    // Prompt the user to enter customer details.
    std::string name;
    char sex;
    std::string address;

    std::cout << "Enter customer name: ";
    std::cin >> name;
    std::cin.ignore();

    std::cout << "Enter customer sex (m / f): ";
    std::cin >> sex;
    std::cin.ignore(); // Clear input buffer

    std::cout << "Enter customer address: ";
    std::getline(std::cin, address);

    int uniqueID = customers.size() + 1;

    Customer customer(name, sex, address, uniqueID);
    customers.push_back(customer);

    std::cout << "Customer registered successfully with ID: " << uniqueID << std::endl
              << "Press enter to continue" << std::endl;
}

void recordPurchase(std::vector<Customer> &customers)
{
    // Prompt the user to enter customer ID
    int customerID;
    std::cout << "Enter customer ID: ";
    std::cin >> customerID;

    // Find the customer in the vector based on ID
    bool customerFound = false;
    for (auto &customer : customers)
    {
        if (customer.getUniqueID() == customerID)
        {
            customerFound = true;

            // Prompt the user to enter the purchase amount
            double purchaseAmount;
            std::cout << "Enter purchase amount: ";
            std::cin >> purchaseAmount;

            // Record the purchase
            customer.addSale(purchaseAmount);
            std::cout << "Purchase of amount " << purchaseAmount << "recorded successfully for customer ID: " << customerID << std::endl;
            break;
        }
    }

    if (!customerFound)
    {
        std::cout << "Customer not found with ID: " << customerID << std::endl;
    }
}

void generateReport(const std::vector<Customer>& customers)
{
    std::cout << "==== End-of-Day Report ====" << std::endl;

    // Prompt the user for report type
    std::cout << "Enter 's' for Summary report or 'd' for Detailed report: ";
    std::string reportType;
    std::cin >> reportType;

    if (reportType == "d" || reportType == "D")
    {
        // Detailed report with tabular format
        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << "|    Name    |    Sex    |         Address        |  Sales  | Total Sales | Average Sales |" << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
        for (const auto& customer : customers)
        {
            std::stringstream salesStream;
            for (const auto& sale : customer.getSales())
            {
                salesStream << sale << ", ";
            }
            std::string salesStr = salesStream.str();
            if (!salesStr.empty())
                salesStr = salesStr.substr(0, salesStr.length() - 2);

            std::cout << "|" << std::setw(12) << customer.getName() << " |"
                      << std::setw(9) << customer.getSex() << " |"
                      << std::setw(23) << customer.getAddress() << " |"
                      << std::setw(9) << salesStr << " |"
                      << std::setw(12) << customer.getTotalSales() << " |"
                      << std::setw(14) << customer.getAverageSales() << " |" << std::endl;
        }
        std::cout << "---------------------------------------------------------------" << std::endl;
    }
    else if (reportType == "s" || reportType == "S")
    {
        // Summary report
        int totalCustomers = customers.size();
        double totalSales = 0.0;
        int totalItemsSold = 0;

        for (const auto& customer : customers)
        {
            totalSales += customer.getTotalSales();
            totalItemsSold += customer.getSales().size();
        }

        std::cout << "Total Customers: " << totalCustomers << std::endl;
        std::cout << "Total Sales: " << totalSales << std::endl;
        std::cout << "Total Items Sold: " << totalItemsSold << std::endl;
    }
    else
    {
        std::cout << "Invalid report type. Please enter 's' for Summary or 'd' for Detailed." << std::endl;
    }
}

void searchCustomerByID(const std::vector<Customer> &customers)
{
    // Prompt the user to enter customer ID
    int customerID;
    std::cout << "Enter customer ID: ";
    std::cin >> customerID;

    // Find the customer in the vector based on ID
    bool customerFound = false;
    for (const auto &customer : customers)
    {
        if (customer.getUniqueID() == customerID)
        {
            customerFound = true;
            std::cout << "Customer found with ID: " << customerID << std::endl;
            std::cout << "Name: " << customer.getName() << std::endl;
            std::cout << "Sex: " << customer.getSex() << std::endl;
            std::cout << "Address: " << customer.getAddress() << std::endl;
            std::cout << "Total Sales: " << customer.getTotalSales() << std::endl;
            std::cout << "Average Sales: " << customer.getAverageSales() << std::endl;
            break;
        }
    }

    if (!customerFound)
    {
        std::cout << "Customer not found with ID: " << customerID << std::endl;
    }
}

void searchCustomerByName(const std::vector<Customer> &customers)
{
    // Prompt the user to enter the customer name
    std::string customerName;
    std::cout << "Enter customer name: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, customerName);

    // Find customers in the vector with matching names
    bool customerFound = false;
    for (const auto &customer : customers)
    {
        if (customer.getName() == customerName)
        {
            customerFound = true;
            std::cout << "Customer found with name: " << customerName << std::endl;
            std::cout << "Name: " << customer.getName() << std::endl;
            std::cout << "Sex: " << customer.getSex() << std::endl;
            std::cout << "Address: " << customer.getAddress() << std::endl;
            std::cout << "Total Sales: " << customer.getTotalSales() << std::endl;
            std::cout << "Average Sales: " << customer.getAverageSales() << std::endl;
            break;
        }
    }

    if (!customerFound)
    {
        std::cout << "No customers found with name: " << customerName << std::endl;
    }
}