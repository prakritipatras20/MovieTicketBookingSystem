#include <cstdlib>
#include <ctime>
#include "MainMenu.cpp"

int main() {
    srand((unsigned)time(0));

    MainMenu menu;
    menu.run();

    return 0;
}