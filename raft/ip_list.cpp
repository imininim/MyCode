#include <ip_list.h>

using namespace std;

void IpList::append(const std::string &ip) {
	for (auto &m_ip: m_ipList) {
		if (m_ip == ip) {
			return;
		}
	}
	m_ipList.push_back(ip);
}
void IpList::erase(const std::string &ip) {
	for (auto it = m_ipList.begin(); it != m_ipList.end(); ++it) {
		if (ip == *it) {
			m_ipList.erase(it);
			break;
		}
	}
}

