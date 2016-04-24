ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

all:
	g++ -o three_components main.cpp -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem
clean:
	$(RM) *.o *~ three_components
