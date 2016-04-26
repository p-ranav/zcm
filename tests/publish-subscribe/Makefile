ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

TEST_PROTO_DIR=proto
TEST_INCLUDE_DIR=include
TEST_SOURCE_DIR=src
TEST_BUILD_DIR=build
TEST_CONFIG_DIR=config

all:
	mkdir -p $(TEST_BUILD_DIR)
	cp -r $(TEST_CONFIG_DIR)/* $(TEST_BUILD_DIR)/.	
	cd $(TEST_PROTO_DIR) && protoc --cpp_out=. test_message.proto && cd ..

	g++ -fPIC -shared $(TEST_SOURCE_DIR)/publisher_component.cpp $(TEST_PROTO_DIR)/test_message.pb.cc -o $(TEST_BUILD_DIR)/publisher_component.so -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(TEST_PROTO_DIR) -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -Wl,-Bstatic -lprotobuf -Wl,-Bdynamic

	g++ -fPIC -shared $(TEST_SOURCE_DIR)/subscriber_component.cpp $(TEST_PROTO_DIR)/test_message.pb.cc -o $(TEST_BUILD_DIR)/subscriber_component.so -I$(TEST_INCLUDE_DIR) -std=c++11 -pthread -I$(TEST_PROTO_DIR) -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -Wl,-Bstatic -lprotobuf -Wl,-Bdynamic

	g++ $(TEST_SOURCE_DIR)/main.cpp -o $(TEST_BUILD_DIR)/actor -I$(TEST_INCLUDE_DIR) -I$(TEST_PROTO_DIR) -std=c++11 -ldl -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq

clean:
	rm -rf $(TEST_BUILD_DIR)
