#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// ============================================
// INCLUDE CLASS DECLARATIONS
// ============================================

#include "Movie.cpp"
#include "Seat.cpp"
#include "ShowSeat.cpp"
#include "Screen.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"
#include "Cinema.cpp"


// ============================================
// MOVIE
// ============================================

Movie::Movie(
    string title,
    string language,
    int duration
)
    : title(title),
      language(language),
      duration(duration) {
}


string Movie::getTitle() const {
    return title;
}


string Movie::getLanguage() const {
    return language;
}


int Movie::getDuration() const {
    return duration;
}


// ============================================
// SEAT
// ============================================

Seat::Seat(
    string seatNumber,
    SeatType seatType
)
    : seatNumber(seatNumber),
      seatType(seatType) {
}


string Seat::getSeatNumber() const {
    return seatNumber;
}


SeatType Seat::getSeatType() const {
    return seatType;
}


// ============================================
// SHOW SEAT
// ============================================

ShowSeat::ShowSeat(Seat* seat)
    : seat(seat),
      status(SeatStatus::AVAILABLE) {
}


bool ShowSeat::isAvailable() const {

    return status == SeatStatus::AVAILABLE;
}


bool ShowSeat::isBooked() const {

    return status == SeatStatus::BOOKED;
}


bool ShowSeat::bookSeat() {

    if (status == SeatStatus::BOOKED)
        return false;

    status = SeatStatus::BOOKED;

    return true;
}


void ShowSeat::releaseSeat() {

    status = SeatStatus::AVAILABLE;
}


Seat* ShowSeat::getSeat() const {

    return seat;
}


// ============================================
// SCREEN
// ============================================

Screen::Screen(int screenNumber)
    : screenNumber(screenNumber) {
}


void Screen::addSeat(Seat* seat) {

    seats.push_back(seat);
}


vector<Seat*> Screen::getSeats() const {

    return seats;
}


int Screen::getScreenNumber() const {

    return screenNumber;
}


// ============================================
// SHOW
// ============================================

int Show::nextShowId = 1;


Show::Show(
    Movie* movie,
    Screen* screen,
    string startTime
)
    : movie(movie),
      screen(screen),
      startTime(startTime) {

    // Create separate ShowSeat objects
    // for every physical seat.

    for (Seat* seat : screen->getSeats()) {

        addShowSeat(
            new ShowSeat(seat)
        );
    }

    showId = nextShowId++;
}


Show::~Show() {

    for (ShowSeat* showSeat : showSeats)
        delete showSeat;

    showSeats.clear();
}


void Show::addShowSeat(
    ShowSeat* showSeat
) {

    showSeats.push_back(showSeat);
}


int Show::getShowId() const {

    return showId;
}


Movie* Show::getMovie() const {

    return movie;
}


Screen* Show::getScreen() const {

    return screen;
}


string Show::getStartTime() const {

    return startTime;
}


vector<ShowSeat*> Show::getShowSeats() const {

    return showSeats;
}


ShowSeat* Show::findShowSeat(
    const string& seatNumber
) const {

    for (ShowSeat* showSeat : showSeats) {

        if (
            showSeat->getSeat()->getSeatNumber()
            == seatNumber
        ) {

            return showSeat;
        }
    }

    return nullptr;
}


void Show::displaySeats() const {

    cout << "\n";

    for (ShowSeat* showSeat : showSeats) {

        cout << "Seat "
             << showSeat->getSeat()->getSeatNumber()
             << " [";

        SeatType type =
            showSeat->getSeat()->getSeatType();

        if (type == SeatType::SILVER)
            cout << "SILVER";

        else if (type == SeatType::GOLD)
            cout << "GOLD";

        else
            cout << "PLATINUM";

        cout << "] - ";

        if (showSeat->isAvailable())
            cout << "AVAILABLE";

        else
            cout << "BOOKED";

        cout << "\n";
    }
}


// ============================================
// CUSTOMER
// ============================================

Customer::Customer(
    string name,
    string phone
)
    : name(name),
      phone(phone) {
}


string Customer::getName() const {

    return name;
}


string Customer::getPhone() const {

    return phone;
}


// ============================================
// BOOKING
// ============================================

int Booking::nextBookingId = 1001;

Booking::Booking(
    Customer customer,
    Show* show,
    vector<ShowSeat*> seats,
    Payment* payment,
    double totalAmount
)
    : customer(customer),
      show(show),
      seats(seats),
      payment(payment),
      totalAmount(totalAmount),
      status(BookingStatus::PENDING) {

    bookingId = nextBookingId++;
}




void Booking::confirmBooking() {

    status = BookingStatus::CONFIRMED;
}


void Booking::failBooking() {

    status = BookingStatus::FAILED;
}


void Booking::cancelBooking() {

    for (ShowSeat* seat : seats)
        seat->releaseSeat();

    status = BookingStatus::CANCELLED;
}


int Booking::getBookingId() const {

    return bookingId;
}


Customer Booking::getCustomer() const {

    return customer;
}

Show* Booking::getShow() const {

    return show;
}


vector<ShowSeat*> Booking::getSeats() const {

    return seats;
}


Payment* Booking::getPayment() const {

    return payment;
}


double Booking::getTotalAmount() const {

    return totalAmount;
}


BookingStatus Booking::getStatus() const {

    return status;
}


string Booking::getStatusString() const {

    switch (status) {

        case BookingStatus::PENDING:
            return "PENDING";

        case BookingStatus::CONFIRMED:
            return "CONFIRMED";

        case BookingStatus::FAILED:
            return "FAILED";

        case BookingStatus::CANCELLED:
            return "CANCELLED";
    }

    return "UNKNOWN";
}


