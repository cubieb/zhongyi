CROSS := mipsel-linux-
CC :=$(CROSS)gcc 

test: scan.o i_utils.o
	$(CC) scan.c i_utils.c -o test 

clean:
	rm *.o test

