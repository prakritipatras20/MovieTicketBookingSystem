#ifndef SEAT_CPP
#define SEAT_CPP

#include <string>
using namespace std;

enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

class Seat {
private:
    string seatNumber;
    SeatType seatType;

public:
    Seat(string seatNumber, SeatType seatType);

    string getSeatNumber() const;
    SeatType getSeatType() const;
};

#endif