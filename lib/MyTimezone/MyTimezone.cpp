
#include "MyTimezone.h"
#include "Arduino.h"


//---------------- Create a Timezone object from the given time change rules ----------------//

Timezone::Timezone(TimeChangeRule dstStart, TimeChangeRule stdStart)
    : m_dst(dstStart), m_std(stdStart)
{
        initTimeChanges();
}

//------------------ Create a Timezone object for a zone that does not observe DST -----------//             

Timezone::Timezone(TimeChangeRule stdTime)
    : m_dst(stdTime), m_std(stdTime)
{
        initTimeChanges();
}


//-------------------- Convert UTC time to local, STD or DST --------------------------------//

time_t Timezone::toLocal(time_t utc)
{
    // recalculate the time change points if needed
    if (year(utc) != year(m_dstUTC)) calcTimeChanges(year(utc));

    if (utcIsDST(utc))
        return utc + m_dst.offset * SECS_PER_MIN;
    else
        return utc + m_std.offset * SECS_PER_MIN;
}

//------------------------ create a return pointer to TCR to do conversion --------------------//

time_t Timezone::toLocal(time_t utc, TimeChangeRule **tcr)
{
    // recalculate the time change points if needed
    if (year(utc) != year(m_dstUTC)) calcTimeChanges(year(utc));

    if (utcIsDST(utc)) {
        *tcr = &m_dst;
        return utc + m_dst.offset * SECS_PER_MIN;
    }
    else {
        *tcr = &m_std;
        return utc + m_std.offset * SECS_PER_MIN;
    }
}

//---------------------------- convert local time to UTC -----------------------------------------//

 
time_t Timezone::toUTC(time_t local)
{
    // recalculate the time change points if needed
    if (year(local) != year(m_dstLoc)) calcTimeChanges(year(local));

    if (locIsDST(local))
        return local - m_dst.offset * SECS_PER_MIN;
    else
        return local - m_std.offset * SECS_PER_MIN;
}

//------------------- check STD or DST within given UTC value -------------------------------------//

bool Timezone::utcIsDST(time_t utc)
{
    // recalculate the time change points if needed
    if (year(utc) != year(m_dstUTC)) calcTimeChanges(year(utc));

    if (m_stdUTC == m_dstUTC)       // daylight time not observed in this tz
        return false;
    else if (m_stdUTC > m_dstUTC)   // northern hemisphere
        return (utc >= m_dstUTC && utc < m_stdUTC);
    else                            // southern hemisphere
        return !(utc >= m_stdUTC && utc < m_dstUTC);
}

//---------------------- check STD or DST within Local time value ---------------------------------//

bool Timezone::locIsDST(time_t local)
{
    // recalculate the time change points if needed
    if (year(local) != year(m_dstLoc)) calcTimeChanges(year(local));

    if (m_stdUTC == m_dstUTC)       // daylight time not observed in this tz
        return false;
    else if (m_stdLoc > m_dstLoc)   // northern hemisphere
        return (local >= m_dstLoc && local < m_stdLoc);
    else                            // southern hemisphere
        return !(local >= m_stdLoc && local < m_dstLoc);
}

//--------------- calulation of the DST & STD year, for local and UTC values -----------------------//

void Timezone::calcTimeChanges(int yr)
{
    m_dstLoc = toTime_t(m_dst, yr);
    m_stdLoc = toTime_t(m_std, yr);
    m_dstUTC = m_dstLoc - m_std.offset * SECS_PER_MIN;
    m_stdUTC = m_stdLoc - m_dst.offset * SECS_PER_MIN;
}

//--------------- Initialize the DST and standard time change conversions --------------------------//

void Timezone::initTimeChanges()
{
    m_dstLoc = 0;
    m_stdLoc = 0;
    m_dstUTC = 0;
    m_stdUTC = 0;
}


//------------------------- convert timechange return to time_t value -------------------------------//

time_t Timezone::toTime_t(TimeChangeRule r, int yr)
{
    uint8_t m = r.month;     // temp copies of r.month and r.week
    uint8_t w = r.week;
    if (w == 0)              // is this a "Last week" rule?
    {
        if (++m > 12)        // yes, for "Last", go to the next month
        {
            m = 1;
            ++yr;
        }
        w = 1;               // and treat as first week of next month, subtract 7 days later
    }

    // calculate first day of the month, or for "Last" rules, first day of the next month
    tmElements_t tm;
    tm.Hour = r.hour;
    tm.Minute = 0;
    tm.Second = 0;
    tm.Day = 1;
    tm.Month = m;
    tm.Year = yr - 1970;
    time_t t = makeTime(tm);

    // add offset from the first of the month to r.dow, and offset for the given week
    t += ( (r.dow - weekday(t) + 7) % 7 + (w - 1) * 7 ) * SECS_PER_DAY;
    // back up a week if this is a "Last" rule
    if (r.week == 0) t -= 7 * SECS_PER_DAY;
    return t;
}
