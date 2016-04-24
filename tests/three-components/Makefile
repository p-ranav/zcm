all:
	g++ -o three_components main.cpp -std=c++11 -I../../include -pthread -L/usr/local/lib -I/usr/local -lzmq -lprotobuf -lboost_filesystem
clean:
	$(RM) *.o *~ three_components
