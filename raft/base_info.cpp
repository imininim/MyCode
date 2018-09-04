#include <base_info.h>

#include <iostream>

using namespace std;

BaseInfo::BaseInfo():currentTerm(-1), getVote(0), vote(1) {}

void BaseInfo::ShowInfo() const {
	cerr << "currentTerm: " << currentTerm << endl
		<< "getVote: " << getVote << endl
		<< "vote: " << vote << endl
		<< "leaderId: " << leaderId << endl
		<< "votedFor: " << votedFor << endl;
}
