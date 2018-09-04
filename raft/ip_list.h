#ifndef __ip_list_h__
#define __ip_list_h__

#include <vector>
#include <string>

class IpList {
public:
	void append(const std::string &ip);
	void erase(const std::string &ip);
	size_t size() const {
		return m_ipList.size();
	}

	std::string &operator[](size_t i) {
		if (i >= size()) {
			abort();
		}
		return m_ipList[i];
	}
private:
	std::vector<std::string> m_ipList;
};


#endif
