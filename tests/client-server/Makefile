all:
	make client && make server

clean:
	$(RM) *.o *~ client server

client:
	g++ client.cpp -o client -g -Wall -std=c++11 -L/usr/local/lib -I/usr/local -lzmq

server:
	g++ server.cpp -o server -g -Wall -std=c++11 -L/usr/local/lib -I/usr/local -lzmq
