#include <iostream>
#include <ctime>
#include <chrono>
#include <string>

/**
    This function returns a fraction of a current second. 
    Accepts the time data type from the chrono library as a template.
    
    Possible specializations:
    std::chrono::nanoseconds
    std::chrono::microseconds
    std::chrono::milliseconds

    All other specifications don't make sense
*/
template <class T>
int64_t GetCurrentSecondFraction()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::high_resolution_clock::now();
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    auto t = std::chrono::duration_cast<T>(now.time_since_epoch()).count();
    return t % sec;
}

/// Return current second
int GetCurrentSecond()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return ltm->tm_sec;
}

/// Return current minute
int GetCurrentMinute()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return ltm->tm_min;
}

/// Return current hour
int GetCurrentHour()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return ltm->tm_hour;
}

/// Return the current day of the month
int GetCurrentMonthDay()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return ltm->tm_mday;
}

/// Return the current day of the year
int GetCurrentYearDay()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return (ltm->tm_yday + 1);
}

/// Return current month
int GetCurrentMonth()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return (ltm->tm_mon + 1);
}

/// Return current year
int GetCurrentYear()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return (ltm->tm_year + 1900);
}

/// Returns the name of today's day of the week
std::string GetCurrentDayWeek()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    switch(ltm->tm_wday)
    {
    case 0: return "Monday";
    case 1: return "Tuesday";
    case 2: return "Wednesday"; 
    case 3: return "Thursday";
    case 4: return "Friday";
    case 5: return "Saturday";
    case 6: return "Sunday";
    }
    return "";
}


/** 
    \brief Function for getting the current date
    \param [in] IsAmericanFormat A variable for specifying the format of the returned date. By default, the parameter is false
    If the parameter is empty or false, the function returns the date in normal format: dd.mm.yyyy.
    Otherwise it will return in the american format: mm.dd.yyyy.
    \return Return current date in string with format: dd.mm.yyyy or mm.dd.yyyy depends on input param
*/  
std::string GetCurrentDate(bool IsAmericanFormat = false)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string currentDate;

    if (IsAmericanFormat)
    {
        if (ltm->tm_mon < 9) currentDate += "0";
        currentDate += std::to_string(ltm->tm_mon + 1);
        currentDate += ".";

        if (ltm->tm_mday < 10) currentDate += "0";
        currentDate += std::to_string(ltm->tm_mday);
        currentDate += ".";
    }
    else
    {
        if (ltm->tm_mday < 10) currentDate += "0";
        currentDate += std::to_string(ltm->tm_mday);
        currentDate += ".";

        if (ltm->tm_mon < 9) currentDate += "0";
        currentDate += std::to_string(ltm->tm_mon + 1);
        currentDate += ".";
    }

    currentDate += std::to_string(1900 + ltm->tm_year);

    return currentDate;
}

/// Return current day time in format: hh.mm.ss
std::string GetCurrentDayTime()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string currentTime;

    if (ltm->tm_hour < 10) currentTime += "0";
    currentTime += std::to_string(ltm->tm_hour);
    currentTime += ".";
    if (ltm->tm_min < 10) currentTime += "0";
    currentTime += std::to_string(ltm->tm_min);
    currentTime += ".";
    if (ltm->tm_sec < 10) currentTime += "0";
    currentTime += std::to_string(ltm->tm_sec);
    
    return currentTime;
}

/**
    This function returns current day time in format: hh.mm.ss.ff. Where f is fraction of a second 
    Accepts the time data type from the chrono library as a template.
    
    Possible specializations:
    std::chrono::nanoseconds
    std::chrono::microseconds
    std::chrono::milliseconds

    All other specifications don't make sense
*/
template <class T>
std::string GetCurrentDayTimeWithSecondFraction()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::high_resolution_clock::now();
    time_t cnow = std::chrono::system_clock::to_time_t(now);
    tm* ltm = localtime(&cnow);
    std::string currentTime;

    if (ltm->tm_hour < 10) currentTime += "0";
    currentTime += std::to_string(ltm->tm_hour);
    currentTime += ".";
    if (ltm->tm_min < 10) currentTime += "0";
    currentTime += std::to_string(ltm->tm_min);
    currentTime += ".";
    if (ltm->tm_sec < 10) currentTime += "0";
    currentTime += std::to_string(ltm->tm_sec);

    auto currentTimeSec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    auto currentTimeT = std::chrono::duration_cast<T>(now.time_since_epoch()).count();
    std::string stringTimeT = std::to_string(currentTimeT);

    int len = currentTimeT / currentTimeSec;
    switch (len)
    {
    // Milliseconds
    case 1000:
        currentTime = currentTime + "." + stringTimeT.substr(stringTimeT.length() - 3);
        break;
    // Microseconds
    case 1000000:
        currentTime = currentTime + "." + stringTimeT.substr(stringTimeT.length() - 6);
        break;
    // Nanoseconds
    case 1000000000:
        currentTime = currentTime + "." + stringTimeT.substr(stringTimeT.length() - 9);
        break;
    }
    
    return currentTime;
}

