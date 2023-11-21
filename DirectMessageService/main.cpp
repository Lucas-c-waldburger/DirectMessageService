#include <iostream>
#include "App.h"
#include "PacketImpl.h"

using namespace Utils;

int main()
{
    if (!App::Init())
        return -1;

    FdIndexPacket fdPack;

    fdPack.fill(3);

    uint16_t conv, conv2;

    memcpy(&conv, fdPack.get(), sizeof(conv));
    
    //conv2 = ntohs(conv);

    std::cout << conv;

 /*   uint16_t sh = 0;
    uint16_t sh2;
    char buf1[2];
    char buf2[2];


    memcpy(buf1, &sh, sizeof(sh));*/
    //memcpy(&sh2, buf1, sizeof(sh2));


    //for (int i = 0; i < 2; i++)
    //{
    //    std::cout << "buf[" << i << "]: " << std::hexfloat << buf1[i] << '\n';
    //}









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
        // accept()s new connections <- ListenerConnection
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