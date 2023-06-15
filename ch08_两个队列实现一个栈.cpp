#include<iostream>
#include <queue>
using namespace std;

/*
1、向栈中放入元素
2、删除栈顶元素
*/
class CStack {
private:
	queue<int>q1;
	queue<int>q2;
public:
	CStack() {};
	void push(int x) {
		//保证队头元素的位置不变，来回捣腾
		q2.push(x);
		while (!q1.empty()) {
			q2.push(q1.front());
			q1.pop();
		}
		swap(q1, q2);
	}
	int top() {
		return q1.front();
	}
	int pop() {
		int tmp = q1.front();
		q1.pop();
		return tmp;
	}
	bool empty() {
		return q1.empty();
	}
};

int main() {
	CStack s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	cout << "s1.pop : " << s1.pop() << endl;
	cout << "s1.pop : " << s1.pop() << endl;
	cout << "s1.pop : " << s1.pop() << endl;


}