#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "hash.h"

extern double dclock(void);

int main(int argc, char **argv)
{
	int imax, jmax;
	char **buf;
	bool found;
	int hashsize;
	int i;
	int val;
	double t0, time;

	if (argc != 4) {
		printf("usage: %s <numbur of buffers> <size of buffers> <hash table size>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	imax = atoi(argv[1]);
	jmax = atoi(argv[2]);
	hashsize = atoi(argv[3]);
	buf = (char**)malloc(sizeof(*buf)*imax);
	for (i=0; i<imax; i++) {
		buf[i] = (char*)malloc(sizeof(**buf)*jmax);
		memset(buf[i], '\0', sizeof(*(buf[i])));
	}
       	
	hashtable_t *hp = gen_hashtable(hashsize);
	printf("generate random number and add them to hashtable...\n");
	for(i=0; i<imax; i++) {
		sprintf(buf[i], "%d", rand());
		add_hashtable(hp, buf[i], i);
	}
	printf("try to find the values from the hashtable...\n");
	t0 = dclock();
	for(i=0; i<imax; i++) {
		val = getval_hashtable(hp, buf[i], &found);
/*		printf("%d\n", val); */
		if (!found) {
			printf("key: %s was not found.\n", buf[i]);
			exit(EXIT_FAILURE);
		}
	}
	time = dclock() - t0;
	printf("time to search the key[s]: %lf\n", time);

	clear_hashtable(hp);
	for (i=0; i<imax; i++)
		free(buf[i]);
	free(buf);
	return 0;
}
