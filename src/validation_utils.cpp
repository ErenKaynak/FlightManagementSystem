#include "Admin.h"
#include <ctime>
#include <iostream>
#include <limits>
using namespace std;

string Admin::generateFlightId() {
  int maxNum = 0;
  for (const auto &flight : flights) {
    string id = flight.getFlightId();
    if (id.length() > 3 && id.substr(0, 3) == "FL-") {
      try {
        int num = stoi(id.substr(3));
        if (num > maxNum)
          maxNum = num;
      } catch (...) {
      }
    }
  }
  return "FL-" + to_string(maxNum + 1);
}

int Admin::findFlightIndex(string flightId) {
  for (size_t i = 0; i < flights.size(); i++) {
    if (flights[i].getFlightId() == flightId) {
      return i;
    }
  }
  return -1;
}

int Admin::findAircraftIndex(string aircraftId) {
  for (size_t i = 0; i < aircrafts.size(); i++) {
    if (aircrafts[i].getAircraftId() == aircraftId) {
      return i;
    }
  }
  return -1;
}

void Admin::pause() {
  cout << "\nPress any key to continue...";
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}

bool Admin::isDateValid(string date) {
  if (date.length() != 10)
    return false;
  if (date[4] != '-' || date[7] != '-')
    return false;

  try {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1900 || year > 2100)
      return false;
    if (month < 1 || month > 12)
      return false;
    if (day < 1 || day > 31)
      return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
      return false;
    if (month == 2 && day > 29)
      return false;

    return true;
  } catch (...) {
    return false;
  }
}

bool Admin::isDateExpired(string date) {
  if (!isDateValid(date))
    return true;

  time_t now = time(0);
  tm *ltm = localtime(&now);

  int currentYear = 1900 + ltm->tm_year;
  int currentMonth = 1 + ltm->tm_mon;
  int currentDay = ltm->tm_mday;

  try {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < currentYear)
      return true;
    if (year == currentYear && month < currentMonth)
      return true;
    if (year == currentYear && month == currentMonth && day < currentDay)
      return true;

    return false;
  } catch (...) {
    return true;
  }
}

int Admin::compareTimes(string time1, string time2) {

  if (time1.empty() || time2.empty())
    return 0;

  try {
    int hour1 = stoi(time1.substr(0, 2));
    int min1 = stoi(time1.substr(3, 2));
    int hour2 = stoi(time2.substr(0, 2));
    int min2 = stoi(time2.substr(3, 2));

    int total1 = hour1 * 60 + min1;
    int total2 = hour2 * 60 + min2;

    if (total1 < total2)
      return -1;
    if (total1 > total2)
      return 1;
    return 0;
  } catch (...) {
    return 0;
  }
}

bool Admin::isAircraftAvailable(string aircraftId, string date, string depTime,
                                string arrTime, int excludeFlightIndex) {
  if (depTime.empty() || arrTime.empty())
    return true;

  for (size_t i = 0; i < flights.size(); i++) {
    if (static_cast<int>(i) == excludeFlightIndex)
      continue;

    Flight &flight = flights[i];
    if (flight.getAircraft().getAircraftId() == aircraftId &&
        flight.getDate() == date) {
      string flightDep = flight.getDepartureTime();
      string flightArr = flight.getArrivalTime();

      if (flightDep.empty() || flightArr.empty())
        continue;

      if ((compareTimes(depTime, flightDep) >= 0 &&
           compareTimes(depTime, flightArr) <= 0) ||
          (compareTimes(arrTime, flightDep) >= 0 &&
           compareTimes(arrTime, flightArr) <= 0) ||
          (compareTimes(depTime, flightDep) <= 0 &&
           compareTimes(arrTime, flightArr) >= 0)) {
        return false;
      }
    }
  }
  return true;
}

bool Admin::isPilotAvailable(string pilotId, string date, string depTime,
                             string arrTime, int excludeFlightIndex) {
  if (depTime.empty() || arrTime.empty())
    return true;

  for (size_t i = 0; i < flights.size(); i++) {
    if (static_cast<int>(i) == excludeFlightIndex)
      continue;

    Flight &flight = flights[i];
    if (flight.getPilotId() == pilotId && flight.getDate() == date) {
      string flightDep = flight.getDepartureTime();
      string flightArr = flight.getArrivalTime();

      if (flightDep.empty() || flightArr.empty())
        continue;

      if ((compareTimes(depTime, flightDep) >= 0 &&
           compareTimes(depTime, flightArr) <= 0) ||
          (compareTimes(arrTime, flightDep) >= 0 &&
           compareTimes(arrTime, flightArr) <= 0) ||
          (compareTimes(depTime, flightDep) <= 0 &&
           compareTimes(arrTime, flightArr) >= 0)) {
        return false;
      }
    }
  }
  return true;
}
