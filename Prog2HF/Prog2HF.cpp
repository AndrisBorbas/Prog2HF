#ifdef isSFML
#include <SFML/Graphics.hpp>
#endif
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}