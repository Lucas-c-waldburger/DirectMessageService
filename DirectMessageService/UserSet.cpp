#include "UserSet.h"

User::User(SOCKET newFd, const std::string& newUsrnm) : fd(newFd), username(newUsrnm)
{}



bool UserSet::add(SOCKET newFd, const std::string& newUsrnm)
{
    auto [_, success] = mSet.insert({ newFd, newUsrnm });

    return success;
}


//bool UserSet::remove(SOCKET fd)
//{
//    try
//    {
//        auto user = getUser(fd);
//        return (!mSet.erase(fd));
//    }
//
//    catch (std::invalid_argument& ex)
//    {
//        std::cout << ex.what() << '\n';
//        return false;
//    }
//}


SOCKET UserSet::operator[](const std::string& usrnm)
{
    auto found = mSet.get<BY_USERNAME>().find(usrnm);

    if (found == mSet.get<BY_USERNAME>().end())
        throw std::invalid_argument("Username does not exist in set");

    return found->fd;
}

const std::string& UserSet::operator[](SOCKET fd)
{
    auto found = mSet.get<BY_FD>().find(fd);

    if (found == mSet.get<BY_FD>().end())
        throw std::invalid_argument("socket fd does not exist in set");

    return found->username;
}

UserSet::USER_ITER_FD UserSet::getUser(SOCKET fd)
{
    auto user = mSet.get<BY_FD>().find(fd);

    if (user == mSet.get<BY_FD>().end())
        throw std::invalid_argument("socket fd does not exist in set");

    return user;
}

UserSet::USER_ITER_USERNAME UserSet::getUser(const std::string& usrnm)
{
    auto user = mSet.get<BY_USERNAME>().find(usrnm);

    if (user == mSet.get<BY_USERNAME>().end())
        throw std::invalid_argument("username does not exist in set");

    return user;
}

bool UserSet::notFound(USER_ITER_FD& user)
{
    return user == mSet.get<BY_FD>().end();
}

bool UserSet::notFound(USER_ITER_USERNAME& user)
{
    return user == mSet.get<BY_USERNAME>().end();
}

