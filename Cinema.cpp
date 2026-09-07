#ifndef CINEMA_CPP
#define CINEMA_CPP

#include <vector>
#include <string>

using namespace std;

class Screen;
class Movie;

class Cinema {

private:

    string name;

    vector<Screen*> screens;

public:

    Cinema(string name);

    void addScreen(Screen* screen);

    vector<Screen*> getScreens() const;

    void listMovies(
        const vector<Movie*>& movies
    ) const;
};

#endif