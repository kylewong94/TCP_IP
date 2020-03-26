proj=ClientTest

obj_path=../obj
bin_path=../bin

cxx=g++
cflags= -Wall -g

$(proj): TestCase.o ImageClient.o Client.o
	$(cxx) $(cflags) -o $(bin_path)/$(proj) $(obj_path)/TestCase.o $(obj_path)/ImageClient.o $(obj_path)/Client.o

TestCase.o: TestCase.cpp ImageClient.o
	$(cxx) $(cflags) -c TestCase.cpp -o $(obj_path)/TestCase.o

ImageClient.o: ImageClient.h Client.o
	$(cxx) $(cflags) -c ImageClient.cpp -o $(obj_path)/ImageClient.o

Client.o: Client.h
	$(cxx) $(cflags) -c Client.cpp -o $(obj_path)/Client.o

clean:
	rm -f $(bin_path)/ClientTest
	rm -f $(obj_path)/*.o
