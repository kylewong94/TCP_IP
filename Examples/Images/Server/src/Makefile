proj=ImageServer

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): ImageServerTest.o ImageServer.o Server.o
	$(cxx) $(cflags) $(obj_path)/ImageServerTest.o $(obj_path)/ImageServer.o $(obj_path)/Server.o -o $(bin_path)/$(proj)

ImageServerTest.o: ImageServerTest.cpp ImageServer.o
	$(cxx) $(cflags) -c ImageServerTest.cpp -o $(obj_path)/ImageServerTest.o

ImageServer.o: ImageServer.h Server.o
	$(cxx) $(cflags) -c ImageServer.cpp -o $(obj_path)/ImageServer.o

Server.o: Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
