#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	//set up the user arguments
	int wait_time = 1;
	if (argc > 1) {
		printf("%s\n",argv[1]);
		fsync(0);
	}
	if (argc > 2) //display information out to the user
		wait_time = atoi(argv[2]);



	struct termios old_tio, new_tio;
	unsigned char c;

	/* get the terminal settings for stdin */
	tcgetattr(STDIN_FILENO,&old_tio);

	/* we want to keep the old setting to restore them a the end */
	new_tio=old_tio;

	/* disable canonical mode (buffered i/o) and local echo */
	new_tio.c_lflag &=(~ICANON );//& ~ECHO);

	/* set the new settings immediately */
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

	struct pollfd poll_stdin;
	poll_stdin.fd = STDIN_FILENO;	
	poll_stdin.events = POLLIN;
	
	poll(&poll_stdin,1,wait_time*1000);



	/* restore the former settings */
	tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
	
	//make the program nice and clean at the end :D
	printf("\n");
	
	if ((poll_stdin.revents & POLLIN))
		return 0;
	return 1;
}
