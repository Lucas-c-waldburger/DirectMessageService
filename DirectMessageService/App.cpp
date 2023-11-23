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
        server = std::make_unique<Server>(HOST_IP, PORT);
    }

    catch (std::runtime_error& ex)
    {
        std::cout << ex.what();
        return false;
    }


    return true;
}

