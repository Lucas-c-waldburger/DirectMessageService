#pragma once
#include "Utils.h"

using namespace Utils;

//// BUFFER DECL ////

template <size_t BUF_LEN>
class Buffer
{
public:
	Buffer();
	~Buffer();

	char* data();
	const size_t maxLen() const;
	const size_t currentLen() const;
	void clear();

private:
	Buffer(const char* setMsg);
	char mBuf[BUF_LEN];
};


//// BUFFER DEFS ////

template<size_t BUF_LEN>
inline Buffer<BUF_LEN>::Buffer() : mBuf{}
{}

template<size_t BUF_LEN>
inline Buffer<BUF_LEN>::~Buffer()
{}

template<size_t BUF_LEN>
inline char* Buffer<BUF_LEN>::data()
{
	return mBuf;
}

template<size_t BUF_LEN>
inline void Buffer<BUF_LEN>::clear()
{
	memset(mBuf, 0, BUF_LEN);
}

template<size_t BUF_LEN>
inline const size_t Buffer<BUF_LEN>::maxLen() const
{
	return BUF_LEN; 
}

template<size_t BUF_LEN>
inline const size_t Buffer<BUF_LEN>::currentLen() const
{
	return strlen(mBuf);
}

template<size_t BUF_LEN>
inline Buffer<BUF_LEN>::Buffer(const char* setMsg)
{
	memcpy(mBuf, setMsg, BUF_LEN);
}

//// RECVBUFFER ////

constexpr size_t RECV_BUF_LEN = 4096;
using RecvBuffer = Buffer<RECV_BUF_LEN>;


//// SENDBUFFER ////

constexpr size_t SEND_BUF_LEN = 4096;
using SendBuffer = Buffer<SEND_BUF_LEN>;

//// BUFFER PRESETS ////

//template <int I> inline constexpr size_t BUF_LEN;
//
//enum MsgNames
//{
//	ASK_USERNAME
//};
//
//constexpr const char* ASK_USERNAME_MSG = "Successfully connected to Server.\nCreate your username: ";
//template <> inline constexpr size_t BUF_LEN<ASK_USERNAME> = cExprStrlen(ASK_USERNAME_MSG);
//class AskUsernameBuffer : public Buffer<BUF_LEN<ASK_USERNAME>> 
//{ 
//public:
//	AskUsernameBuffer(); 
//	virtual ~AskUsernameBuffer();
//};

