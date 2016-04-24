ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

all:
	g++ -o client_server main.cpp test_message.pb.cc -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lprotobuf
message:
	protoc --cpp_out=. test_message.proto
clean:
	$(RM) *.o *~ client_server
