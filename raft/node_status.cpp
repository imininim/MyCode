#include <node_status.h>

#include <iostream>

#include <manager.h>
#include <rpc.h>

using namespace std;

void Action::SetStatus(NodeStatus *status) {
	m_pNodeStatus = status;
}

void SleepStatus::DoWork() {
	cerr << "I'm Sleep" << endl;
}

int SleepStatus::SetStatus(Role role) {
	switch(role) {
		case Role::slave:
			m_pAction->SetStatus(new SlaveStatus(m_pAction, m_pManager));
			break;
		default:
			break;
	}
	return 0;
}

string SleepStatus::ResponseRPC(const std::string &data) {
	string ret;
	switch(RPC::Test(data)) {
		case awakeRPC: {
				AwakeRPC awakeRPC;
				if (0 == awakeRPC.Load(data)) {
					if (m_pManager->ResponseAwakeRPC(awakeRPC, ret) == 0) {
						SetStatus(Role::slave);
					}
				}
				break;
			}
	}
	return ret;
}

void SlaveStatus::DoWork() {
	cerr << "I'm Slave" << endl;
}

int SlaveStatus::SetStatus(Role role) {
	switch(role) {
		case Role::campaigner:
			m_pAction->SetStatus(new CampaignerStatus(m_pAction, m_pManager));
			break;
		case Role::sleep:
			m_pAction->SetStatus(new SleepStatus(m_pAction, m_pManager));
			break;
		default:
			break;
	}
	return 0;
}

string SlaveStatus::ResponseRPC(const std::string &data) {
	string ret;
	switch(RPC::Test(data)) {
		case append_entriesRPC: {
				AppendEntriesRPC appendEntriesRPC;
				if (0 == appendEntriesRPC.Load(data)) {
					m_pManager->ResponseAppendEntriesRPC(appendEntriesRPC, ret);
				}
				break;
			}
		case request_voteRPC: {
				RequestVoteRPC requestVoteRPC;
				if (0 == requestVoteRPC.Load(data)) {
					m_pManager->ResponseRequestVoteRPC(requestVoteRPC, ret);
				}
				break;
			}
	}
	return ret;
}

void CampaignerStatus::DoWork() {
	cerr << "I'm Campaigner" << endl;
}

int CampaignerStatus::SetStatus(Role role) {
	switch(role) {
		case Role::slave:
			m_pAction->SetStatus(new SlaveStatus(m_pAction, m_pManager));
			break;
		case Role::sleep:
			m_pAction->SetStatus(new SleepStatus(m_pAction, m_pManager));
			break;
		case Role::master:
			m_pAction->SetStatus(new MasterStatus(m_pAction, m_pManager));
			break;
		default:
			break;
	}
	return 0;
}
string CampaignerStatus::ResponseRPC(const std::string &data) {
	string ret;
	switch(RPC::Test(data)) {
		case append_entriesRPC: {
				AppendEntriesRPC appendEntriesRPC;
				if (0 == appendEntriesRPC.Load(data)) {
					if (m_pManager->ResponseAppendEntriesRPC(appendEntriesRPC, ret) == 0) {
						SetStatus(Role::slave);
					}
				}
				break;
			}
		case request_voteRPC: {
				break;
			}
	}
	return ret;
}

void MasterStatus::DoWork() {
	cerr << "I'm Master" << endl;
}

int MasterStatus::SetStatus(Role role) {
	switch(role) {
		case Role::slave:
			m_pAction->SetStatus(new SlaveStatus(m_pAction, m_pManager));
			break;
		case Role::sleep:
			m_pAction->SetStatus(new SleepStatus(m_pAction, m_pManager));
			break;
		default:
			break;
	}
	return 0;
}
string MasterStatus::ResponseRPC(const std::string &data) {
	string ret;
	switch(RPC::Test(data)) {
		case append_entriesRPC: {
				AppendEntriesRPC appendEntriesRPC;
				if (0 == appendEntriesRPC.Load(data)) {
					if (m_pManager->ResponseAppendEntriesRPC(appendEntriesRPC, ret) == 0) {
						SetStatus(Role::slave);
					}
				}
				break;
			}
		case request_voteRPC: {
				break;
			}
	}
	return ret;
}


