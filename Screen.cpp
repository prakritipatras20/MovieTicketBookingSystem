#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <vector>
using namespace std;

class Seat;

class Screen {
private:
    int screenNumber;
    vector<Seat*> seats;

public:
    Screen(int screenNumber);

    void addSeat(Seat* seat);

    vector<Seat*> getSeats() const;

    int getScreenNumber() const;
};

#endif