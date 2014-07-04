#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include <string>
#include <sstream>

template<typename T>
float sign(T num)
{
    if(num >= 0)  return 1;
    else return -1;
}

template < typename T >
std::string to_string( const T& v )
{
    std::ostringstream stm ;
    return ( stm << v ) ? stm.str() : "{*** error ***}" ;
}

#endif // UTIL_H_INCLUDED
