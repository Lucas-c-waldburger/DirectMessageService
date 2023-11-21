#include "App.h"


bool App::Init()
{
    if (wsaInit)
    {
        std::cout << "Winsock already initialized\n";
        return false;
    }

    try
    {
        wsaInit = std::make_unique<WSAInit>();
    }

    catch (std::runtime_error& ex)
    {
        std::cout << ex.what();
        return false;
    }

}

