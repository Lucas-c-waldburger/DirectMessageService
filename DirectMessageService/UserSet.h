#pragma once
#include "Utils.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index/hashed_index.hpp>


struct User
{
	User(SOCKET newFd, const std::string& newUsrnm);

	SOCKET fd;
	std::string username;
};

// birectional mapping for user vars ( fd <-> username ) with fast lookup/insertion 
class UserSet
{
public:
	bool add(SOCKET newFd, const std::string& newUsrnm);
    //bool remove(SOCKET fd);

    template <typename T>
    bool remove(const T& key);

    //bool remove(const std::string& usrnm);

	SOCKET operator[](const std::string& usrnm);
	const std::string& operator[](SOCKET fd);


private:
    struct BY_FD {};
    struct BY_USERNAME {};

    using USER_SET = boost::multi_index_container<
        User,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_unique<
                boost::multi_index::tag<BY_FD>,
                boost::multi_index::member<User, SOCKET, &User::fd>
            >,
            boost::multi_index::hashed_unique<
                boost::multi_index::tag<BY_USERNAME>,
                boost::multi_index::member<User, std::string, &User::username>
            >
        >
    >;

    using USER_ITER_FD = boost::multi_index::detail::hashed_index_iterator<
        boost::multi_index::detail::hashed_index_node<
            boost::multi_index::detail::hashed_index_node<
                boost::multi_index::detail::index_node_base<
                    User,
                    std::allocator<User>
                >
            >
        >,
        boost::multi_index::detail::bucket_array<std::allocator<User>>,
        boost::multi_index::detail::hashed_unique_tag,
        boost::multi_index::detail::hashed_index_global_iterator_tag
    >;

    using USER_ITER_USERNAME = boost::multi_index::detail::hashed_index_iterator<
        boost::multi_index::detail::hashed_index_node<
            boost::multi_index::detail::index_node_base<
                User,
                std::allocator<User>
            >
        >,
        boost::multi_index::detail::bucket_array<std::allocator<User>>,
        boost::multi_index::detail::hashed_unique_tag,
        boost::multi_index::detail::hashed_index_global_iterator_tag
    >;

    USER_SET mSet;

    USER_ITER_FD getUser(SOCKET fd);
    USER_ITER_USERNAME getUser(const std::string& usrnm);

    bool notFound(USER_ITER_FD& user);
    bool notFound(USER_ITER_USERNAME& user);
};

template<typename T>
inline bool UserSet::remove(const T& key)
{
    try
    {
        auto user = getUser(key);
        return (!notFound(mSet.erase(key)));
    }

    catch (std::invalid_argument& ex)
    {
        std::cout << ex.what() << '\n';
        return false;
    }
}
