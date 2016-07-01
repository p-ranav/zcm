ZeroMQ Component Model
======================

A lightweight component model using ZeroMQ

ZCM Dependencies
-----------------

* Install library dependencies

```bash
$ sudo apt-get install autoconf automake libtool curl
```

* Install libzmq

```bash
$ git clone https://github.com/zeromq/libzmq
$ cd libzmq
$ ./autogen.sh && ./configure && make -j 4
$ make check && sudo make install && sudo ldconfig
```

* Download and copy cppzmq headers

```bash
$ git clone https://github.com/zeromq/cppzmq
$ cd cppzmq
$ sudo cp *.hpp /usr/local/include/.
```

Install ZCM
------------

```bash
$ git clone https://github.com/pranav-srinivas-kumar/zcm
$ cd zcm
$ make
$ sudo make install
$ sudo ldconfig
```

Optional (Used in tests)
------------------------

* Install protobuf with -fPIC flag

```bash
$ git clone https://github.com/google/protobuf
$ cd protobuf
$ ./autogen.sh
$ ./configure --prefix=/usr
$ `# Open src/Makefile and add -fPIC to CXXFLAGS`
$ make
$ make check
$ sudo make install
$ sudo ldconfig
```

* Install boost

```bash
$ sudo apt-get install libboost-all-dev
```

