#ifndef BOOKING_CPP
#define BOOKING_CPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Customer.cpp"
#include "Show.cpp"
#include "ShowSeat.cpp"
#include "Payment.cpp"

enum class BookingStatus {
    PENDING,
    CONFIRMED,
    FAILED,
    CANCELLED
};

class Booking {

private:

    static int nextBookingId;

    int bookingId;

    Customer customer;

    Show* show;

    vector<ShowSeat*> seats;

    Payment* payment;

    double totalAmount;

    BookingStatus status;

public:

    Booking(
        Customer customer,
        Show* show,
        vector<ShowSeat*> seats,
        Payment* payment,
        double totalAmount
    );

    void confirmBooking();

    void failBooking();

    void cancelBooking();

    int getBookingId() const;

    Customer getCustomer() const;

    Show* getShow() const;

    vector<ShowSeat*> getSeats() const;

    Payment* getPayment() const;

    double getTotalAmount() const;

    BookingStatus getStatus() const;

    string getStatusString() const;
};

#endif