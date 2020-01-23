# TCP/IP
Purpose: To wrap the C++ network library in to a reusable module for all projects.

## Table of Contents
1. [Purpose]
2. [Struct Guide]

## Struct Explanation

[Man page for "addrinfo"](http://man7.org/linux/man-pages/man3/getaddrinfo.3.html)

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
