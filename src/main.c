#include <time.h>
#include <stdio.h>
#if defined(__WIN32)
	#include <windows.h> // Sleep
#elif defined(__unix__)
	#include <unistd.h> // usleep
#endif

const char *nums[10][8] = {
	{ "          ",
	  "  #####   ",
	  " #    ##  ",
	  " #   # #  ",
	  " #  #  #  ",
	  " # #   #  ",
	  " ##    #  ",
	  "  #####   "},
	{ "          ", "    #     ", "   ##     ", "    #     ", "    #     ", "    #     ", "    #     ", "  #####   "}, // 1
	{ "          ", "  #####   ", " #     #  ", "       #  ", "   ####   ", "  #       ", " #        ", " #######  "}, // 2
	{ "          ", "  #####   ", " #     #  ", "       #  ", "   ####   ", "       #  ", " #     #  ", "  #####   "}, // etc...
	{ "          ", "    ###   ", "   #  #   ", "  #   #   ", " #    #   ", " #######  ", "      #   ", "      #   "},
	{ "          ", " #######  ", " #     #  ", " #        ", "  #####   ", "       #  ", " #     #  ", "  #####   "},
	{ "          ", "  #####   ", " #     #  ", " #        ", "  #####   ", " #     #  ", " #     #  ", "  #####   "},
	{ "          ", " #######  ", " #     #  ", "      #   ", "     #    ", "    #     ", "   #      ", "  #       "},
	{ "          ", "  #####   ", " #     #  ", " #     #  ", "  #####   ", " #     #  ", " #     #  ", "  #####   "},
	{ "          ", "  #####   ", " #     #  ", " #     #  ", "  #####   ", "       #  ", "       #  ", "  #####   "},
};

int strtoi(char *str);
void DisplayTime(int hours, int minutes, int seconds);

unsigned int running = 1;

int main(int argc, char **argv)
{
	int utc = 0;
	if(argc > 1)
		utc = strtoi(argv[1]);
	unsigned int displayTime = time(NULL);
	
	while(running)
	{
		unsigned int currentTime = time(NULL);
		if(currentTime <= displayTime)
		{
			#if defined(__WIN32)
			Sleep(100);
			#elif defined(__unix__)
			usleep(100);
			#endif
			
			continue;
		}
		
		int seconds = currentTime%60;
		int minutes = (currentTime/60) % 60;
		int hours = ((currentTime/3600) % 24) + utc;
		DisplayTime(hours, minutes, seconds);
		displayTime = currentTime;
	}
	
	return 0;
}

int strtoi(char *str)
{
	int sign = 1;
	int result = 0;
	
	if(str[0] == '-')
	{
		sign = -1;
		str++;
	}
		
	for(char *c = str; *c != '\0' && *c >= '0' && *c <= '9'; ++c)
		result = result * 10 + *c - '0';
	
	return result * sign;
}

void printnum(int num, int i)
{
	if(num < 10)
		printf("%s", nums[0][i]);
	else
		printf("%s", nums[num/10][i]);
	printf("%s", nums[num-10*(num/10)][i]);

}

void DisplayTime(int hours, int minutes, int seconds)
{
#if defined(__WIN32)
	system("cls");
#elif defined(__unix__)
	system("clear");
#endif
	for(int i = 0; i < 8; ++i)
	{
		//Print hour
		printnum(hours, i);
		
		//Print double points
		if(i == 3 || i == 5)
			printf("# ");
		else
			printf("  ");

		printnum(minutes, i);

		if(i == 3 || i == 5)
			printf("#");
		else
			printf(" ");

		printnum(seconds, i);
		printf("\n");
	}
}
