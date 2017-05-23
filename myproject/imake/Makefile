TARGET := get_from_client.cgi

CROSS := /opt/buildroot-gcc463/usr/bin/mipsel-linux-
CC :=$(CROSS)gcc 


all: my.c mod_method.c utils.c
	$(CC) $^ -o $(TARGET)

clean:
	rm *.o  $(TARGET)

