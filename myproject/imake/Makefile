TARGET := my.cgi

#CROSS := mipsel-linux-
CROSS :=
CC :=$(CROSS)gcc 


all: my.c utils.c mod_method.c
	$(CC) $^ -o $(TARGET)

clean:
	rm *.o  $(TARGET)

