#include <sys/ioctl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void hand(int sig) {
	printf("ksoksosos\n");
	ioctl(0,TIOCSTI, 0x04);
}

int main() {
	char tmp[1000];


	signal(SIGINT, hand);
	
	int m = read(0, tmp, 1000);

	tmp[m] = '\0';

	printf("%s\n", tmp);
}
