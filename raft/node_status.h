#ifndef __node_status_h__
#define __node_status_h__

#include <nocopyable.h>
#include <string>

class Manager;
enum Role { sleep=0,slave=1,campaigner=2,master=3 };

class NodeStatus;

class Action {
public:
	void SetStatus(NodeStatus *status);

	NodeStatus *m_pNodeStatus;
};

class NodeStatus: public Nocopyable {
public:
	NodeStatus():m_pAction(nullptr), m_pManager(nullptr) {}
	NodeStatus(Action *pAction, Manager *pManager):m_pAction(pAction), m_pManager(pManager) {}
	Manager *GetManager() const {
		return m_pManager;
	}
	virtual int SetStatus(Role role)=0;
	virtual void DoWork()=0;
	virtual std::string ResponseRPC(const std::string &data)=0;
	virtual ~NodeStatus() {}
protected:
	Action *m_pAction;
	Manager *m_pManager;
};

class SleepStatus:public NodeStatus {
public:
	SleepStatus(Action *pAction, Manager *pManager):NodeStatus(pAction, pManager) {}
	virtual void DoWork();
	virtual int SetStatus(Role role);
	virtual std::string ResponseRPC(const std::string &data);
private:
};

class SlaveStatus:public NodeStatus {
public:
	SlaveStatus(Action *pAction, Manager *pManager):NodeStatus(pAction, pManager) {}
	virtual void DoWork();
	virtual int SetStatus(Role role);
	virtual std::string ResponseRPC(const std::string &data);
private:
	
};

class CampaignerStatus:public NodeStatus {
public:
	CampaignerStatus(Action *pAction, Manager *pManager):NodeStatus(pAction, pManager) {}
	virtual void DoWork();
	virtual int SetStatus(Role role);
	virtual std::string ResponseRPC(const std::string &data);
private:
};

class MasterStatus:public NodeStatus {
public:
	MasterStatus(Action *pAction, Manager *pManager):NodeStatus(pAction, pManager) {}
	virtual void DoWork();
	virtual int SetStatus(Role role);
	virtual std::string ResponseRPC(const std::string &data);
private:
	
};

#endif
