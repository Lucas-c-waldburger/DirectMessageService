#include "UserSet.h"

User::User(SOCKET newFd, const std::string& newUsrnm) : fd(newFd), username(newUsrnm)
{}



bool UserSet::add(SOCKET newFd, const std::string& newUsrnm)
{
    auto [_, success] = mSet.insert({ newFd, newUsrnm });

    return success;
}


bool UserSet::remove(SOCKET fd)
{
    try
    {
        auto user = getUser(fd);
        return (mSet.erase(user) != mSet.get<BY_FD>().end());
    }

    catch (std::invalid_argument& ex)
    { 
        std::cout << ex.what() << '\n';
        return false;
    }
}

// can only erase using fd as key, so we use usrnm to get the appropriate 
// fd iterator and erase using that
bool UserSet::remove(const std::string& usrnm)
{
    try
    {
        auto userByNm = getUser(usrnm);

        if (found(userByNm))
        {
            auto userByFd = getUser(userByNm->fd);
            return (mSet.erase(userByFd) != mSet.get<BY_FD>().end());
        }

        return false;
    }

    catch (std::invalid_argument& ex)
    {
        std::cout << ex.what() << '\n';
        return false;
    }
}

const SOCKET* UserSet::operator[](const std::string& usrnm)
{
    try
    {
        auto user = getUser(usrnm);
        return &user->fd;
    }
    catch (std::invalid_argument& ex)
    {
        return nullptr;
    }
}

const std::string* UserSet::operator[](SOCKET fd)
{
    try
    {
        auto user = getUser(fd);
        return &user->username;
    }
    catch (std::invalid_argument& ex)
    {
        return nullptr;
    }
}

bool UserSet::hasUsername(SOCKET fd) const
{
    return mSet.count(fd) > 0;
}

/* Maybe move outside UserSet class to specifically interact with UsernameValidator */
bool UserSet::usernameExists(std::string_view usrnm)
{
    return this->operator[](std::string{usrnm}) != nullptr;
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

bool UserSet::found(USER_ITER_FD& user)
{
    return user != mSet.get<BY_FD>().end();
}

bool UserSet::found(USER_ITER_USERNAME& user)
{
    return user != mSet.get<BY_USERNAME>().end();
}

