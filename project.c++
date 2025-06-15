#include <iostream>
#include <string>

using namespace std;

struct Node {
    int seatNumber;
    bool isBooked;
    Node* next;
    Node* prev;

    Node(int number) : seatNumber(number), isBooked(false), next(nullptr), prev(nullptr) {}
};

class TrainReservationSystem {
private:
    Node* head;
    Node* tail;
    int totalSeats;

public:
    TrainReservationSystem(int seats) : totalSeats(seats), head(nullptr), tail(nullptr) {
        for (int i = 1; i <= totalSeats; ++i) {
            Node* newNode = new Node(i);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }

    void bookSeat(int seatNumber) {
        Node* current = head;
        while (current) {
            if (current->seatNumber == seatNumber) {
                if (!current->isBooked) {
                    current->isBooked = true;
                    cout << "Seat " << seatNumber << " booked successfully." << endl;
                } else {
                    cout << "Seat " << seatNumber << " is already booked." << endl;
                }
                return;
            }
            current = current->next;
        }
        cout << "Seat " << seatNumber << " does not exist." << endl;
    }

    void cancelSeat(int seatNumber) {
        Node* current = head;
        while (current) {
            if (current->seatNumber == seatNumber) {
                if (current->isBooked) {
                    current->isBooked = false;
                    cout << "Seat " << seatNumber << " canceled successfully." << endl;
                } else {
                    cout << "Seat " << seatNumber << " is not booked." << endl;
                }
                return;
            }
            current = current->next;
        }
        cout << "Seat " << seatNumber << " does not exist." << endl;
    }

    void displayAvailableSeats() {
        Node* current = head;
        cout << "Available Seats: ";
        bool found = false;
        while (current) {
            if (!current->isBooked) {
                cout << current->seatNumber << " ";
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "No available seats.";
        }
        cout << endl;
    }

    ~TrainReservationSystem() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    int totalSeats;
    cout << "Enter the total number of seats: ";
    cin >> totalSeats;

    TrainReservationSystem train(totalSeats);
    int choice, seatNumber;

    do {
        cout << "\n1. Display Available Seats\n2. Book a Seat\n3. Cancel a Seat\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                train.displayAvailableSeats();
                break;
            case 2:
                cout << "Enter seat number to book: ";
                cin >> seatNumber;
                train.bookSeat(seatNumber);
                break;
            case 3:
                cout << "Enter seat number to cancel: ";
                cin >> seatNumber;
                train.cancelSeat(seatNumber);
                break;
            case 4:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}