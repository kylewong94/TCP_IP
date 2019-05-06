proj=IRC_Server

obj_path=../obj
bin_path=../bin

cxx=g++
cflags= -Wall -g

$(proj): TestCase.o Server.o
	$(cxx) $(cflags) -o $(bin_path)/$(proj) $(obj_path)/TestCase.o $(obj_path)/Server.o

TestCase.o: TestCase.cpp Server.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

Server.o: Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)*.o
