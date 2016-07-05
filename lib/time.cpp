tm* get_tm(int year, int month, int day, int hour = 0, int min = 0, int sec = 0) {
    tm *date = new tm();
    date->tm_year = year - 1900;
    date->tm_mon = month - 1;
    date->tm_mday = day;
    date->tm_hour = hour;
    date->tm_min = min;
    date->tm_sec = sec;
    mktime(date);
    return date;
}

// Returns the Unix timestamp for the given date interpreted as local time
int get_timestamp(int year, int month, int day, int hour = 0, int min = 0, int sec = 0) {
    tm *date = get_tm(year, month, day, hour, min, sec);
    return mktime(date);
}

// Get day of the week of given date
int day_of_week(int year, int month, int day) {
    tm *date = get_tm(year, month, day);
    return date->tm_wday;
}
