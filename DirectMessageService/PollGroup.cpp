#include "PollGroup.h"


PollGroup::PollGroup(SOCKET listener) : timeout(-1)
{
    add(listener, POLLIN);
}

PollGroup::PollGroup(SOCKET listener, int timeO) : timeout(timeO)
{
    add(listener, POLLIN);
}

void PollGroup::add(SOCKET sockFd, short events)
{
    pfds.push_back({ sockFd, events, 0 });
}

bool PollGroup::remove(SOCKET sockFd)
{
    auto toRemove = 
        pfds.erase
        (
            std::remove_if
            (
                pfds.begin(), pfds.end(), [&sockFd](pollfd& pfd) { return pfd.fd == sockFd; }
            ),
            pfds.end()
        );

    return (toRemove != pfds.end());
}

const SOCKET& PollGroup::listenerFd()
{
    return pfds[0].fd;
}

PollGroup::IterPair PollGroup::getIters()
{
    return std::make_pair(pfds.begin(), pfds.end());
}

int PollGroup::poll()
{
    if (pfds.empty())
        return 0;

    return WSAPoll(&pfds[0], pfds.size(), timeout);
}

int PollGroup::size()
{

    return pfds.size();
}
