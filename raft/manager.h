#ifndef __manager_h__
#define __manager_h__

#include <container.h>
#include <base_info.h>
#include <ip_list.h>
#include <timer.h>
#include <node_status.h>
#include <rpc.h>

class Manager {
public:
	void Init();
	int ResponseAppendEntriesRPC(const AppendEntriesRPC &appendEntriesRPC, std::string &ret);
	int ResponseRequestVoteRPC(const RequestVoteRPC &requestVoteRPC, std::string &ret);
	int ResponseAwakeRPC(const AwakeRPC &awakeRPC, std::string &ret);
	void ShowInfo() const;
private:
	//状态机
	Action *m_action;
	//数据容器
	Container m_container;
	//定时器任务
	std::vector<Timer*> m_timerList;
	//基础信息
	BaseInfo m_baseInfo;
	//ip列表
	IpList m_ipList;
};

#endif
