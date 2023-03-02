#pragma once
#include <iostream>
template <typename T>
struct LinkQueueNode {
	T data;
	LinkQueueNode* next;
};
template <class T>
class LinkQueue {
private:
	LinkQueueNode<T>* rear;
	int length;
public:
	void EnLinkQueue(T x);
	T DeLinkQueue();
	void Print();
	LinkQueue();
};
template <typename T>
LinkQueue<T>::LinkQueue()
{
	this->rear = nullptr;
	length = 0;
}
template <typename T>
void LinkQueue<T>::EnLinkQueue(T x)
{
	LinkQueueNode<T>* newnode = new LinkQueueNode<T>;
	LinkQueueNode<T>* p = this->rear;
	newnode->data = x;
	this->rear = newnode;
	if (this->length == 0) {
		newnode->next = newnode;
	}
	if (this->length >= 1) { 
		LinkQueueNode<T>* q = p->next;
		p->next = newnode;
		newnode->next = q;
	}
	this->length += 1;
}
template <typename T>
T LinkQueue<T>::DeLinkQueue()
{
	if (this->length >= 1) {
		T x = this->rear->next->data;//��һ�����ݽڵ��ֵ
		LinkQueueNode<T>* p = this->rear->next;//��һ�����ݽڵ�ĵ�ַ
		LinkQueueNode<T>* q = this->rear->next->next;//�ڶ������ݽڵ�ĵ�ַ
		this->rear->next = q;
		this->length -= 1;
		delete p;
		return x;
	}
	return 0;
}
template <typename T>
void LinkQueue<T>::Print()
{
	std::cout << "��ǰ����Ϊ:" << std::endl;
	if (this->length >= 1) {
		LinkQueueNode<T>* p = this->rear->next;
		for (int i = 0; i < this->length; i++) {
			std::cout << p->data << ' ';
			p = p->next;
		}
		std::cout << std::endl;
	}
}