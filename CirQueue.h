#pragma once
#include <iostream>
template <class T>
class CirQueue {
private:
	int front;
	int rear;
	int flag;
	int length;
	T data[MaxSize];
public:
	void EnCirQueue(T x);
	T DeCirQueue();
	void Print();
	void Isfull();
	CirQueue(int size);
	CirQueue(T* data, int n);
};

template <typename T>
CirQueue<T>::CirQueue(int size) {
	front = 0;
	rear = 0;
	flag = 0;
	length = size;
}

template <typename T>
CirQueue<T>::CirQueue(T* data, int n) {
	front = 0;
	rear = 0;
	flag = 0;
	length = n;
	for (int i = 0; i < n; i++) {
		EnCirQueue(data[i]);
	}
}

template <typename T>
void CirQueue<T>::EnCirQueue(T x) {  
	data[rear] = x;
	if (rear + 1 == length) { rear = 0; }
	else { rear += 1; }
	if (front == rear) flag = 1;//ֻ����ӲŻ�ʹ���б���
}

template <typename T>
T CirQueue<T>::DeCirQueue() {
	T x = data[front];
	if (front != rear || flag == 1) {//����Ϊ�������ķ�
		front += 1;
		return x;
	}
	if (front != rear) flag = 0;//���ӻ�ʹ�����б�ɷ�������
	return 0;
}

template <typename T>
void CirQueue<T>::Print() {
	std::cout << "Queue:" << ' ';
	if (front != rear || flag == 1) {
		int a = front;
		int n = 0;
		if (rear > front) n = rear - front;
		if (rear <= front) n = rear + length - front;
		for (int i = 0; i < n; i++) {
			std::cout << data[a] << ' ';
			if (a == length - 1) { a = 0; }
			else { a += 1; }
		}
		std::cout << std::endl;
	}
}

template <typename T>
void CirQueue<T>::Isfull() {
	if (flag == 1 && front == rear)std::cout << "����Ϊ��" << std::endl;
	else std::cout << "���з���" << std::endl;
}