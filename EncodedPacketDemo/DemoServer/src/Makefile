proj=GPSDemoServer

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): TestCase.o DemoServer.o
	$(cxx) $(cflags) -o $(bin_path)/$(proj) $(obj_path)/TestCase.o $(obj_path)/DemoServer.o

TestCase.o: TestCase.cpp DemoServer.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

DemoServer.o: DemoServer.cpp Server.h
	$(cxx) $(cflags) -c DemoServer.cpp -o $(obj_path)/DemoServer.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
