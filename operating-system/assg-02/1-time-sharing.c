#include <stdio.h>
#include <sys/time.h>

int main(int argc,char *argv[]) {
	FILE *fp1 = fopen("1-utility/time.csv", "a");
	FILE *fp2 = fopen("1-utility/time.txt", "a");
	
	for(int i = 0; i < 10000; i++) {
		struct timeval now;
		gettimeofday(&now, NULL);
		printf("%s %lu\n", argv[1], now.tv_usec);
		fprintf(fp1, "%s %lu\n", argv[1], now.tv_usec);
		fprintf(fp2, "%s %lu\n", argv[1], now.tv_usec);
	}
}