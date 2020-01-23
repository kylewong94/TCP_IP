
=# TCP/IP
Purpose: To wrap the C++ network library in to a reusable module for all projects.

## Table of Contents
1. [Purpose]
2. [Struct Guide]

## Struct Explanation

[Man page for "struct addrinfo"](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)

Summary: This struct prepares the socket for continuous use


**struct addrinfo**
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
[Man page for "struct sockaddr and struct sockaddr_in"](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)
Summary: sockaddr is the generic socket descriptor for any type of socket operation
         sockaddr_in is the socket descriptor specifically for IP-based communication

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

**For iPv6 addresses**
**struct sockaddr_in6**
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


**For overflow**
In some cases you will not know if the struct coming in is a IPv4 or IPv6 so this is a solution

```c++
struct sockaddr_storage
{
  sa_family_t ss_family;
  
  char        __ss_pad1[_SS_PAD1SIZE];
  int64_t     __ss_align;
  char        __ss_pad2[_SS_PAD2SIZE];
}
```
