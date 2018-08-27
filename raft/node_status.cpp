#include <node_status.h>

void SleepStatus::DoWork() {

}

int SleepStatus::SetState(Role role) {
	switch(role) {
		case Role::slave:
			break;
		default:
			break;
	}
}

void SlaveStatus::DoWork() {

}

int SlaveStatus::SetState(Role role) {
	switch(role) {
		case Role::campaigner:
			break;
		case Role::sleep:
			break;
		default:
			break;
	}
}

void CampaignerStatus::DoWork() {

}

int CampaignerStatus::SetState(Role role) {
	switch(role) {
		case Role::slave:
			break;
		case Role::sleep:
			break;
		case Role::master:
			break;
		default:
			break;
	}
}

void MasterStatus::DoWork() {

}

int MasterStatus::SetState(Role role) {
	switch(role) {
		case Role::slave:
			break;
		case Role::sleep:
			break;
		case Role::master:
			break;
		default:
			break;
	}
}


