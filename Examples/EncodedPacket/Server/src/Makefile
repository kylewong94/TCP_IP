proj=GPSDataServer

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): TestCase.o GPSDataServer.o Server.o
	$(cxx) $(cflags) $(obj_path)/TestCase.o $(obj_path)/GPSDataServer.o $(obj_path)/Server.o -o $(bin_path)/$(proj)

TestCase.o: TestCase.cpp GPSDataServer.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

GPSDataServer.o: GPSDataServer.h Server.o
	$(cxx) $(cflags) -c GPSDataServer.cpp -o $(obj_path)/GPSDataServer.o

Server.o: Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
