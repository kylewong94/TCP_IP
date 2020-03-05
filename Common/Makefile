obj_path=./obj
lib_path=./lib

cxx=g++
cflags= -Wall

objs: Server.o \
      Client.o 

all: $(lib_path)/libnetcomm.a

clean: 
	rm $(lib_path)/*.a
	rm $(obj_path)/*.o

$(lib_path)/libnetcomm.a: $(objs)
	ar rcs $(lib_path)/libnetcomm.a $(objs) 

$(obj_path)/Client.o: Client.cpp Client.h
	$(cxx) $(cflags) -c Client.cpp -o $(obj_path)/Client.o

$(obj_path)Server.o: Server.cpp Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

