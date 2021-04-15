// leetcode 430.扁平化多级双向链表 中等 3/5
// 把这个链表旋转一下，可以看成一棵二叉树，前向遍历存入一个vector中，时间复杂度：O（n），空间：O（n）

// leetcode 61.旋转链表 中等 5/5
// 对移动步长的理解,考虑多种corner
// case(空结点,一个结点,k=0),计算出链表长度,找到倒数第k和第k+1个结点作为首尾结点
/*
ListNode* rotateRight(ListNode* head, int k) {
    // 空结点，一个结点，向前走0步，直接返回
    if (head == NULL || head->next == NULL || k == 0) return head;
    // 获取链表长度，并将链表首尾相连
    int length = 1;
    ListNode* cur = head;
    while (cur->next != NULL) {
        length++;
        cur = cur->next;
    }
    // k正好是长度的整数倍，直接返回
    if (k % length == 0) return head;

    cur->next = head;
    // 倒数第k个点为首结点，第k+1个为尾结点
    k = k % length;
    for (int i = 0; i < length - k; i++) cur = cur->next;

    ListNode* new_head = cur->next;
    cur->next = NULL;
    return new_head;
}
*/

// leetcode 445.两数相加2 中等 5/5
// 两个问题:注意要逆序输出,所以要使用头插法插入新结点;
// 循环结束时如果进位是1,要额外加一个结点

// leetcode 143.重排链表 中等 4/5
// 首先使用快慢指针找中点拆成两端(下中点),第二端逆序,设置一个dummy结点,用一个while循环插入,最后将head置为dummy结点的next,
// I CAN DO THIS

// leetcode 82.删除排序链表中的重复元素2 中等 5/5
// 这类删除问题一般要利用一个dummy结点,这个题难点在于判断0个重复和多个重复的问题
/*
ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL) return NULL;

    ListNode* dummy = new ListNode(-1);
    ListNode* pre = dummy;
    dummy->next = head;

    while (pre->next) {
        int num = 0;
        ListNode* tmp = pre->next;
        while (tmp->next && tmp->next->val == tmp->val) {
            num++;
            tmp = tmp->next;
        }
        // 无重复结点
        if (num == 0)
            pre = pre->next;
        // 有重复结点
        else
            pre->next = tmp->next;
    }

    return dummy->next;
}
*/

// leetcode 109.有序链表转换二叉搜索树 中等 4/5
// 思路是找链表的中点,快慢指针,然后中点左右各自递归,一个前序遍历
// 或者用一个数组存取所有的结点
// I CAN DO THIS

// leetcode 707.设计链表 中等 4/5
// 还是要使用dummy结点用来保持一致性,注意在插入和删除的时候索引的开始位置
// I CAN DO THIS
class MyLinkedList {
   public:
    struct Node {
        int val;
        Node* next;
        Node* prev;
        Node(int v) : val(v), next(NULL), prev(NULL) {}
    };
    int size;
    Node* head;
    Node* tail;
    /** Initialize your data structure here. */
    MyLinkedList() : size(0), head(NULL), tail(NULL) {
        // 两个dummy结点用来保持一致性
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
    }

    /** Get the value of the index-th node in the linked list. If the index is
     * invalid, return -1. */
    int get(int index) {
        // 索引无效
        if (index < 0 || index > size - 1) return -1;
        // head -> next 才是第0个结点
        Node* tmp = head->next;
        for (int i = 0; i < index; i++) tmp = tmp->next;
        return tmp->val;
    }

    /** Add a node of value val before the first element of the linked list.
     * After the insertion, the new node will be the first node of the linked
     * list. */
    void addAtHead(int val) {
        Node* tmp = new Node(val);
        tmp->next = head->next;
        head->next = tmp;
        size++;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node* tmp = new Node(val);
        Node* cur = head;
        while (cur->next != tail) cur = cur->next;
        cur->next = tmp;
        tmp->next = tail;
        size++;
    }

    /** Add a node of value val before the index-th node in the linked list. If
     * index equals to the length of linked list, the node will be appended to
     * the end of linked list. If index is greater than the length, the node
     * will not be inserted. */
    void addAtIndex(int index, int val) {
        // index = 链表长度
        if (index == size) {
            addAtTail(val);
            return;
        }
        // index <= 0
        if (index <= 0) {
            addAtHead(val);
            return;
        }
        // 无效索引
        if (index > size) return;
        // 一般情况, 这个起始位置从head开始,因为可能要新增index = 0的结点
        Node* tmp = head;
        for (int i = 0; i < index; i++) tmp = tmp->next;
        Node* new_node = new Node(val);
        new_node->next = tmp->next;
        tmp->next = new_node;
        size++;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        // 无效索引
        if (index < 0 || index > size - 1) return;

        // 这个起始位置从head开始,因为可能要删除index = 0的结点
        Node* tmp = head;
        for (int i = 0; i < index; i++) tmp = tmp->next;
        Node* next = tmp->next;
        tmp->next = next->next;
        delete next;
        size--;
    }
};