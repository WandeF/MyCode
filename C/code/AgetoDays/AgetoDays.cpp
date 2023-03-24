#include <stdio.h>
#include <time.h>

int countDay(int birthyear, int birthmon, int birthday);
int isLeapYear(int year);
int dayOfMonth(int year, int month);

int main()
{
	int birthyear, birthmon, birthday;
	int days;

	printf("please input your birthday: \n");

	scanf("%d %d %d", &birthyear, &birthmon, &birthday);

	days = countDay(birthyear, birthmon, birthday);

	printf("your days till your birth are %d", days);
}
int countDay(int birthyear, int birthmon, int birthday)
{
	int toyear, tomon, today, yday, bday;
	int countday = 0;
	int subday = 0;

	
	time_t timep;
	time(&timep);
	struct tm *p;
	p = gmtime(&timep);

	toyear = 1900+p->tm_year;
	tomon = p->tm_mon;
	today = p->tm_mday;
	yday = p->tm_yday;

	for (int i=birthyear+1; birthyear < i && i < toyear; i++)
	{
		if (isLeapYear(i)== 1)
		{
			countday += 366;
		}
		else
		{
			countday += 365;
		}
	}

	for (int j = 1; j < birthmon; j++) {
		bday += dayOfMonth(birthyear, j);
	}

	bday += birthday;

	subday = 365 + isLeapYear(birthyear) - bday + yday+1;

	countday += subday;
	return countday;
}
int isLeapYear(int year)
{	
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return 1;
	else return 0;
}

int dayOfMonth(int year, int month)
{
	int day = 0;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		day = 31;
		break;
	case 2:
		day = 28 + isLeapYear(year);
		break;
	default:
		day = 30;
		break;
	}
	return day;
}