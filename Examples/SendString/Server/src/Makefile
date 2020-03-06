proj=StringTest

root= ../../../
obj_path=../obj
bin_path=../bin


cxx=g++
cflags= -Wall -g  

$(proj): ServerTest.o Server.o
	$(cxx) $(cflags) $(obj_path)/ServerTest.o $(obj_path)/Server.o -o $(bin_path)/$(proj)

ServerTest.o: ServerTest.cpp Server.o
	$(cxx) $(cflags) -c ServerTest.cpp -o $(obj_path)/ServerTest.o

Server.o: Server.h
	$(cxx) $(cflags) -c Server.cpp -o $(obj_path)/Server.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
