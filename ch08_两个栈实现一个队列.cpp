#include <iostream>
#include <stack>
using namespace std;

//���ֵ�����
/*�������ܣ�
1���ڶ���β�����Ԫ��
2��ɾ������ͷ��Ԫ��
*/
class CQueue {
private:
	stack<int>q1;
	stack<int>q2;
public:
	CQueue() {};
	void appendTail(int value) {
		q1.push(value);
	}
	int deleteHead() {
		if (q1.empty() && q2.empty()) {
			return -1;
		}
		if (q2.empty()) {
			while (!q1.empty()) {
				q2.push(q1.top());
				q1.pop();
			}
		}
		int ans = q2.top();
		q2.pop();
		return ans;
	}

};

int main() {
	CQueue c1;
	c1.appendTail(2);
	c1.appendTail(3);
	c1.appendTail(4);
	cout<<"queue head: "<<c1.deleteHead()<<endl;
	c1.appendTail(2);
	c1.appendTail(3);
	c1.appendTail(4);
	cout << "queue head: " << c1.deleteHead() << endl;
	return 0;
}