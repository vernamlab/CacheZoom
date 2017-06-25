HEADERS = ../kernel/cachezoom_kernel.h

default: cachezoom

cachezoom_client.o: cachezoom_client.c $(HEADERS)
	gcc -c cachezoom_client.c -o cachezoom_client.o -w

cachezoom: cachezoom_client.o
	gcc cachezoom_client.o -o cachezoom

clean:
	-rm -f cachezoom_client.o
	-rm -f cachezoom