#include "TimeUtils.h"

TimeUtils::TimeUtils() {}

string TimeUtils::getCurrentDate(bool time) {
    auto now = system_clock::now();

    time_t nowTime = system_clock::to_time_t(now);
    tm localTime = *localtime(&nowTime);

    stringstream dateStream;
    if (time) 
        dateStream << put_time(&localTime, "%d-%m-%Y %H:%M:%S");
    else 
        dateStream << put_time(&localTime, "%d-%m-%Y");
    return dateStream.str();
}

string TimeUtils::loadLastOpenDate() {
    ifstream file(lastOpenDateFile);
    string date;
    
    if (file.is_open()) {
        getline(file, date);
        file.close();
    } else {
        cout << "No last open date file found. Creating new file." << endl;
        saveLastOpenDate();
    }
    return date;
}

void TimeUtils::saveLastOpenDate() {
    ofstream file(lastOpenDateFile);
    if (file.is_open()) {
        file << getCurrentDate(false);
        file.close();
    } else {
        cerr << "Error: Unable to open or create file for saving the last open date." << endl;
    }
}

bool TimeUtils::isNewMonth() {
    
    if (toNewMonth) {
        return true;
    }

    string lastOpenDate = loadLastOpenDate();
    if (lastOpenDate.empty()) {
        saveLastOpenDate();
        return false;
    }

    tm lastDateStruct = {};
    stringstream dateStream(lastOpenDate);
    dateStream >> get_time(&lastDateStruct, "%d-%m-%Y");

    auto now = system_clock::now();
    time_t nowTime = system_clock::to_time_t(now);
    tm currentDate = *localtime(&nowTime);

    bool newMonthPassed = (currentDate.tm_year > lastDateStruct.tm_year) ||
                          (currentDate.tm_year == lastDateStruct.tm_year && currentDate.tm_mon > lastDateStruct.tm_mon);

    if (newMonthPassed) {
        saveLastOpenDate();
    }

    return newMonthPassed;
}