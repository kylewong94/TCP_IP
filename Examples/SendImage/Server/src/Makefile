proj=ImageServer

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): TestCase.o ImageServer.o Server.o
	$(cxx) $(cflags) $(obj_path)/TestCase.o $(obj_path)/ImageServer.o $(obj_path)/Server.o -o $(bin_path)/$(proj)

TestCase.o: TestCase.cpp ImageServer.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

ImageServer.o: ImageServer.h Server.o
	$(cxx) $(cflags) -c ImageServer.cpp -o $(obj_path)/ImageServer.o

Server.o: Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
