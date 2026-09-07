#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration;

public:
    Movie(string title, string language, int duration);

    string getTitle() const;
    string getLanguage() const;
    int getDuration() const;
};

#endif