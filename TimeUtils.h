#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace std::chrono;

class TimeUtils {
public:
    TimeUtils();
    bool toNewMonth = false;

    string getCurrentDate(bool time);
    string loadLastOpenDate();
    bool isNewMonth();
    void saveLastOpenDate();

private:
    const string lastOpenDateFile = "./last_open_date.txt";
};

#endif // TIMEUTIL_H