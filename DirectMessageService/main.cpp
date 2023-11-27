#include <iostream>
#include <limits>
#include <numeric>
#include "App.h"
#include "Server.h"

using namespace Utils;

int main()
{
    if (!App::Init())
        return -1;


    UserSet userSet;

    std::cout << std::boolalpha << userSet.add(1, "lukazz1");
    std::cout << std::boolalpha << userSet.remove(1);












    return 0;
}

// When sending CLIENT to SERVER : htons/l
// When sending SERVER to CLIENT : ntohs/l
// only when larger than chars! (sockets, ports, addresses)


// SERVER
    // HAS:
        // listener connection
        // map of usernames to fd's
        // poll array + managing interface
   // DOES:
        // accept()s new connections <- ListenerConnectionOLD
        // register()s users (RegistrationRequest)
        // poll()s connections for events <- PollGroup
        // recv()s events(requests) from connections
            // route()s MsgRequests to requested user
            // establishes direct message channels from a NewChannelRequest
            // serves up info (available users) from a ServerInfoRequest


// All requests sent as char arrays
// reserved portion in the beginning identifies request type

// user commands
    // /msg 'username'
        // if success, all text entered will be sent to username
            // UNLESS small reserved part of message identitied (/commands)
        // USER VIEW:
            // /msg picketingElm
            // now messaging picketingElm
            // ----------------------------------------------
            // [lukazz1]: hey
            // [picketingElm]: hey dude
            // 
            // 
            // 
            // 
            // 
            // 
            // 
            // 
            // ----------------------------------------------
            // to [picketingElm]: whatsup_
            // ----------------------------------------------  
    //      // [