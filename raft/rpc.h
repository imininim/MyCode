#ifndef __rpc_h__
#define __rpc_h__

#include <container.h>
#include <string>

const int append_entriesRPC = 1;
const int request_voteRPC = 2;
const int awakeRPC = 3;

class RPC {
public:
	static int Test(const std::string &data) {
		return static_cast<int>(data[0]);
	};
};

struct AppendEntriesRPC {
	AppendEntriesRPC():size(0) {}
	int term;
	int prevLogIndex;
	int prevLogTerm;
	int leaderCommit;
	char size;
	std::string leaderId;
	Content content;

	std::string Dump() const;
	int Load(const std::string &str);
};

struct AppendEntriesResp {
	int term;
	int success;
	std::string Dump() const;
	int Load(const std::string &str);
};

struct RequestVoteRPC {
	int term;
	int lastLogIndex;
	int lastLogTerm;
	std::string candidateId;

	std::string Dump() const;
	int Load(const std::string &str);
};

struct RequestVoteResp {
	int term;
	int voteGranted;
	std::string Dump() const;
	int Load(const std::string &str);
};

struct AwakeRPC {
	std::string Dump() const;
	int Load(const std::string &str);
};

struct AwakeResp {
	std::string Dump() const;
	int Load(const std::string &str);
};
#endif
