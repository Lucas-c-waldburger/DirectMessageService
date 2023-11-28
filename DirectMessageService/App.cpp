#include "App.h"


bool App::Init()
{
    try
    {
        // Initialize Winsock
        wsaInit = std::make_unique<WSAInit>();

    #if RUN_AS_SERVER
        // Initialize Server Logic
        server = std::make_unique<Server>(HOST_IP, PORT);

    #elif RUN_AS_CLIENT
        // Initialize Client Logic
        client = std::make_unique<Client>(HOST_IP, PORT);

    #endif

    }

    catch (std::runtime_error& ex)
    {
        std::cout << ex.what();
        return false;
    }

    return true;
}

