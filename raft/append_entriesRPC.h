#ifndef __append_entriesRPC_h__
#define __append_entriesRPC_h__

struct AppendEntriesRPC {
	int term;
	int prevLogIndex;
	int prevLogTerm;
	int leaderCommit;
	std::string leaderId;
	Content context;
};



#endif
