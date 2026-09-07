#ifndef SHOWSEAT_CPP
#define SHOWSEAT_CPP

class Seat;

enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    ShowSeat(Seat* seat);

    bool isAvailable() const;
    bool isBooked() const;

    bool bookSeat();
    void releaseSeat();

    Seat* getSeat() const;
};

#endif