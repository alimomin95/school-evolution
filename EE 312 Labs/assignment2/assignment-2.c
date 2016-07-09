/* 
Momin, Ali Ziyaan 
AZM259,
15975
EE312-Assignment 2
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
	int operation = 1;
	
	while(operation){
		
		int selection;
		
		//printf("Menu:\n1. Convert a given Austin time to Irish time\n2. Convert a given Irish time to Austin time\n3. Convert a given USD value to EUR\n4. Convert a given EUR value to USD\n5. Convert a given Fahrenheit temperature to Celsius\n6. Convert a given Celsius temperature to Fahrenheit\n7. Convert a given weight in kg to pounds, ounces\n8. Convert a given weight in pounds, ounces to kg\n9. Convert a given distance in km to miles\n10. Convert a given distance in miles to km\n11. Stop doing conversions and quit the program\n");
		printf("Enter a number from the menu (1-11) to select a specific conversion to perform or to quit:");
		scanf("%d", &selection);

		if(selection == 1){
			
			int austinHour = 0;
			int austinMin = 0;
			
			printf("Enter Austin time to be converted, expressed in hours and minutes:");
			scanf("%d %d", &austinHour, &austinMin);

			int irishHour = (austinHour + 6) % 24;

			if(austinHour >= 18){
				printf("The time in Ireland equivalent to %.2d %.2d in Austin is %.2d %.2d of the next day\n", austinHour, austinMin, irishHour, austinMin);
			}
			else{
				printf("The time in Ireland equivalent to %.2d %.2d in Austin is %.2d %.2d of the same day\n", austinHour, austinMin, irishHour, austinMin);
			}

		}

		if(selection ==2){
			
			int irishHour = 0;
			int irishMin = 0;
			
			printf("Enter Irish time to be converted, expressed in hours and minutes:");
			scanf("%d %d", &irishHour, &irishMin);

			int austinHour = (irishHour + 18) % 24;

			if(irishHour >= 6){
				printf("The time in Austin equivalent to %.2d %.2d in Ireland is %.2d %.2d of the same day\n", irishHour, irishMin, austinHour, irishMin);
			}
			else{
				printf("The time in Austin equivalent to %.2d %.2d in Ireland is %.2d %.2d of the previous day\n", irishHour, irishMin, austinHour, irishMin);
			}

		}

		if(selection == 3){

			double dol = 0;
			double cent = 0;

			printf("Enter USD value:");
			
			scanf("%lf %lf", &dol, &cent);

			double amt = dol + (cent/100);

			printf("EUR value is: %lf Euros\n", (amt * 0.74));

		}

		if(selection == 4){

			double eur = 0;
			int dol = 0;
			double cent = 0;

			printf("Enter EUR value:");
			scanf("%lf", &eur);

			cent = eur * 1.36;
			dol = eur * 1.36;

			cent = cent - dol;
			cent = cent * 100;

			printf("USD value is: $ %d %.0lf\n", dol, cent);

		}

		if(selection == 5){

			double f = 0;

			printf("Enter temperature in Fahrenheit:");
			scanf("%lf", &f);

			printf("Temperature in Celsius is: %lf\n", ((5*(f-32))/9));

		}

		if(selection == 6){

			double c = 0;

			printf("Enter temperature in Celsius:");
			scanf("%lf", &c);

			printf("Temperature in Fahrenheit is: %.0lf\n", (((9*c)/5)+32));

		}

		if(selection == 7){

			double kg = 0;

			printf("Enter weight in kg:");
			scanf("%lf", &kg);

			int oz = kg * 35.274;
			int lb = oz/16;

			printf("Weight in pounds and ounces is: %d lb %d oz\n", lb, oz % 16);

		}

		if(selection == 8){

			int lb = 0;
			int oz = 0;

			printf("Enter weight in pounds and ounces:");
			scanf("%d %d", &lb, &oz);

			double kg = ((lb * 16) + oz) / 35.274;

			printf("Weight in kg is: %lf kg\n", kg);

		}

		if(selection == 9){

			double km = 0;

			printf("Enter distance in km:");
			scanf("%lf", &km);

			double miles = km * 0.6213712;

			printf("Distance in miles is: %lf mi\n", miles);

		}

		if(selection == 10){

			double miles = 0;

			printf("Enter distance in miles:");
			scanf("%lf", &miles);

			double km = miles / 0.6213712;

			printf("Distance in km is: %lf km\n", km);
			
		}

		if(selection == 11){
			
			operation = 0;

		}

		if(selection >= 12 || selection <= 0){
		
			printf("Invalid input.\n");
		
		}

	}

	printf("Good Bye\n");

	return 0;

}
