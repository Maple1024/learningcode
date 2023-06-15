/*
青蛙跳台阶
*/
class Solution {
    int MOD = 1e9 + 7;
public:
    int numWays(int n) {
        int a = 1, b = 1, c = 1;
        if (n == 0 || n == 1) {
            return 1;
        }
        for (int i = 2; i <= n; i++) {
            c = (a + b) % MOD;
            a = b;
            b = c;
        }
        return c;
    }
};
/*
反转链表
*/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* tmp = nullptr;
        ListNode* ptr = head;
        while (ptr) {
            head = head->next;
            ptr->next = tmp;
            tmp = ptr;
            ptr = head;
        }
        return tmp;
    }
};