#ifndef MAINMENU_CPP
#define MAINMENU_CPP

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "Implementation.cpp"

using namespace std;

class MainMenu {
private:
    Cinema cinema;

    vector<Movie*> movies;
    vector<Show*> shows;
    vector<Booking*> bookings;

    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    BookingService bookingService;

    

private:

    int readIntChoice() {
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return -1;
        }

        return choice;
    }

    void setupData() {

        cinema = Cinema("PVR Cinema");

        // --------------------------------
        // SCREEN
        // --------------------------------

        Screen* screen1 = new Screen(1);

        screen1->addSeat(new Seat("A1", SeatType::PLATINUM));
        screen1->addSeat(new Seat("A2", SeatType::PLATINUM));

        screen1->addSeat(new Seat("B1", SeatType::GOLD));
        screen1->addSeat(new Seat("B2", SeatType::GOLD));

        screen1->addSeat(new Seat("C1", SeatType::SILVER));
        screen1->addSeat(new Seat("C2", SeatType::SILVER));

        cinema.addScreen(screen1);

        // --------------------------------
        // MOVIES
        // --------------------------------

        movies.push_back(
            new Movie("Avengers: Endgame", "English", 181)
        );

        movies.push_back(
            new Movie("Inception", "English", 148)
        );

        movies.push_back(
            new Movie("Interstellar", "English", 169)
        );

        movies.push_back(
            new Movie("Dangal", "Hindi", 161)
        );

        movies.push_back(
            new Movie("3 Idiots", "Hindi", 170)
        );

        // --------------------------------
        // SHOWS
        // --------------------------------

        shows.push_back(
            new Show(movies[0], screen1, "10:00 AM")
        );

        shows.push_back(
            new Show(movies[0], screen1, "7:00 PM")
        );

        shows.push_back(
            new Show(movies[1], screen1, "1:00 PM")
        );

        shows.push_back(
            new Show(movies[1], screen1, "9:30 PM")
        );

        shows.push_back(
            new Show(movies[2], screen1, "4:00 PM")
        );

        shows.push_back(
            new Show(movies[2], screen1, "10:30 PM")
        );

        shows.push_back(
            new Show(movies[3], screen1, "12:00 PM")
        );

        shows.push_back(
            new Show(movies[3], screen1, "6:00 PM")
        );

        shows.push_back(
            new Show(movies[4], screen1, "3:00 PM")
        );

        shows.push_back(
            new Show(movies[4], screen1, "8:30 PM")
        );

        // --------------------------------
        // CUSTOMER
        // --------------------------------

        
    }


    void listMovies() {

        cout << "\n============================================\n";
        cout << "              MOVIES\n";
        cout << "============================================\n";

        for (size_t i = 0; i < movies.size(); i++) {

            cout << i + 1 << ". "
                 << movies[i]->getTitle()
                 << " | "
                 << movies[i]->getLanguage()
                 << " | "
                 << movies[i]->getDuration()
                 << " min\n";
        }
    }


    void listShowsForMovie(Movie* movie) {

        cout << "\n============================================\n";
        cout << "Shows for " << movie->getTitle() << "\n";
        cout << "============================================\n";

        bool found = false;

        for (Show* show : shows) {

            if (show->getMovie() == movie) {

                cout << "Show ID: "
                     << show->getShowId()
                     << " | Screen "
                     << show->getScreen()->getScreenNumber()
                     << " | "
                     << show->getStartTime()
                     << "\n";

                found = true;
            }
        }

        if (!found)
            cout << "No shows available.\n";
    }


    Show* findShowById(int showId) {

        for (Show* show : shows) {

            if (show->getShowId() == showId)
                return show;
        }

        return nullptr;
    }


    Booking* findBookingById(int bookingId) {

        for (Booking* booking : bookings) {

            if (booking->getBookingId() == bookingId)
                return booking;
        }

        return nullptr;
    }


    // --------------------------------
    // OPTION 1
    // --------------------------------

    void handleListMovies() {

        listMovies();
    }


    // --------------------------------
    // OPTION 2
    // --------------------------------

    void handleListShows() {

        listMovies();

        cout << "\nSelect movie number: ";

        int choice = readIntChoice();

        if (choice < 1 || choice > (int)movies.size()) {

            cout << "Invalid movie selection.\n";
            return;
        }

        listShowsForMovie(movies[choice - 1]);
    }


    // --------------------------------
    // OPTION 3
    // --------------------------------

    void handleDisplaySeats() {

        cout << "\nEnter Show ID: ";

        int showId = readIntChoice();

        Show* show = findShowById(showId);

        if (show == nullptr) {

            cout << "Invalid show selection.\n";
            return;
        }

        cout << "\n--------------------------------------------\n";
        cout << "Movie : "
             << show->getMovie()->getTitle()
             << "\n";

        cout << "Time  : "
             << show->getStartTime()
             << "\n";

        cout << "--------------------------------------------\n";

        show->displaySeats();
    }


    // --------------------------------
    // OPTION 4
    // BOOK TICKET
    // --------------------------------

    void handleBookSeats() {

        cout << "\nEnter Show ID: ";

        int showId = readIntChoice();

        Show* show = findShowById(showId);

        if (show == nullptr) {

            cout << "Invalid show selection.\n";
            return;
        }

        cout << "\nSelected Movie: "
             << show->getMovie()->getTitle()
             << "\n";

        cout << "Show Time: "
             << show->getStartTime()
             << "\n\n";

        show->displaySeats();

        cout << "\nEnter number of seats to book: ";

        int count = readIntChoice();

        if (count <= 0 || count > 6) {

            cout << "Invalid seat count.\n";
            return;
        }

        vector<string> seatNumbers;

        for (int i = 0; i < count; i++) {

            cout << "Enter seat number "
                 << i + 1 << ": ";

            string seatNumber;
            cin >> seatNumber;

            seatNumbers.push_back(seatNumber);
        }


        // --------------------------------
        // CUSTOMER DETAILS
        // --------------------------------

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string name;
        string phone;

        cout << "\nEnter customer name: ";
        getline(cin, name);

        cout << "Enter phone number: ";
        getline(cin, phone);

        Customer bookingCustomer(name, phone);


        // --------------------------------
        // PAYMENT
        // --------------------------------

        cout << "\n============================================\n";
        cout << "             PAYMENT METHOD\n";
        cout << "============================================\n";

        cout << "1. UPI\n";
        cout << "2. Card\n";
        cout << "3. Cash\n";

        cout << "Enter choice: ";

        int paymentChoice = readIntChoice();

        Payment* payment = nullptr;

        if (paymentChoice == 1) {

            string upiId;

            cout << "Enter UPI ID: ";
            cin >> upiId;

            payment = new UpiPayment(upiId);
        }

        else if (paymentChoice == 2) {

            string cardNumber;

            cout << "Enter card number: ";
            cin >> cardNumber;

            payment = new CardPayment(cardNumber);
        }

        else if (paymentChoice == 3) {

            payment = new CashPayment();
        }

        else {

            cout << "Invalid payment method.\n";
            return;
        }


        // --------------------------------
        // BOOK
        // --------------------------------

        Booking* booking =
        bookingService.bookTicket(
        bookingCustomer,
        show,
        seatNumbers,
        *payment
    );

        if (booking != nullptr) {

            bookings.push_back(booking);
        }

        delete payment;
    }


    // --------------------------------
    // OPTION 5
    // --------------------------------

    void handleCancelBooking() {

        if (bookings.empty()) {

            cout << "No bookings available.\n";
            return;
        }

        cout << "\n============================================\n";
        cout << "          CONFIRMED BOOKINGS\n";
        cout << "============================================\n";

        bool found = false;

        for (Booking* booking : bookings) {

            if (booking->getStatus() == BookingStatus::CONFIRMED) {

                cout << "Booking ID : "
                     << booking->getBookingId()
                     << " | Movie : "
                     << booking->getShow()->getMovie()->getTitle()
                     << " | Show : "
                     << booking->getShow()->getStartTime()
                     << "\n";

                found = true;
            }
        }

        if (!found) {

            cout << "No confirmed bookings available.\n";
            return;
        }

        cout << "\nEnter Booking ID to cancel: ";

        int bookingId = readIntChoice();

        Booking* booking = findBookingById(bookingId);

        if (booking == nullptr) {

            cout << "Invalid booking ID.\n";
            return;
        }

        if (bookingService.cancelBooking(booking)) {

            cout << "Booking "
                 << bookingId
                 << " cancelled successfully.\n";

            cout << "Seats are AVAILABLE again.\n";
        }

        else {

            cout << "Booking cannot be cancelled.\n";
        }
    }


    // --------------------------------
    // MENU
    // --------------------------------

    void displayMenu() {

        cout << "\n\n============================================\n";
        cout << "       MOVIE TICKET BOOKING SYSTEM\n";
        cout << "============================================\n";

        cout << "1. List Movies\n";
        cout << "2. List Shows for a Movie\n";
        cout << "3. Display Seats for a Show\n";
        cout << "4. Book Seats\n";
        cout << "5. Cancel Booking\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
    }


public:

    MainMenu()
        : cinema("PVR Cinema"),
          bookingService(&priceCalculator, &ticketPrinter) {

        setupData();
    }


    ~MainMenu() {

        // Delete bookings first
        for (Booking* booking : bookings)
            delete booking;

        // Delete shows and their ShowSeats
        for (Show* show : shows)
            delete show;

        // Delete movies
        for (Movie* movie : movies)
            delete movie;

        // Delete physical seats
        vector<Screen*> screens = cinema.getScreens();

        for (Screen* screen : screens) {

            vector<Seat*> seats = screen->getSeats();

            for (Seat* seat : seats)
                delete seat;

            delete screen;
        }
    }


    void run() {

        bool running = true;

        while (running) {

            displayMenu();

            int choice = readIntChoice();

            switch (choice) {

                case 1:
                    handleListMovies();
                    break;

                case 2:
                    handleListShows();
                    break;

                case 3:
                    handleDisplaySeats();
                    break;

                case 4:
                    handleBookSeats();
                    break;

                case 5:
                    handleCancelBooking();
                    break;

                case 6:
                    running = false;
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }

        cout << "\nThank you for using the Movie Ticket Booking System!\n";
    }
};

#endif