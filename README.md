# TCP/IP Module
Purpose: A module for TCP/IP communication, can be used to be implemented in larger projects that require network communication

Note: This repository is meant for the creator's development of software engineering skills, please excuse possible errors or typos. This repo takes a lot of information from Beej's Networking Guide and the Linux Man Pages which can be followed through the hyperlink(s). This repo is also under construction as well so the README and software will be subject to change.

## Table of Contents
1. [Installation]
2. [Demos]
3. [Developer and Beginner's code reference](#dev-guide)
   <br/>a. [Structs](#struct)
   <br/>b. [Library Functions](#lib-func)
   
## Installation
Open up your command line application and clone this repository

```
git clone https://github.com/kylewong94/TCP_IP.git
```
From here please take a look at the following DEMOs in order to get a hang of how the class is structured

[Setting up the server for telnet communication]
[Sending/Receiving datapackets]
[Sending/Receiving Images]
[Sending/Receiving Commands (Embedded)]


<!-- (#dev-guide) -->
## Developer and Beginner's code reference

<!-- (#struct) -->
### Structs

**struct addrinfo**

This struct prepares the socket for continuous use

[Man page for "struct addrinfo"](http://man7.org/linux/man-pages/man7/ip.7.html)

```c++
struct addrinfo 
{
  int              ai_flags;      //AI_PASSIVE
  int              ai_family;     //AF_INET, AF_INET6, AF_UNSPEC
  int              ai_socktype;   //SOCK_STREAM, SOCK_DGRAM
  int              ai_protocol;   //use 0 for "any"
  size_t           ai_addrlen;    //size of ai_addr in bytes
  struct sockaddr *ai_addr;       //struct sockaddr_in or _in6
  char            *ai_canonname;  //full canonical hostname
  
  struct addrinfo *ai_next;       //next address (in linked list)
}
```

**struct sockaddr and struct sockaddr_in**

[Man page for "struct sockaddr and struct sockaddr_in"](http://man7.org/linux/man-pages/man7/ip.7.html)

sockaddr is the generic socket descriptor for any type of socket operation sockaddr_in is the socket descriptor specifically for IP-based communication

**struct sockaddr**

```c++
struct sockaddr
{
  unsigned short  sa_family;   //address family AF_XXX
  char            sa_data[14]; //14 bytes of protocal address
}
```


**struct sockaddr_in**

```c++
struct sockaddr_in
{
  short int           sin_family;   //AF_INET
  unsigned short int  sin_port;     //Port Number
  struct in_addr      sin_addr;     //Internet Address
  unsigned char       sin_zero[8];  //Same size as struct sockaddr 
}
```


**struct in_addr**

```c++
struct in_addr
{
  uint32_t s_addr; //the 32-bit address
}
```

For iPv6 addresses struct sockaddr_in6

Summary: Same as sockaddr_in but larger storage for bigger address

```c++
struct sockaddr_in6
{
  u_int16_t       sin6_family; //AF_INET6
  u_int16_t       sin6_port;
  u_int32_t       sin6_flowinfo; //IPv6 information
  struct in6_addr sin6_addr;
  u_int32_t       sin6_scope_id;
}
```
As with the iPv4 sockaddr structm iPv6's comes with its own properly sized in_addr

```c++
struct in6_addr
{
  unsigned char   s6_addr[16];
}
```
For overflow In some cases you will not know if the struct coming in is a IPv4 or IPv6 so this is a solution

```c++
struct sockaddr_storage
{
  sa_family_t ss_family;
  
  char        __ss_pad1[_SS_PAD1SIZE];
  int64_t     __ss_align;
  char        __ss_pad2[_SS_PAD2SIZE];
}
```
<!-- (#lib-func) -->
### Library Functions
This section provides information on commonly used functions provided by c++

**Manipulating IP Address**

```c++
inet_pton(ADDRESS_FAMILY, ADDRESS, &(STRUCT)) 
```

[inet_pton man page](http://man7.org/linux/man-pages/man3/inet_pton.3.html)

```c++
struct sockaddr_in  sa;

struct sockaddr_in6 sa6;

inet_pton(AF_INET, "10.12.110.57", &(sa.sockaddr_in));
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));
```

**Filling in structs for later use**

```c++
getaddrinfo(const char * node, const char * service, 
              const struct addrinfo * hints, struct addrinfo **res)
```

[getaddrinfo man page](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)

In most cases the first parameter const char * node contains the address that you are connecting to. For example an IP address or a webserver.

However if you are hosting you would leave it NULL

The following example shows how it works when setting up as a Server

```c++
int status;
struct addrinfo hints;
struct addrinfo *servinfo;

memset(&hints, sizeof hints);
hints.ai_family   = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags    = AI_PASSIVE;

if((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) !=0)
{
 
    fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(status));
    exit(-1); 
}

//Do what is needed to be done

freeaddrinfo(servinfo);
```

**Creating a socket file descriptor**

```c++
int socket(int Domain, int Type, int Protocol);
```

[socket man page](http://man7.org/linux/man-pages/man2/socket.2.html)

This returns a integer that relates to the socket file descriptor

The following example creates an array of sockets in order to store socket file descriptors.

(NOTE: the array size is 6 means we can store a maximum of 6 connections)

```c++
struct addrinfo hints, *res;
int Sockets[6];

int TotalConnections = 0;

//while finding connections

//connection found
getaddrinfo("192.168.4.3", "IPv4", &hints, &res);

if(TotalConnections < 6)
{
    Sockets[TotalConnections] = socket(res->ai_family, res->ai_socktype, res->ai_protocol)
    TotalConnection++;
}

//Do what is needed to be done
freeaddrinfo(r); //Free linked list
```

**Binding**

```c++
int bind(int socket, struct sockaddr *myaddr, int addrlen)
```
[bind man page](http://man7.org/linux/man-pages/man2/bind.2.html)

This functions returns a -1 or 0 identifing success of binding to a port. This function takes the socket file descriptor and the sockaddr and binds it to a port specified in the initial set up of the sockaddr.

The following example shows how bind is used as a host

```c++
int HostSocket;

struct sockaddr HostAddr;
struct sockaddr *ptAddr;

memset(&HostAddr, sizeof HostAddr);
HostAddr.ai_family   = AF_UNSPEC;
HostAddr.ai_socktype = SOCK_STREAM;
HostAddr.ai_flags    = AI_FLAGS;

getaddrinfo(NULL, "780", &HostAddr, &ptAddr);

HostSocket = socket(ptAddr->ai_family, ptAddr->ai_socktype, ptAddr->ai_protocol);

bind(HostSocket, ptAddr->ai_addr, ptAddr->ai_addrlen);
```

**Connecting**

```c++
int connect(int sockfd, struct sockaddr *server_addr, int addrlen);
```

[connect man page](http://man7.org/linux/man-pages/man2/connect.2.html)

This function connects you to the specified address returns a -1 or 0 identifing success.

Assuming you already set up the addrinfo and the pointer addrinfo with the initial socket.

```c++
//getaddrinfo("www.helloworld.com", "780", &ClientAddr, &ptAddr);

connect(ClientSocket, ptAddr->ai_addr, ptAddr->ai_addrlen);
```
