/*
 * Mini_project.c
 *
 *  Created on: Sep 7, 2021
 *      Author: Hana
 */
#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1

void Vehicle_engine_state(int *ptr);
void Sensors_set_menu(void);
void Traffic_light(void);
void Room_temperature(void);
void Engine_temperature(void);
void display(int state);

int state ; //the state of the vehicle engine
int SPEED ;
int room_temperature = 25;
int AC ;
int engine_temperature = 80 ;
int TemperatureController ;


void Vehicle_engine_state(int *ptr)
{

	char check;
	printf("Would you like to : \n");
	printf("a. Turn on the vehicle engine \n");
	printf("b. Turn off the vehicle engine \n");
	printf("c. Quit the system \n");
	scanf(" %c" , &check);
	switch(check)
	{
	case 'a' : *ptr = 1;
	break;
	case 'b' : *ptr = 2;
	printf("the vehicle engine is turned off \n");
	break;
	case 'c' : *ptr = 0;
	break;
	default :  *ptr = -1; //wrong input
	}

}
void Sensors_set_menu(void)
{

	char check;
	printf("a. Turn off the engine \n");
	printf("b. Set the traffic light color \n");
	printf("c. Set the room temperature \n");
#if(WITH_ENGINE_TEMP_CONTROLLER)
	printf("d. Set the engine temperature \n");
#endif
	do
	{
		scanf(" %c" , &check);
	} while( !(check == 'a' || check == 'b' || check == 'c' || check == 'd') );


	switch(check)
	{
	case 'a' : Vehicle_engine_state(&state);
	break;
	case 'b' : Traffic_light();
	break;
	case 'c' : Room_temperature();
	break;
	case 'd' :
#if(WITH_ENGINE_TEMP_CONTROLLER)
		Engine_temperature();
#endif
		if(!WITH_ENGINE_TEMP_CONTROLLER)
		{

			Sensors_set_menu();
		}

		break;
	}
}

void Traffic_light(void)
{
	char color;
	scanf(" %c" , &color);
	switch(color)
	{
	case 'G' : SPEED = 100;
	break;
	case 'O' : SPEED = 30;
	break;
	case 'R' : SPEED = 0;
	break;

	}
	if (SPEED == 30)
	{
		if(!AC) AC =1;
		room_temperature = room_temperature*5/4 + 1;

#if(WITH_ENGINE_TEMP_CONTROLLER)

		if(!TemperatureController) TemperatureController =1;
		engine_temperature = engine_temperature*5/4 + 1;
#endif

	}

	display(state);
}

void Room_temperature(void)
{

	scanf(" %d" , &room_temperature);
	if(room_temperature < 10 || room_temperature >30)
	{
		AC=1;//AC On
		room_temperature = 20;
	}
	else
	{
		AC=0; //AC Off
	}

	if(SPEED==30)
	{
		if(!AC) AC =1;
		room_temperature = room_temperature*5/4 + 1;
	}
	display(state);

}

void Engine_temperature(void)
{

	scanf(" %d" , &engine_temperature);
	if(engine_temperature < 100 || engine_temperature > 150)
	{
		TemperatureController = 1; // Engine temperature controller On
		engine_temperature = 125;

	}
	else
	{
		TemperatureController = 0; // Engine temperature controller Off
	}
	if(SPEED == 30)
	{

#if(WITH_ENGINE_TEMP_CONTROLLER)

		if(!TemperatureController) TemperatureController =1;
		engine_temperature = engine_temperature*5/4 + 1;
#endif
	}
	display(state);
}

void display(int state)
{
	if(state == 1)
		printf("The vehicle engine is ON \n");
	else if (state == 2)
	{
		printf("The vehicle engine is OFF \n");
		return;
	}
	if (AC)
		printf("AC is ON \n");
	else
		printf("AC is OFF \n");
	printf("The vehicle speed = %d km/hr \n", SPEED);
	printf("Room temperature = %d ° \n" , room_temperature);

#if(WITH_ENGINE_TEMP_CONTROLLER)


	if (TemperatureController)
		printf("Engine temperature controller is ON \n");
	else
		printf("Engine temperature controller is OFF \n");
	printf("Engine temperature = %d ° \n", engine_temperature);

#endif
	Sensors_set_menu();
}
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	Vehicle_engine_state(&state);

	switch(state)
	{
	case 0 : return 0;
	case 1 : printf("The vehicle engine is turned on \n");
	Sensors_set_menu();
	break;
	case 2 : printf("The vehicle engine is turned off \n");
	break;
	default: printf("Wrong input \n");
	main();
	break;
	}

	if(state == 1)
	{
		printf("The vehicle engine is turned on \n");
		Sensors_set_menu();
	}

	if(state == 0) return 0; //in case the user chose to quit the system after turning it on


	main();
}

