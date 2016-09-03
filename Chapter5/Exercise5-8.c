/** There is no error checking in day_of_year or month_day. Remedy this defect. */

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

static const char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
static const int maxmonth = 12;
static const int daytotal[2] = {365, 366};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);
int mygetline(char * s, int n);


int main(void) {
	printf("There is no error checking in day_of_year or month_day. Remedy this defect.\n");

	int month, day, year, doy, yearday;
	char mystring[MAXLEN + 1];
	printf("Please enter month as integer: ");
	mygetline(mystring, MAXLEN);
	month = atoi(mystring);
	printf("Please enter day as integer: ");
	mygetline(mystring, MAXLEN);
	day = atoi(mystring);
	printf("Please enter year as integer: ");
	mygetline(mystring, MAXLEN);
	year = atoi(mystring);
	printf("Please enter yearday as integer: ");
	mygetline(mystring, MAXLEN);
	yearday = atoi(mystring);

	if ((doy = day_of_year(year, month, day)) != -1) {
		printf("%d/%d/%d (MM/DD/YYYY) is the %d day of the year.\n", month, day, year, doy);
	} else {
		printf("%d/%d/%d (MM/DD/YYYY) is not a valid day of year.\n", month, day, year);
	}

	if (month_day(year, yearday, &month, &day) != -1) {
		printf("The %d day of %d is %d/%d (MM/DD).\n", yearday, year, month, day);
	} else {
		printf("The %d day of %d is not a valid day of year.\n", yearday, year);
	}
	return EXIT_SUCCESS;
}


/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	if (month < 1 || month > maxmonth || daytab[leap][month] < day) {
		return -1;
	}

	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;
	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	if (yearday < 1 || yearday > daytotal[leap]) {
		return -1;
	}
	
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
	return 0;
}

int mygetline(char * s, int n) {
	char c;
	int i = 0;
	while (i < n && (c = getchar()) != '\n' && c != EOF) {
		*s++ = c;
		i++;
	}
	if (c == '\n') {
		*s++ = '\n';
		i++;
	}
	*s = '\0';
	return i;
}