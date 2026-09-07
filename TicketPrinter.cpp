#ifndef TICKETPRINTER_CPP
#define TICKETPRINTER_CPP

#include <iostream>
#include <iomanip>

using namespace std;

class Booking;

class TicketPrinter {

public:

    void printTicket(
        const Booking& booking
    ) const;
};

#endif