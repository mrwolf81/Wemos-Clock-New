#ifndef MYTIMEZONE_H_INCLUDED
#define MYTIMEZONE_H_INCLUDED
#if ARDUINO >= 100
#include "Arduino.h" 
#else
#include "WProgram.h" 
#endif
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time

//---------------constants for TimeChangeRules---------------------------------------------//

enum week_t {Last, First, Second, Third, Fourth}; 
enum dow_t {Sun=1, Mon, Tue, Wed, Thu, Fri, Sat};
enum month_t {Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

//-------------------- structure for DST start and STD start rules ------------------------//


struct TimeChangeRule
{
    char abbrev[6];    // five chars max
    uint8_t week;      // First, Second, Third, Fourth, or Last week of the month
    uint8_t dow;       // day of week (Monday to Sunday)
    uint8_t month;     // Month numbers
    uint8_t hour;      // 0-23 - hours in 24 hour format 0 = midnight, 12 = noon
    int offset;        // offset UTC in minutes
};
        
class Timezone
{
    public:
        Timezone(TimeChangeRule dstStart, TimeChangeRule stdStart);
        Timezone(TimeChangeRule stdTime);
        time_t toLocal(time_t utc);
        time_t toLocal(time_t utc, TimeChangeRule **tcr);
        time_t toUTC(time_t local);
        bool utcIsDST(time_t utc);
        bool locIsDST(time_t local);

    private:
        void calcTimeChanges(int yr);
        void initTimeChanges();
        time_t toTime_t(TimeChangeRule r, int yr);
        TimeChangeRule m_dst;   // rule for start of dst time
        TimeChangeRule m_std;   // rule for start of standard time
        time_t m_dstUTC;        // dst start for current year in UTC
        time_t m_stdUTC;        // std start for given year in UTC
        time_t m_dstLoc;        // dst start for given local time
        time_t m_stdLoc;        // std start for given local time
};
#endif
