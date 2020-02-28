proj=IRC_Server

obj_path=../obj
bin_path=../bin
server_path=../../lib/Server/src

cxx=g++
cflags= -Wall -g -I$(server_path)

$(proj): TestCase.o DemoServer.o
	$(cxx) $(cflags) -o $(bin_path)/$(proj) $(obj_path)/TestCase.o $(obj_path)/DemoServer.o

Server.o : Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

TestCase.o: TestCase.cpp DemoServer.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

DemoServer.o: DemoServer.h
	$(cxx) $(cflags) -c DemoServer.cpp -o $(obj_path)/DemoServer.o
	
clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
