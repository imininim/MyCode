#include <node_status.h>
#include <rpc.h>
#include <manager.h>

#include <iostream>

using namespace std;

int main() {
	Action action;
	Manager manager;
	manager.Init();
	NodeStatus *status = new SleepStatus(&action, &manager);
	action.SetStatus(status);

	action.m_pNodeStatus->SetStatus(Role::slave);
	action.m_pNodeStatus->DoWork();

	AppendEntriesRPC appendEntriesRPC;
	appendEntriesRPC.term = 1;
	appendEntriesRPC.prevLogIndex = 0;
	appendEntriesRPC.prevLogTerm = 0;
	appendEntriesRPC.leaderCommit = 0;
	appendEntriesRPC.leaderId = "127.0.0.1";

	AppendEntriesResp appendEntriesResp;
	{
		cerr << "########### 测试slave 下的 AppendEntriesRPC" << endl;
		string appendEntriesRPCStr = appendEntriesRPC.Dump();

		string resp = action.m_pNodeStatus->ResponseRPC(appendEntriesRPCStr);
		appendEntriesResp.Load(resp);
		cerr << "resp:   term: " << appendEntriesResp.term << " success: " << appendEntriesResp.success << endl;

		action.m_pNodeStatus->DoWork();
		cerr << "########### 测试结束" << endl;
	}
	manager.ShowInfo();
	
	{
		cerr << "########### 测试campaigner 下的 AppendEntriesRPC" << endl;
		action.m_pNodeStatus->SetStatus(Role::campaigner);
		action.m_pNodeStatus->DoWork();

		string appendEntriesRPCStr = appendEntriesRPC.Dump();

		string resp = action.m_pNodeStatus->ResponseRPC(appendEntriesRPCStr);
		appendEntriesResp.Load(resp);
		cerr << "resp:   term: " << appendEntriesResp.term << " success: " << appendEntriesResp.success << endl;

		action.m_pNodeStatus->DoWork();
		cerr << "########### 测试结束" << endl;
	}
	manager.ShowInfo();

	{
		cerr << "########### 测试master 下的 AppendEntriesRPC" << endl;
		action.m_pNodeStatus->SetStatus(Role::campaigner);
		action.m_pNodeStatus->DoWork();
		action.m_pNodeStatus->SetStatus(Role::master);
		action.m_pNodeStatus->DoWork();

		string appendEntriesRPCStr = appendEntriesRPC.Dump();

		string resp = action.m_pNodeStatus->ResponseRPC(appendEntriesRPCStr);
		appendEntriesResp.Load(resp);
		cerr << "resp:   term: " << appendEntriesResp.term << " success: " << appendEntriesResp.success << endl;

		action.m_pNodeStatus->DoWork();
		cerr << "########### 测试结束" << endl;
	}
	manager.ShowInfo();

	{
		cerr << "########### 测试term 不匹配的 AppendEntriesRPC" << endl;
		action.m_pNodeStatus->DoWork();

		appendEntriesRPC.term = 0;
		string appendEntriesRPCStr = appendEntriesRPC.Dump();

		string resp = action.m_pNodeStatus->ResponseRPC(appendEntriesRPCStr);
		appendEntriesResp.Load(resp);
		cerr << "resp:   term: " << appendEntriesResp.term << " success: " << appendEntriesResp.success << endl;

		action.m_pNodeStatus->DoWork();
		cerr << "########### 测试结束" << endl;
	}
	manager.ShowInfo();

	RequestVoteRPC requestVoteRPC;
	requestVoteRPC.term = 2;
	requestVoteRPC.lastLogIndex = 0;
	requestVoteRPC.lastLogTerm = 0;
	requestVoteRPC.candidateId = "127.0.0.1";

	RequestVoteResp requestVoteResp;
	{
		cerr << "########### 测试slave 的 RequestVoteRPC" << endl;
		action.m_pNodeStatus->DoWork();

		string requestVoteRPCStr = requestVoteRPC.Dump();

		string resp = action.m_pNodeStatus->ResponseRPC(requestVoteRPCStr);
		requestVoteResp.Load(resp);
		cerr << "resp:   term: " << requestVoteResp.term << " voteGranted: " << requestVoteResp.voteGranted << endl;

		action.m_pNodeStatus->DoWork();
		cerr << "########### 测试结束" << endl;
	}
	manager.ShowInfo();

	return 0;
}

