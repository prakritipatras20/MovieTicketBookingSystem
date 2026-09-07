#ifndef CASHPAYMENT_CPP
#define CASHPAYMENT_CPP

#include <iostream>

#include "Payment.cpp"

using namespace std;

class CashPayment : public Payment {

public:

    bool pay(double amount) override {

        cout << "\nCollecting cash of Rs."
             << amount
             << "...\n";

        cout << "Cash received. Payment successful.\n";

        return true;
    }

    string getMethodName() const override {
        return "CASH";
    }
};

#endif