all:
	g++ -c -Wall -Werror -fPIC -std=c++11 -I../include -pthread -L/usr/local/lib -I/usr/local -lzmq timer.cpp component.cpp
	g++ -shared -o libzcm.so timer.o component.o
	rm timer.o component.o
clean:
	rm libzcm.so
