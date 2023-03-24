/*
	给出生日期计算活了多少天
	Calculate the number of days lived for a date of birth
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int countDay(int birthyear, int birthmon, int birthday);//计算天数函数 The function to count days
int isLeapYear(int year); //isLeapYear
int dayOfMonth(int year, int month); //给定年份和月份计算当月天数 give me year and month to count days of month

int main()
{
	int birthyear, birthmon, birthday; // 出生年月日 birthday
	int days; //your days 

	printf("please input your birthday: \n");

	scanf("%d %d %d", &birthyear, &birthmon, &birthday);

	days = countDay(birthyear, birthmon, birthday);

	printf("your days till your birth are %d .\n", days);
	system("pause");
	return 0;
}
int countDay(int birthyear, int birthmon, int birthday)
{
	int toyear, tomon, today, yday, bday; // 用gmtime函数给出当前年月日   yday：从今年1月1日起过了多少天    bday：从出生年份1月1日起过了多少天
 	int countday = 0;
	int subday = 0; // yday + 出生年天数(365/366)-bday+1

	
	time_t timep;
	time(&timep);
	struct tm *p;
	p = gmtime(&timep);

	toyear = 1900+p->tm_year; //从1900到现在有多少年，计算年份需+1900
	tomon = p->tm_mon;
	today = p->tm_mday;
	yday = p->tm_yday;

	for (int i=birthyear+1; birthyear < i && i < toyear; i++) //中间年份的日期(完整年的天数之和)
	{
		
		countday += 365+isLeapYear(i);
	}

	for (int j = 1; j < birthmon; j++) // 出生年份1月1到出生月的天数之和(完整月的天数和) 
	{
		bday += dayOfMonth(birthyear, j);
	}

	bday += birthday; //从1月1到出生日的天数和

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