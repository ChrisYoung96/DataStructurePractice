// List.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct Node {
	int value;
	Node *next=NULL;
};

void initList(Node *head) {
	if (head == NULL) {
		cout << "请创建节点" << endl;
	}
	else {
		Node  *ptail = new Node;
		ptail = head;
		int len;
		cout << "输入节点数:" << endl;
		cin >> len;
		head->value = len;
		cout << "输入值：" << endl;
		for (int i = 0; i < len; i++) {
			Node *temp = new Node;
			cin >> temp->value;
			temp->next = NULL;
			ptail->next = temp;
			ptail = temp;
		}
	}
	
}

void printList(Node *head) {
	if (head == NULL) {
		cout << "请创建节点" << endl;
	}
	else {
		Node *temp = new Node;
		temp = head;
		while (temp != NULL) {
			cout << temp->value;
			temp = temp->next;
		}
	}
	
}

void insertNode(Node *head,int pos,int value) {
	if (head == NULL) {
		cout << "请创建节点" << endl;
	}
	else {
		int i, len;
		Node *temp = new Node;
		Node *newnode = new Node;
		temp = head;
		len = head->value;
		newnode->value = value;
		if (pos < len) {
			for (i = 1; i < pos; i++) {
				temp = temp->next;
			}
			newnode->next = temp->next;
			temp->next = newnode;
		}
		else {
			while (temp != NULL) {
				temp = temp->next;
			}
			temp->next = newnode;
		}
		head->value++;
	}
	
}


void deleteNode(Node *head, int pos) {
	if (head == NULL) {
		cout << "请创建节点" << endl;
	}
	else {
		int i;
		Node *temp = head;
		if (pos > head->value) {
			cout << "找不到相应节点！" << endl;
		}
		else {
			if (pos == 1) {
				temp = head->next;
				head->next = temp->next;
				delete(temp);
			}
			else if (pos > 1 && pos < head->value) {
				for (i = 1; i < pos; i++) {
					temp = temp->next;
				}
				temp->next = temp->next->next;
			}
			else {
				for (i = 1; i < pos; i++) {
					temp = temp->next;
				}
				temp->next = NULL;
			}
			head->value--;
		}
	}
	
	
}


void searchNode(Node *head, int value) {
	if (head == NULL) {
		cout << "请创建节点" << endl;
	}
	else {
		Node *temp = head->next;
		int index = 1;
		while (temp != NULL) {
			if (temp->value == value) {
				break;
			}
			else {
				temp = temp->next;
				index++;
			}
		}

		if (temp == NULL) {
			cout << "无此节点" << endl;
		}
		else {
			cout << "位置为" << index << endl;
		}
	}
	
}


int main()
{
	Node *head = new Node;
	int n=1;
	while (n != 0) {
		cout << "选择链表操作：" << endl;
		cout << "1. 创建链表   2.显示链表   3.插入节点   4.删除节点   5.查找节点" << endl;
		cin >> n;
		switch (n) {
		case 1:
			initList(head);
			break;
		case 2:
			printList(head);
			break;
		case 3:
			cout << "请输入插入位置:pos 以及插入值：value" << endl;
			int pos1, value;
			cout << "pos=";
			cin >> pos1;
			cout << " value=";
			cin >> value;
			insertNode(head, pos1, value);
			break;
		case 4:
			cout << "请输入删除位置:pos" << endl;
			int pos2;
			cout << "pos=";
			cin >> pos2;
			deleteNode(head, pos2);
			break;
		case 5:
			cout << "请输入要查找的值：value" << endl;
			int value1;
			cout << "value=";
			cin >> value1;
			searchNode(head, value1);
		}
	}
	
	
	
    return 0;
}

