all:
	mkdir -p build

	g++ -c -Wall -Werror -fPIC -std=c++11 -I./include -pthread -L/usr/local/lib -I/usr/local -lzmq \
	src/timer.cpp \
	src/component.cpp \
	src/operation_types.cpp

	g++ -shared -o build/libzcm.so timer.o component.o operation_types.o
	rm timer.o component.o operation_types.o
clean:
	rm build/libzcm.so
	rm -rf build
