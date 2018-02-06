batch.o: batch.c
	gcc batch.c -Wall -g -o batch
	./batch /mnt/dd/Dropbox/github/graph-temp/sample/ 2018-02-07 2018-02-13

exec:
	./batch /mnt/dd/Dropbox/github/graph-temp/sample/ 2018-02-07 2018-02-13
