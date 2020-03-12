proj=ImageClient

obj_path=../obj
bin_path=../bin

cxx=g++
cflags= -Wall -g

$(proj): ImageClientTest.o ImageClient.o Client.o
	$(cxx) $(cflags) $(obj_path)/ImageClientTest.o $(obj_path)/ImageClient.o $(obj_path)/Client.o -o $(bin_path)/$(proj)

ImageClientTest.o: ImageClientTest.cpp ImageClient.o
	$(cxx) $(cflags) -c ImageClientTest.cpp -o $(obj_path)/ImageClientTest.o

ImageClient.o: ImageClient.h Client.o
	$(cxx) $(cflags) -c ImageClient.cpp -o $(obj_path)/ImageClient.o

Client.o: Client.h
	$(cxx) $(cflags) -c Client.cpp -o $(obj_path)/Client.o

clean:
	rm -f $(bin_path)/*
	rm -f $(obj_path)/*.o
