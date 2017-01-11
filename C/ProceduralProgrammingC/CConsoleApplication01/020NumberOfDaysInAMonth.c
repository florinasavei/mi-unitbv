//determinig the number of days in a month
//using a switch statement

#include <stdio.h>

void main(){
	int days, month, year;
	printf("year: ");
	scanf_s("%d", &year);
	printf("month (1-12): ");
	scanf("%d", &month);
	switch (month){
	case 2:if (((year % 4 == 0) && (year % 100 != 0)) || (year%400 == 0))
				days = 29;
		   else days = 28;
		   break;
	case 4:case 6:case 9:case 11: days = 30;
		break;
	default: days = 31;
		break;
	}
	printf("\nmonth %d has %d days \n", month, days);
}