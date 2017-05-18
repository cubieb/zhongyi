CROSS := mipsel-linux-
CC :=$(CROSS)gcc 

test.cgi: scan.o utils.o
	$(CC) scan.c utils.c -o $@

clean:
	rm *.o test.cgi test

