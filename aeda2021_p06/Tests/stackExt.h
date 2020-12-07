# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();

private:
    std::stack<T> m_values;
    std::stack<T> m_minimums;
};


template <class T> 
bool StackExt<T>::empty() const {
	return m_values.empty();
}

template <class T> 
T& StackExt<T>::top() {
    return m_values.top();
}


template <class T> 
void StackExt<T>::pop() {
    if (!m_minimums.empty() && (m_values.top() == m_minimums.top())) m_minimums.pop();
    m_values.pop();
}


template <class T> 
void StackExt<T>::push(const T & val) {
    m_values.push(val);
    if (m_minimums.empty() || val < m_minimums.top()) m_minimums.push(val);
}


template <class T> 
T& StackExt<T>::findMin() {
    return (m_minimums.top());
}

