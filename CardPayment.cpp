#ifndef CARDPAYMENT_CPP
#define CARDPAYMENT_CPP

#include <iostream>
#include <cstdlib>
#include <string>

#include "Payment.cpp"

using namespace std;

class CardPayment : public Payment {

private:
    string cardNumber;

public:

    CardPayment(string cardNumber) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) override {

        cout << "\nCharging Rs. "
             << amount
             << " to card "
             << cardNumber
             << "...\n";

        // Approximately 20% failure
        if (rand() % 5 == 0) {

            cout << "Card payment declined.\n";
            return false;
        }

        cout << "Card payment approved.\n";
        return true;
    }

    string getMethodName() const override {
        return "CARD";
    }
};

#endif