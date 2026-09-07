#ifndef SHOW_CPP
#define SHOW_CPP

#include <string>
#include <vector>
using namespace std;

class Movie;
class Screen;
class ShowSeat;

class Show {
private:
    static int nextShowId;

    int showId;

    Movie* movie;
    Screen* screen;

    string startTime;

    vector<ShowSeat*> showSeats;

public:

    Show(Movie* movie, Screen* screen, string startTime);

    ~Show();

    int getShowId() const;

    void addShowSeat(ShowSeat* showSeat);

    void displaySeats() const;

    ShowSeat* findShowSeat(const string& seatNumber) const;

    Movie* getMovie() const;

    Screen* getScreen() const;

    string getStartTime() const;

    vector<ShowSeat*> getShowSeats() const;
};

#endif