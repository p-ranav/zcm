all:
	g++ -c -Wall -Werror -fPIC -std=c++11 -I../include -pthread -L/usr/local/lib -I/usr/local -lzmq timer.cpp
	g++ -shared -o libzcm.so timer.o
	rm timer.o
