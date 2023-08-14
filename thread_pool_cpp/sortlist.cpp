#include<iostream>
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int _val, ListNode* _next):val(_val), next(_next){}
    ListNode(int _val):val(_val), next(nullptr) {};
};
ListNode* find_mid(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* fast = head->next;
    ListNode* slow = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
ListNode* sortList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* mid = find_mid(head);
    ListNode* list1 = head;
    ListNode* list2 = mid->next;
    //std::cout << mid->val << std::endl;
    mid->next = nullptr;
    list1 = sortList(list1);
    list2 = sortList(list2);
    ListNode* hair = new ListNode(0);
    ListNode* result = hair;
    while (list1 && list2) {
        if (list1->val < list2->val) {
            hair->next = list1;
			list1 = list1->next;
        } else {
            hair->next = list2;
			list2 = list2->next;
        }
        hair = hair->next;
    }
    if (list1) {
        hair->next = list1;
    }
    if (list2) {
        hair->next = list2;
    }
    return result->next;
}
int main() {
    ListNode* head = new ListNode(4, nullptr);
    ListNode* start = head;
    head->next = new ListNode(2, nullptr);
    head = head->next;
    head->next = new ListNode(1, nullptr);
    head = head->next;
    head->next = new ListNode(3, nullptr);
    ListNode* result = sortList(start);
    while (result) {
        std::cout << result->val <<std::endl;
        result = result->next;
    }
    return 0;
}
