Integration Test
================

Test Dependency
----------------

* Install boost

```bash
$ sudo apt-get install libboost-all-dev
```

Running this Test
-----------------

```bash
$ make
$ cp configuration.json build/.
$ cd build
$ export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
$ ./actor
```