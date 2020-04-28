proj=CommServer

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): TestCase.o NetCommServer.o Server.o
	$(cxx) $(cflags) $(obj_path)/TestCase.o $(obj_path)/NetCommServer.o $(obj_path)/Server.o -o $(bin_path)/$(proj)

TestCase.o: TestCase.cpp NetCommServer.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

NetCommServer.o: NetCommServer.h Server.o
	$(cxx) $(cflags) -c NetCommServer.cpp -o $(obj_path)/NetCommServer.o

Server.o: Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
