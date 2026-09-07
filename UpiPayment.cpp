#ifndef UPIPAYMENT_CPP
#define UPIPAYMENT_CPP

#include <iostream>
#include <cstdlib>
#include <string>

#include "Payment.cpp"

using namespace std;

class UpiPayment : public Payment {

private:
    string upiId;

public:

    UpiPayment(string upiId) {
        this->upiId = upiId;
    }

    bool pay(double amount) override {

        cout << "\nSending Rs. "
             << amount
             << " via UPI ("
             << upiId
             << ")...\n";

        // Approximately 20% failure
        if (rand() % 5 == 0) {

            cout << "UPI payment declined by bank.\n";
            return false;
        }

        cout << "UPI payment successful.\n";
        return true;
    }

    string getMethodName() const override {
        return "UPI";
    }
};

#endif