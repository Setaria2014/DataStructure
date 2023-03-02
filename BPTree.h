#pragma once
const int degree = 4;
struct BPNode {
	int key[degree];
	BPNode* ptr[degree];//��Ҷ�ӽڵ�ĺ���ָ��
	BPNode* parent;
	int cluster[degree];//Ҷ�ӽڵ�ָ��Ĵ��̴�
	int size;//�ڵ������ݸ���
	bool isLeaf;
};

class BPTree {
public:
	BPTree() { root = nullptr; }
	void Insert(int x);
private:
	BPNode* root;
};

void BPTree::Insert(int x) {
	if (root == nullptr) {
		root = new BPNode;
		root->key[0] = x;
		root->isLeaf = true;
		root->size = 1;
		root->parent = nullptr;
	}
	else {

	}
}