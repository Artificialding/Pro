#include "lotcontrol.h"
#include "lotview.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main_menu_control(void)
{
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		main_menu();
		printf("intput your choose:");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("error\n");
			return;
		}
		switch(choose)
		{
			case 1:
				//
				break;
			case 2:
				////
				break;
			case 0:
				printf("tuichu\n");
				return;
			default:
				printf("error\n");
				break;
		}
	}


}
