FIND_PACKAGE(Protobuf REQUIRED)

INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} proto/event.proto)

ADD_EXECUTABLE(test_cppzmq_proto_server server/main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
ADD_EXECUTABLE(test_cppzmq_proto_client client/main.cpp ${PROTO_SRCS} ${PROTO_HDRS})

TARGET_INCLUDE_DIRECTORIES(test_cppzmq_proto_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)
TARGET_INCLUDE_DIRECTORIES(test_cppzmq_proto_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

TARGET_LINK_LIBRARIES(test_cppzmq_proto_server PRIVATE spdlog::spdlog_header_only cppzmq::cppzmq protobuf::protobuf)
TARGET_LINK_LIBRARIES(test_cppzmq_proto_client PRIVATE spdlog::spdlog_header_only cppzmq::cppzmq protobuf::protobuf)
