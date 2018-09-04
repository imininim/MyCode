#ifndef __container_h__
#define __container_h__

#include <vector>
#include <string>

class Content {
public:
	Content():index(-1), currentTerm(-1) {}
	int index;
	int currentTerm;
	std::string content;
};

class Container {
public:
	Container();
	int GetNewLogTerm() const;
	int GetNewLogIndex() const;
	int GetLogTermFromIndex(int index) const {
		for (auto rit = m_contents.rbegin(); rit != m_contents.rend(); ++rit) {
			if (rit->index == index) {
				return rit->currentTerm;
			}
		}
		return -1;
	}
	int GetCommitIndex() const;
	void SetCommitIndex(int commitIndex);
	int Size() const;
	void AppendContent(const Content &content) {
		m_contents.push_back(content);
	}
	void DeleteContent(int index) {
		for (auto rit = m_contents.rbegin(); rit != m_contents.rend(); ) {
			if (rit->index == index) {
				break;
			}
			rit = std::vector<Content>::reverse_iterator(m_contents.erase((++rit).base()));
		}
	}
private:
	std::vector<Content> m_contents;
	int m_commitIndex;
};

#endif
