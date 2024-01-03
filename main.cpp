#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int NUM_BOATS = 10;
const int OPEN_HOUR = 10;
const int CLOSE_HOUR = 17;
const float HOUR_RATE = 20.0;
const float HALF_HOUR_RATE = 12.0;

struct Boat {
    float moneyTaken;
    float hoursHired;
    int returnTime;
};

// Task 1 - Calculate the money taken in a day for one boat
void calculateMoneyTaken(Boat &boat, int currentTime) {
    if (currentTime < OPEN_HOUR || currentTime >= CLOSE_HOUR) {
        cout << "Boat cannot be hired at this time." << endl;
        return;
    }

    int hireDuration;
    cout << "Enter the duration of hire (in minutes) for Boat: ";
    cin >> hireDuration;

    if (hireDuration <= 0 || hireDuration > 420) { // 420 minutes = 7 hours (17:00 - 10:00)
        cout << "Invalid hire duration." << endl;
        return;
    }

    float payment;
    if (hireDuration <= 30) {
        payment = HALF_HOUR_RATE;
    } else {
        int hours = hireDuration / 60;
        int minutes = hireDuration % 60;
        if (minutes > 0) {
            ++hours;
        }
        payment = hours * HOUR_RATE;
    }

    boat.moneyTaken += payment;
    boat.hoursHired += static_cast<float>(hireDuration) / 60;
    boat.returnTime = currentTime + (hireDuration / 60);

    cout << "Money taken for the day: $" << fixed << setprecision(2) << boat.moneyTaken << endl;
    cout << "Total hours hired for the day: " << boat.hoursHired << " hours" << endl;
}

// Task 2 - Find the next boat available
void findNextAvailableBoat(const vector<Boat> &boats, int currentTime) {
    int availableCount = 0;
    int earliestReturn = CLOSE_HOUR;

    for (const auto &boat : boats) {
        if (boat.returnTime <= currentTime) {
            ++availableCount;
        } else if (boat.returnTime < earliestReturn) {
            earliestReturn = boat.returnTime;
        }
    }

    if (availableCount > 0) {
        cout << "Number of boats available for hire: " << availableCount << endl;
    } else {
        cout << "No boats available for hire. Earliest available time: " << earliestReturn << ":00" << endl;
    }
}

// Task 3 - Calculate the money taken for all the boats at the end of the day
void calculateEndOfDaySummary(const vector<Boat> &boats) {
    float totalMoneyTaken = 0;
    float totalHoursHired = 0;
    int unusedBoats = 0;
    int mostUsedBoatIndex = 0;

    for (int i = 0; i < boats.size(); ++i) {
        totalMoneyTaken += boats[i].moneyTaken;
        totalHoursHired += boats[i].hoursHired;

        if (boats[i].hoursHired == 0) {
            ++unusedBoats;
        }

        if (boats[i].hoursHired > boats[mostUsedBoatIndex].hoursHired) {
            mostUsedBoatIndex = i;
        }
    }

    cout << "Total money taken for all boats: $" << fixed << setprecision(2) << totalMoneyTaken << endl;
    cout << "Total hours boats were hired: " << totalHoursHired << " hours" << endl;
    cout << "Number of boats not used: " << unusedBoats << endl;
    cout << "Boat used the most: Boat " << mostUsedBoatIndex + 1 << " with " << boats[mostUsedBoatIndex].hoursHired << " hours" << endl;
}

int main() {
    vector<Boat> boats(NUM_BOATS);

    int currentTime;
    cout << "Enter the current time (in 24-hour format): ";
    cin >> currentTime;

    // Task 1 - Calculate the money taken in a day for one boat
    for (int i = 0; i < NUM_BOATS; ++i) {
        cout << "\nBoat " << i + 1 << ":" << endl;
        calculateMoneyTaken(boats[i], currentTime);
    }

    // Task 2 - Find the next boat available
    findNextAvailableBoat(boats, currentTime);

    // Task 3 - Calculate the money taken for all the boats at the end of the day
    calculateEndOfDaySummary(boats);

    return 0;
}
