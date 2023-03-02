#pragma once
#include <iostream>
#include <algorithm>
template <class T>
class AoeGraph {
public:
	AoeGraph(T a[], int n, int e, int edges[][3]);
	void TopSort();
	void CriticalPath();
private:
	VertexNode<T> adjlist[MaxVertex];//�ڽӱ�
	EdgeGraphNode edge[MaxEdge];//�߼�����
	int vertexNum, edgeNum;
	int ve[MaxVertex], vl[MaxVertex], ee[MaxEdge], el[MaxEdge];
};


template <typename T>
AoeGraph<T>::AoeGraph(T a[], int n, int e, int edges[][3]) {
	int i, j, k ,m;
	EdgeNode* s = nullptr,* t = nullptr;
	vertexNum = n; edgeNum = e;
	for (k = 0; k < vertexNum; k++) {
		adjlist[k].vertex = a[k];
		adjlist[k].firstEdge = nullptr;
		adjlist[k].firstTail = nullptr;
		adjlist[k].in = 0;
		ve[k] = 0;
		vl[k] = 0;
	}
	for (m = 0; m < edgeNum; m++) {
		i = edges[m][0];
		j = edges[m][1];//��iָ��j
		s = new EdgeNode;
		s->adjvex = j;
		s->next = adjlist[i].firstEdge;
		adjlist[i].firstEdge = s;
		t = new EdgeNode;
		t->adjvex = i;
		t->last = adjlist[j].firstTail;
		adjlist[j].firstTail = t;
		s->weight = edges[m][2];
		t->weight = edges[m][2];
		adjlist[j].in++;
		edge[m].from = edges[m][0];
		edge[m].to = edges[m][1];
		edge[m].weight = edges[m][2];
		ee[m] = 0;
		el[m] = 0;
	}
}

template <typename T>
void AoeGraph<T>::TopSort() {
	int i, j, k, count = 0;
	int S[MaxVertex], top = -1;
	EdgeNode* p = nullptr;
	for (i = 0; i < vertexNum; i++)
		if (adjlist[i].in == 0)S[++top] = i;
	while (top != -1) {
		j = S[top--];
		std::cout << adjlist[j].vertex << "->";
		count++;
		p = adjlist[j].firstEdge;
		while (p != nullptr) {
			k = p->adjvex;
			adjlist[k].in--;
			if (adjlist[k].in == 0)S[++top] = k;
			p = p->next;
		}
	}
	if (count < vertexNum) std::cout << "�л�·\n";
	else std::cout << "#\n";
}

template <typename T>
void AoeGraph<T>::CriticalPath() {
	int S[MaxVertex], Topo[MaxVertex], i, j, k, m, w,
		count = 0, top = -1, topo_top = -1, ve_max = 0;
	EdgeNode* p = nullptr;
	//��������
	for (i = 0; i < MaxVertex; i++) {//��ʼ��ve[]
		ve[i] = 0;
		if (adjlist[i].in == 0) S[++top] = i;
	}
	while (top != -1) {
		j = S[top--];
		Topo[++topo_top] = j;
		count++;
		p = adjlist[j].firstEdge;//jΪ��p�����
		while (p != nullptr) {//��ʼ����һ����ȱ�Ϊ0�Ľ����ڽӱ�
			k = p->adjvex;//kΪ��p���յ�
			adjlist[k].in--;
			if (ve[k] < p->weight + ve[j]) ve[k] = p->weight + ve[j]; 

			//ve[k]Ϊ��kΪ�յ�ı�p���棬p->weight + ve[j]�����ֵ
			if (adjlist[k].in == 0) { 
				S[++top] = k; 
			}
			p = p->next;
		}
	}
	if (count < vertexNum) {
		std::cout << "�л�·\n";
		return;
	}

	//����������
	ve_max = ve[Topo[vertexNum - 1]];
	for (i = 0; i < MaxVertex; i++) vl[i] = ve_max;//��ʼ��vl[]
	while (topo_top != -1) {
		j = Topo[topo_top--];//jΪ��p���յ�
		p = adjlist[j].firstTail;//pΪ���ڽӱ��е���Ԫ��
		while (p != nullptr) {
			k = p->adjvex;//kΪ��p�����
			if (vl[k] > vl[j] - p->weight) vl[k] = vl[j] - p->weight;
			//vl[k]Ϊ��jΪ�յ�ı�p���棬vl[j] - p->weight����Сֵ
			p = p->last;
		}
	}

	//����ee[]
	for (i = 0; i < edgeNum; i++) {
		k = edge[i].from;
		ee[i] = ve[k];
	}

	//����el[]
	for (i = 0; i < edgeNum; i++) {
		j = edge[i].to;
		w = edge[i].weight;
		el[i] = vl[j] - w;
	}
	for (m = 0; m < edgeNum; m++) {
		if (ee[m] == el[m]) {
			std::cout << adjlist[edge[m].from].vertex << "->" 
				<< adjlist[edge[m].to].vertex << "  ";
		}
	}
}