// ============================================
// PRICE CALCULATOR
// ============================================

double PriceCalculator::getSeatPrice(
    SeatType type
) const {

    switch (type) {

        case SeatType::SILVER:
            return 150.0;

        case SeatType::GOLD:
            return 250.0;

        case SeatType::PLATINUM:
            return 400.0;
    }

    return 0.0;
}


double PriceCalculator::calculateTotal(
    const vector<ShowSeat*>& seats
) const {

    double total = 0.0;

    for (ShowSeat* seat : seats) {

        total += getSeatPrice(
            seat->getSeat()->getSeatType()
        );
    }

    return total;
}


// ============================================
// TICKET PRINTER
// ============================================

void TicketPrinter::printTicket(
    const Booking& booking
) const {

    cout << "\n";
    cout << "============================================\n";
    cout << "                 TICKET\n";
    cout << "============================================\n";

    cout << "Booking ID : "
         << booking.getBookingId()
         << "\n";

    cout << "Customer   : "
     << booking.getCustomer().getName()
     << "\n";

    cout << "Phone      : "
     << booking.getCustomer().getPhone()
     << "\n";

    cout << "Movie      : "
         << booking.getShow()->getMovie()->getTitle()
         << "\n";

    cout << "Screen     : "
         << booking.getShow()->getScreen()->getScreenNumber()
         << "\n";

    cout << "Show Time  : "
         << booking.getShow()->getStartTime()
         << "\n";

    cout << "Seats      : ";

    vector<ShowSeat*> seats =
        booking.getSeats();

    for (size_t i = 0; i < seats.size(); i++) {

        if (i > 0)
            cout << ", ";

        cout << seats[i]
                    ->getSeat()
                    ->getSeatNumber();
    }

    cout << "\n";

    cout << "Paid via   : "
         << booking.getPayment()->getMethodName()
         << "\n";

    cout << "Total      : Rs."
         << fixed
         << setprecision(2)
         << booking.getTotalAmount()
         << "\n";

    cout << "Status     : "
         << booking.getStatusString()
         << "\n";

    cout << "============================================\n";
}


// ============================================
// BOOKING SERVICE
// ============================================

BookingService::BookingService(
    PriceCalculator* priceCalculator,
    TicketPrinter* ticketPrinter
)
    : priceCalculator(priceCalculator),
      ticketPrinter(ticketPrinter) {
}


bool BookingService::selectSeats(
    Show* show,
    const vector<string>& seatNumbers,
    vector<ShowSeat*>& selectedSeats
) const {

    for (const string& requested : seatNumbers) {

        ShowSeat* seat =
            show->findShowSeat(requested);

        if (seat == nullptr) {

            cout << "Seat "
                 << requested
                 << " does not exist.\n";

            return false;
        }


        if (!seat->isAvailable()) {

            cout << "Seat "
                 << requested
                 << " is already BOOKED.\n";

            return false;
        }


        // Duplicate seat check

        if (
            find(
                selectedSeats.begin(),
                selectedSeats.end(),
                seat
            )
            != selectedSeats.end()
        ) {

            cout << "Seat "
                 << requested
                 << " was selected more than once.\n";

            return false;
        }


        selectedSeats.push_back(seat);
    }

    return true;
}


bool BookingService::processPayment(
    Booking* booking,
    Payment& payment
) const {

    bool paid =
        payment.pay(
            booking->getTotalAmount()
        );


    if (paid) {

        for (ShowSeat* seat :
             booking->getSeats()) {

            seat->bookSeat();
        }

        booking->confirmBooking();

        return true;
    }


    // Payment failed
    // Release seats

    for (ShowSeat* seat :
         booking->getSeats()) {

        seat->releaseSeat();
    }

    booking->failBooking();

    return false;
}


Booking* BookingService::bookTicket(
    Customer customer,
    Show* show,
    const vector<string>& seatNumbers,
    Payment& payment
) {

    vector<ShowSeat*> selectedSeats;


    // Validate all seats first

    if (
        !selectSeats(
            show,
            seatNumbers,
            selectedSeats
        )
    ) {

        return nullptr;
    }


    // Calculate price

    double total =
        priceCalculator->calculateTotal(
            selectedSeats
        );


    // Create booking

    Booking* booking =
        new Booking(
            customer,
            show,
            selectedSeats,
            &payment,
            total
        );


    // Process payment

    if (
        !processPayment(
            booking,
            payment
        )
    ) {

        cout << "\nPayment failed.\n";
        cout << "Seats released.\n";

        cout << "Booking ID: "
             << booking->getBookingId()
             << " | Status: "
             << booking->getStatusString()
             << "\n";

        return booking;
    }


    // Successful booking

    ticketPrinter->printTicket(
        *booking
    );

    return booking;
}


bool BookingService::cancelBooking(
    Booking* booking
) {

    if (
        booking == nullptr ||
        booking->getStatus()
            != BookingStatus::CONFIRMED
    ) {

        return false;
    }


    booking->cancelBooking();

    return true;
}


// ============================================
// CINEMA
// ============================================

Cinema::Cinema(string name)
    : name(name) {
}


void Cinema::addScreen(
    Screen* screen
) {

    screens.push_back(screen);
}


vector<Screen*> Cinema::getScreens() const {

    return screens;
}


void Cinema::listMovies(
    const vector<Movie*>& movies
) const {

    cout << "\n============================================\n";
    cout << "             CURRENT MOVIES\n";
    cout << "============================================\n";

    for (size_t i = 0; i < movies.size(); i++) {

        cout << i + 1
             << ". "
             << movies[i]->getTitle()
             << " ("
             << movies[i]->getLanguage()
             << ", "
             << movies[i]->getDuration()
             << " min)"
             << "\n";
    }
}