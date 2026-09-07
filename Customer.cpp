#ifndef CUSTOMER_CPP
#define CUSTOMER_CPP

#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    Customer(string name, string phone);

    string getName() const;
    string getPhone() const;
};

#endif