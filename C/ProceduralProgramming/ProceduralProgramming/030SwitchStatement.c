#include <stdio.h>
#include <conio.h>

void main(){
	int a, b;
	char opt;

	do{
		system("cls");
		pritf("\n\t A=Add \n\t S=Substract \n\t M=Multiply");
		printf("\n\t D=Devide \n\t \n\t X= Exit \n\n");
		printf("\t Option:");
		fflush(stdin);
		opt = getchar();
		if (opt == "x" || opt == "X") return;
		printf("\n\t Enter two integers");
		scanf_s("%d%d",&a,&b);
		printf("\n\t Result=");
		switch (opt){
				case 'a':case 'A':printf("%d", a + b); break;
				case 's':case 'S':printf("%d", a - b); break;
				case 'm':case 'M':printf("%d", a * b); break;
				case 'd':case 'D':printf("%d", a / b); break;
		}
		fflush(stdin);
		getchar();
	} while(1);

}