TARGET := test.cgi

CROSS := mipsel-linux-
CROSS :=
CC :=$(CROSS)gcc 


all: scan.c utils.c
	$(CC) $^ -o $(TARGET)

clean:
	rm *.o  $(TARGET)