/** \brief Return current local time in ctime format
    \return Return current local day time in string with format: "week_day_name month_name day_in_month local_time year" 
    where day_week_name only 3 first char, first char is Capital like Tue or Sat,
    month_name only 3 first char, first char is Capital like May or Mar,
    day_in_month in format: dd like 01 or 12,
    local time in format: hh.mm.ss,
    year in format: yyyy like 2023
*/
std::string GetLocalTime()
{
    time_t now = time(0);
    std::string res(ctime(&now));
    res.pop_back();
    return res;
}

/** \brief Return current UTC time in ctime format
    \return Return current UTC day time in string with format: "week_day_name month_name day_in_month local_time year" 
    where day_week_name only 3 first char, first char is Capital like Tue or Sat,
    month_name only 3 first char, first char is Capital like May or Mar,
    day_in_month in format: dd like 01 or 12,
    local time in format: hh.mm.ss,
    year in format: yyyy like 2023
*/
std::string GetUTCTime()
{
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    char *dt = asctime(gmtm);
    return std::string(dt);
}

int main()
{    
    std::cout << "Nanoseconds: " << GetCurrentSecondFraction<std::chrono::nanoseconds>() << std::endl;
    std::cout << "Microseconds: " << GetCurrentSecondFraction<std::chrono::microseconds>() << std::endl;
    std::cout << "Milliseconds: " << GetCurrentSecondFraction<std::chrono::milliseconds>() << std::endl;
    std::cout << "Seconds: " << GetCurrentSecond() << std::endl;
    std::cout << "Minutes: " << GetCurrentMinute() << std::endl;
    std::cout << "Hours: " << GetCurrentHour() << std::endl;
    std::cout << "Month days: " << GetCurrentMonthDay() << std::endl;
    std::cout << "Year days: " << GetCurrentYearDay() << std::endl;
    std::cout << "Month: " << GetCurrentMonth() << std::endl;
    std::cout << "Year: " << GetCurrentYear() << std::endl;

    std::cout << std::endl;
    
    std::cout << "GetCurrentDate in normal format" << std::endl;
    std::cout << GetCurrentDate() << std::endl;

    std::cout << std::endl;

    std::cout << "GetCurrentDate in american format" << std::endl;
    std::cout << GetCurrentDate(true) << std::endl;

    std::cout << std::endl;

    // Add current time with milliseconds, microseconds, nanoseconds.
    std::cout << "GetCurrentDayTime" << std::endl;
    std::cout << GetCurrentDayTime() << std::endl;

    std::cout << std::endl;

    std::cout << "GetCurrentDayTime with milliseconds" << std::endl;
    std::cout << GetCurrentDayTimeWithSecondFraction<std::chrono::milliseconds>() << std::endl;

    std::cout << std::endl;

    std::cout << "GetCurrentDayTime with microseconds" << std::endl;
    std::cout << GetCurrentDayTimeWithSecondFraction<std::chrono::microseconds>() << std::endl;

    std::cout << std::endl;

    std::cout << "GetCurrentDayTime with nanoseconds" << std::endl;
    std::cout << GetCurrentDayTimeWithSecondFraction<std::chrono::nanoseconds>() << std::endl;

    std::cout << std::endl;

    std::cout << "GetLocalTime" << std::endl;
    std::cout << GetLocalTime() << std::endl;

    std::cout << std::endl;

    std::cout << "GetUTCTime" << std::endl;
    std::cout << GetUTCTime() << std::endl;
}
