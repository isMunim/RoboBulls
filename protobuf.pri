
#
# Qt qmake integration with Google Protocol Buffers compiler protoc
#
# To compile protocol buffers with qt qmake, specify PROTOS variable and
# include this file
#
# Example:
# LIBS += /usr/local/lib/libprotobuf.so
# PROTOS = a.proto b.proto
# include(protobuf.pri)
#
#





message("Generating protocol buffer classes from .proto files.")
 

win32:PROTOC_CMD = $$PWD/libs/windows/x64/tools/protoc
unix:!macx: PROTOC_CMD = protoc

protobuf_decl.name = protobuf headers
protobuf_decl.input = PROTOS
protobuf_decl.output = ${QMAKE_FILE_BASE}.pb.h
protobuf_decl.commands = $$PROTOC_CMD --cpp_out=. --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_decl
 
protobuf_impl.name = protobuf sources
protobuf_impl.input = PROTOS
protobuf_impl.output = ${QMAKE_FILE_BASE}.pb.cc
protobuf_impl.depends = ${QMAKE_FILE_BASE}.pb.h
protobuf_impl.commands = $$escape_expand(\n)
protobuf_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_impl
