// ChatTracker.cpp

// This is a correct but inefficient implementation of
// the ChatTracker functionality.
#include "ChatTracker.h"
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <functional>
#include <cassert>
#include <iostream>
using namespace std;

class ChatTracketImpl;
// This class does the real work of the implementation.

class ChatTrackerImpl
{
public:
	ChatTrackerImpl(int maxBuckets);
	void join(string user, string chat);
	int terminate(string chat);
	int contribute(string user);
	int leave(string user, string chat);
	int leave(string user);
	int getBuckets() const { return m_bucketSize; }
	// Called by constructor to store the parameter bucket size number

private:
	struct Info
	{
		Info(string u, string c) : user(u), chat(c), count(0) {}
		string user;
		string chat;
		int count;
	};
	int m_bucketSize;

	unsigned int keyGen(string& name) const;
	vector < list< Info >> m_usersWhoLeft;
	vector < list<Info>> m_info;
	vector < list<Info>> m_chatrooms;
};

unsigned int ChatTrackerImpl::keyGen(string& name) const
{
	//hash function for strings
	unsigned int h = 2166136261u;
	for (int k = 0; k < name.size(); k++)
	{
		h += name[k];
		h *= 16777619;
	}
	return h % m_bucketSize;
}
ChatTrackerImpl::ChatTrackerImpl(int maxBuckets)
{
	//set bucketsize to the one passed int
	m_bucketSize = maxBuckets;
	m_info.resize(getBuckets());
	m_usersWhoLeft.resize(getBuckets());
	m_chatrooms.resize(getBuckets());
}

void ChatTrackerImpl::join(string user, string chat)
{
	// Gnerate bucket number hashed by user
	unsigned int bucket = keyGen(user);
	list<Info>::iterator p = m_info[bucket].end();
	while (p != m_info[bucket].begin())
	{
		// Decrement iterator first because .end() accesses outside of the scope
		--p;
		// If user already exists, doesn't change anything
		if (p->user == user && p->chat == chat)
		{
			Info temp = *p;
			m_info[bucket].erase(p);
			m_info[bucket].push_back(temp);
			return;
		}
	}
	// If user & chat didn't already exist, just push back to its list
	m_info[bucket].push_back(Info(user, chat));

	//add Info to chat vector hashed by chat name
	unsigned int cBucket = keyGen(chat);
	m_chatrooms[cBucket].push_back(Info(user, chat));
}

int ChatTrackerImpl::contribute(string user)
{
	unsigned int bucket = keyGen(user);
	list<Info>::iterator p = m_info[bucket].end();
	//iteratorate through list and increment the count
	while (p != m_info[bucket].begin())
	{
		p--;
		if (p->user == user)
		{
			p->count++;
			return p->count;
		}
	}
	return 0;
}

int ChatTrackerImpl::terminate(string chat)
{
	int total = 0;
	//look in chat bucket, add count of users into total
	unsigned int c = keyGen(chat);
	list<Info>::iterator p = m_chatrooms[c].end();

	while (p != m_chatrooms[c].begin())
	{
		p--;
		string userName = p->user;
		unsigned int b = keyGen(userName);   //get the bucket that user is in for m_info
		//iterate through m_info and add to total if chat matches
		list<Info>::iterator u = m_info[b].end();
		while (u != m_info[b].begin())
		{
			u--;
			if (u->chat == chat)
			{
				total += u->count;
				u = m_info[b].erase(u);
			}
		}
	}

	//iterate through m_usersWhoLeft and add to total
	list<Info>::iterator k = m_usersWhoLeft[c].end();
	while (k != m_usersWhoLeft[c].begin())
	{
		k--;
		if (k->chat == chat)
		{
			total += k->count;
			k = m_usersWhoLeft[c].erase(k);
		}
	}

	//if the user's last chat (most current chat) is the chat, when chat terminated, the second to last chat is the current chat
	return total;
}

int ChatTrackerImpl::leave(string user, string chat)
{
	//find the user in its bucket and delete last item (current chat)
	unsigned int bucket = keyGen(user);
	unsigned int c = keyGen(chat);
	list<Info>::iterator p = m_info[bucket].end();

	while (p != m_info[bucket].begin())
	{
		p--;
		if (p->user == user && p->chat == chat)
		{
			int count = p->count;
			//push_back to m_usersWhoLeft list sorted by chat name
			m_usersWhoLeft[c].push_back(*p);
			m_info[bucket].erase(p);
			return count;
		}
	}
	return -1;
}

int ChatTrackerImpl::leave(string user)
{
	//find the bucket that users are stored in

	unsigned int bucket = keyGen(user);

	list<Info>::iterator p = m_info[bucket].end();

	while (p != m_info[bucket].begin())
	{
		p--;
		if (p->user == user)
		{
			int count = p->count;
			string chatName = p->chat;
			unsigned int c = keyGen(chatName);
			m_usersWhoLeft[c].push_back(*p);
			m_info[bucket].erase(p);
			return count;
		}
	}

	return -1;
}

//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
	m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
	delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
	m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
	return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
	return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
	return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
	return m_impl->leave(user);
}