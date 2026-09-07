#ifndef BOOKINGSERVICE_CPP
#define BOOKINGSERVICE_CPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Show;
class ShowSeat;
class Booking;
class Customer;
class Payment;
class PriceCalculator;
class TicketPrinter;

class BookingService {

private:

    PriceCalculator* priceCalculator;
    TicketPrinter* ticketPrinter;

public:

    BookingService(
        PriceCalculator* priceCalculator,
        TicketPrinter* ticketPrinter
    );

    Booking* bookTicket(
    Customer customer,
    Show* show,
    const vector<string>& seatNumbers,
    Payment& payment
    );

    bool cancelBooking(Booking* booking);

    bool selectSeats(
        Show* show,
        const vector<string>& seatNumbers,
        vector<ShowSeat*>& selectedSeats
    ) const;

    bool processPayment(
        Booking* booking,
        Payment& payment
    ) const;
};

#endif