# Build ZCM as a shared library
LIBFLAG=-shared

# Paths to ZMQ library
LIBZMQ_DIR=/usr/local
LIBZMQ_LIBDIR=$(LIBZMQ_DIR)/lib
LIBZMQ_INCDIR=$(LIBZMQ_DIR)/include

# Install Location for ZCM
LIBZCM_DIR=/usr/local
LIBZCM_LIBDIR=/usr/local/lib
LIBZCM_INCDIR=/usr/local/include/zcm

all:
	mkdir -p build
	g++ -c -Wall -Werror -fPIC -std=c++11 -I./include -pthread -L$(LIBZMQ_LIBDIR) -I$(LIBZMQ_INCDIR) -lzmq -ldl \
	src/timer.cpp \
	src/component.cpp \
	src/operation_types.cpp \
	src/operation_queue.cpp \
	src/publisher.cpp \
	src/subscriber.cpp \
	src/client.cpp \
	src/server.cpp \
	src/json.cpp \
	src/actor.cpp

	g++ -shared -o build/libzcm.so timer.o component.o operation_types.o operation_queue.o publisher.o subscriber.o client.o server.o json.o actor.o -ldl
	rm timer.o component.o operation_types.o operation_queue.o publisher.o subscriber.o client.o server.o json.o actor.o
install:
	mkdir -p $(LIBZCM_LIBDIR)
	cp build/libzcm.so $(LIBZCM_LIBDIR)
	mkdir -p $(LIBZCM_INCDIR)
	cp include/*.hpp $(LIBZCM_INCDIR)/.
clean:
	rm build/libzcm.so
	rm -rf build

