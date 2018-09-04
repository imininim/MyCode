#include <manager.h>

void Manager::Init() {
	m_action = new Action();
	m_action->SetStatus(new SleepStatus(m_action, this));
}

void Manager::ShowInfo() const {
	m_baseInfo.ShowInfo();
}

int Manager::ResponseAwakeRPC(const AwakeRPC &awakeRPC, std::string &ret) {
	return 0;
}

int Manager::ResponseAppendEntriesRPC(const AppendEntriesRPC &appendEntriesRPC, std::string &ret) {
	AppendEntriesResp appendEntriesResp{m_baseInfo.currentTerm, 0};
	ret = appendEntriesResp.Dump();
	if (appendEntriesRPC.term < m_baseInfo.currentTerm) {
		return -1;
	}

	if (m_container.Size()) {
		if (m_container.GetLogTermFromIndex(appendEntriesRPC.prevLogIndex) != appendEntriesRPC.prevLogTerm) {
			return -1;
		}
	}
	
	//删除不需要的数据
	m_container.DeleteContent(appendEntriesRPC.prevLogIndex);
	//新增数据
	if (appendEntriesRPC.size) {
		m_container.AppendContent(appendEntriesRPC.content);
	}

	m_baseInfo.leaderId = appendEntriesRPC.leaderId;
	m_baseInfo.currentTerm = appendEntriesRPC.term;

	m_container.SetCommitIndex((appendEntriesRPC.leaderCommit<m_container.GetNewLogIndex())?appendEntriesRPC.leaderCommit:m_container.GetNewLogIndex());

	appendEntriesResp.term = m_baseInfo.currentTerm;
	appendEntriesResp.success = 1;
	ret = appendEntriesResp.Dump();
	return 0;
}

int Manager::ResponseRequestVoteRPC(const RequestVoteRPC &requestVoteRPC, std::string &ret) {
	RequestVoteResp requestVoteResp{m_baseInfo.currentTerm, 0};
	ret = requestVoteResp.Dump();
	if (requestVoteRPC.term < m_baseInfo.currentTerm) {
		return -1;
	}

	if (requestVoteRPC.lastLogIndex < m_container.GetNewLogIndex() || requestVoteRPC.lastLogTerm < m_container.GetNewLogTerm()) {
		return -1;
	}

	if (requestVoteRPC.term == m_baseInfo.currentTerm) {
		if (!m_baseInfo.vote) {
			return -1;
		}
	}

	m_baseInfo.votedFor = requestVoteRPC.candidateId;
	m_baseInfo.vote = 0;

	m_baseInfo.currentTerm = requestVoteRPC.term;

	requestVoteResp.term = m_baseInfo.currentTerm;
	requestVoteResp.voteGranted = 1;
	ret = requestVoteResp.Dump();
	return 0;
}

