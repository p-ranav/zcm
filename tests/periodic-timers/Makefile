ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

all:
	g++ -o timers main.cpp -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq
clean:
	$(RM) *.o *~ timers
