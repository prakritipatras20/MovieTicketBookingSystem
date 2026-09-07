#ifndef PRICECALCULATOR_CPP
#define PRICECALCULATOR_CPP

#include <vector>
using namespace std;

class ShowSeat;
enum class SeatType;

class PriceCalculator {

public:

    double getSeatPrice(SeatType type) const;

    double calculateTotal(
        const vector<ShowSeat*>& seats
    ) const;
};

#endif