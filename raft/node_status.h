#ifndef __node_status_h__
#define __node_status_h__

enum Role { master=0,slave=1,campaigner=2,sleep=3 };

class Action {
public:

};

class NodeStatus {
public:
	NodeStatus():m_pAction(nullptr), m_pManager(nullptr) {}
	NodeStatus(Action *pAction, Manager *pManager):m_pAction(pAction), m_pManager(pManager) {}
	Manager *GetManager() const {
		return m_pManager;
	}
	virtual int SetState(Role role)=0;
	virtual void DoWork()=0;
	virtual ~NodeStatus() {}
protected:
	Action *m_pAction;
	Manager *m_pManager;
};

class SleepStatus:public NodeStatus {
public:
	virtual void DoWork();
	virtual int SetState(Role role);
};

class SlaveStatus:public NodeStatus {
public:
	virtual void DoWork();
	virtual int SetState(Role role)
};

class CampaignerStatus:public NodeStatus {
public:
	virtual void DoWork();
	virtual int SetState(Role role);
};

class MasterStatus:public NodeStatus {
public:
	virtual void DoWork();
	virtual int SetState(Role role);
};

#endif
