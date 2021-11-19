#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	int random_value, cookie, now;

	now = time(0);
	srand(now);
	random_value = rand();
	cookie = random_value % now;
	printf("%d", cookie);

}