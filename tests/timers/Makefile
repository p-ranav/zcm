all:
	g++ -o timers main.cpp -std=c++11 -I../../include -pthread -L/usr/local/lib -I/usr/local -lzmq -Wl,--no-as-needed
clean:
	$(RM) *.o *~ timers
