#include <rpc.h>

#include <string.h>

using namespace std;

std::string AppendEntriesRPC::Dump() const {
	string ret;
	char buf[100000];
	buf[0] = 1;
	ret += string(buf, sizeof(char));

	memcpy(buf, &term, sizeof(int));
	ret += string(buf, sizeof(int));

	memcpy(buf, &prevLogIndex, sizeof(int));
	ret += string(buf, sizeof(int));
	
	memcpy(buf, &prevLogTerm, sizeof(int));
	ret += string(buf, sizeof(int));

	memcpy(buf, &leaderCommit, sizeof(int));
	ret += string(buf, sizeof(int));

	memset(buf, 0, sizeof(char)*15);
	memcpy(buf, leaderId.c_str(), leaderId.size());
	ret += string(buf, sizeof(char)*15);

	memcpy(buf, &size, sizeof(char));
	ret += string(buf, sizeof(char));
	return ret;
}

int AppendEntriesRPC::Load(const std::string &str) {
	if (str.size() < 16+sizeof(int)*3) {
		return -1;
	}
	char *offset = const_cast<char*>(str.c_str());
	offset += 1;

	memcpy(&term, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&prevLogIndex, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&prevLogTerm, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&leaderCommit, offset, sizeof(int));
	offset += sizeof(int);

	leaderId = string(offset, 15);
	offset += 15;

	size = *offset;
	offset += 1;
	if (size) {

	}
	return 0;
}

std::string RequestVoteRPC::Dump() const {
	string ret;
	char buf[100000];
	buf[0] = 2;
	ret += string(buf, sizeof(char));

	memcpy(buf, &term, sizeof(int));
	ret += string(buf, sizeof(int));

	memcpy(buf, &lastLogIndex, sizeof(int));
	ret += string(buf, sizeof(int));
	
	memcpy(buf, &lastLogTerm, sizeof(int));
	ret += string(buf, sizeof(int));

	memset(buf, 0, sizeof(char)*15);
	memcpy(buf, candidateId.c_str(), candidateId.size());
	ret += string(buf, sizeof(char)*15);
	return ret;
}

int RequestVoteRPC::Load(const std::string &str) {
	if (str.size() != 16+sizeof(int)*3) {
		return -1;
	}
	char *offset = const_cast<char*>(str.c_str());
	offset += 1;

	memcpy(&term, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&lastLogIndex, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&lastLogTerm, offset, sizeof(int));
	offset += sizeof(int);

	candidateId = string(offset, 15);
	offset += 15;
	return 0;
}


std::string AppendEntriesResp::Dump() const {
	string ret;
	char buf[20];
	memcpy(buf, &term, sizeof(int));
	ret += string(buf, sizeof(int));

	memcpy(buf, &success, sizeof(int));
	ret += string(buf, sizeof(int));
	return ret;
}

int AppendEntriesResp::Load(const std::string &str) {
	char *offset = const_cast<char*>(str.c_str());
	memcpy(&term, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&success, offset, sizeof(int));
	offset += sizeof(int);
	return 0;
}

std::string RequestVoteResp::Dump() const {
	string ret;
	char buf[20];
	memcpy(buf, &term, sizeof(int));
	ret += string(buf, sizeof(int));

	memcpy(buf, &voteGranted, sizeof(int));
	ret += string(buf, sizeof(int));
	return ret;

}

int RequestVoteResp::Load(const std::string &str) {
	char *offset = const_cast<char*>(str.c_str());
	memcpy(&term, offset, sizeof(int));
	offset += sizeof(int);

	memcpy(&voteGranted, offset, sizeof(int));
	offset += sizeof(int);
	return 0;
}

std::string AwakeRPC::Dump() const {
	return "";
}
int AwakeRPC::Load(const std::string &str) {
	return 0;
}

std::string AwakeResp::Dump() const {
	return "";
}
int AwakeResp::Load(const std::string &str) {
	return 0;
}
