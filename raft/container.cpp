#include <container.h>

Container::Container(): m_commitIndex(-1) {}

int Container::GetCommitIndex() const {
	return m_commitIndex;
}
void Container::SetCommitIndex(int commitIndex) {
	m_commitIndex = commitIndex;
}
int Container::GetNewLogTerm() const {
	int last = Size()-1;
	if (last < 0) {
		return -1;
	}
	return m_contents[last].currentTerm;
}
int Container::GetNewLogIndex() const {
	int last = Size()-1;
	if (last < 0) {
		return -1;
	}
	return m_contents[last].index;
}
int Container::Size() const {
	return m_contents.size();
}

