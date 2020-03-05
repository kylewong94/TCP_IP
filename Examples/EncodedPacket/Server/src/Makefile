proj=GPSDataServer

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): GPSDataServerTest.o GPSDataServer.o
	$(cxx) $(cflags) -o $(bin_path)/$(proj) $(obj_path)/GPSDataServerTest.o $(obj_path)/GPSDataServer.o

GPSDataServerTest.o: GPSDataServerTest.cpp GPSDataServer.o
	$(cxx) $(cflags) -c GPSDataServerTest.cpp -o $(obj_path)/GPSDataServerTest.o

GPSDataServer.o: GPSDataServer.cpp Server.h
	$(cxx) $(cflags) -c GPSDataServer.cpp -o $(obj_path)/GPSDataServer.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
