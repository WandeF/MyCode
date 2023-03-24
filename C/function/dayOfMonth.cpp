/*
    给定年份和月份计算当月天数 give me year and month to count days of month
*/
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