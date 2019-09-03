proj=IRC_Server

obj_path=../obj
bin_path=../bin

cxx=g++
cflags= -Wall -g

$(proj): TestCase.o Client.o
	$(cxx) $(cflags) -o $(bin_path)/$(proj) $(obj_path)/TestCase.o $(obj_path)/Client.o

TestCase.o: TestCase.cpp Client.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

Client.o: Client.h
	$(cxx) $(cflags) -c Client.cpp -o $(obj_path)/Client.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
