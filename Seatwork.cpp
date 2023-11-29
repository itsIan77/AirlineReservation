#include <iostream>
#include <cstdlib>
#include <ctime>

const int numAirplanes = 3;
const int numRows = 2;
const int numSeatsPerRow = 5;

// Prototype for each airplane's seat layout
const bool seatPrototype[numRows][numSeatsPerRow] = {
    {false, false, false, false, false},
    {false, false, false, false, false}
};

bool seats[numAirplanes][numRows][numSeatsPerRow];

void displaySeats(int airplaneIndex) {
    std::cout << "Airplane " << airplaneIndex + 1 << " - Seat Availability:\n";
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numSeatsPerRow; ++j) {
            std::cout << (seats[airplaneIndex][i][j] ? "X" : "O") << " ";
        }
        std::cout << "\n";
    }
}

bool assignSeat(int airplaneIndex, int seatType, int& row, int& col, int assignmentMethod) {
    if (seatType != 1 && seatType != 2) {
        std::cout << "Invalid seat type.\n";
        return false;
    }

    row = (seatType == 1) ? 0 : 1;

    if (assignmentMethod == 1) { // for manual assignment
        for (int j = 0; j < numSeatsPerRow; ++j) {
            if (!seats[airplaneIndex][row][j]) {
                col = j;
                seats[airplaneIndex][row][col] = true;
                return true;
            }
        }
    }
    else if (assignmentMethod == 2) { // For Random assignment
        // Generating a random seat in the chosen section
        col = rand() % numSeatsPerRow;
        if (!seats[airplaneIndex][row][col]) {
            seats[airplaneIndex][row][col] = true;
            return true;
        }
    }

    return false;
}

void boardingPass(int airplaneIndex, int row, int col, int seatType) {
    std::string section = (seatType == 1) ? "Economy Plus" : "Economy";
    std::cout << "\nBoarding Pass - Airplane " << airplaneIndex + 1 << ":\n";
    std::cout << "Seat Number: " << row + 1 << char('A' + col) << "\n";
    std::cout << "Section: " << section << "\n";
}

int main() {
    //For initialize seats based on the prototype for each airplane
    for (int i = 0; i < numAirplanes; ++i) {
        for (int j = 0; j < numRows; ++j) {
            for (int k = 0; k < numSeatsPerRow; ++k) {
                seats[i][j][k] = seatPrototype[j][k];
            }
        }
    }

    srand(time(0));

    for (int airplaneIndex = 0; airplaneIndex < numAirplanes; ++airplaneIndex) {
        //For displaying available seats for the current airplane
        displaySeats(airplaneIndex);

        // Looping until all seats in the current airplane are filled
        while (true) {
            std::cout << "\nEnter seat type (1 for Economy Plus, 2 for Economy, or 0 to exit): ";
            int seatType;
            std::cin >> seatType;

            if (seatType == 0) {
                std::cout << "Exiting the program. Thank you!\n";
                return 0;
            }

            if (seatType != 1 && seatType != 2) {
                std::cout << "Invalid seat type.\n";
                continue;
            }

            std::cout << "Choose assignment method (1 for manual, 2 for random): ";
            int assignmentMethod;
            std::cin >> assignmentMethod;

            int row, col;

            if (assignSeat(airplaneIndex, seatType, row, col, assignmentMethod)) {
                std::cout << "Seat assigned successfully.\n";
                boardingPass(airplaneIndex, row, col, seatType);
                displaySeats(airplaneIndex);  // For displaying seats after assignment for debugging
            }
            else {
                std::cout << "The chosen section is full.\n";

                // Checking if both sections are full in the current airplane
                bool isAirplaneFull = true;
                for (int i = 0; i < numRows; ++i) {
                    for (int j = 0; j < numSeatsPerRow; ++j) {
                        if (!seats[airplaneIndex][i][j]) {
                            isAirplaneFull = false;
                            break;
                        }
                    }
                    if (!isAirplaneFull) {
                        break;
                    }
                }

                // If both sections are full in the current airplane, then it move's to the next airplane
                if (isAirplaneFull) {
                    std::cout << "Both sections are full in this airplane. Moving to the next airplane.\n";
                    break;
                }
                else {
                    std::cout << "Trying the other section.\n";
                }
            }
        }
    }

    std::cout << "All airplanes are full. Exiting the program. Thank you!\n";

    return 0;
}
