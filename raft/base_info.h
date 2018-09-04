#ifndef __base_info_h__
#define __base_info_h__

#include <string>

class BaseInfo {
public:
	BaseInfo();
	void ShowInfo() const;
public:
	int currentTerm;
	int getVote;
	int vote;

	std::string leaderId;
	std::string votedFor;
};

#endif
