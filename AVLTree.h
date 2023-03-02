#pragma once
template <typename T>
struct AVLNode {
	T data;
	AVLNode<T>* lchild, * rchild;
	int factor;//ƽ������
};

class AVLTree {
public:
	AVLTree(int a[], int n);
	~AVLTree() { Release(root); }
	AVLNode<int>* Insert(int x) { return Insert(root, x); }
	void Delete(AVLNode<int>* p, AVLNode<int>* f);
	AVLNode<int>* Search(int k) { return Search(root, k); }
	void PreOrder() { std::cout << "AVLTree:" << ' '; PreOrder(root); std::cout << std::endl; }
	void InOrder() { std::cout << "AVLTree:" << ' '; InOrder(root); std::cout << std::endl; }
private:
	AVLNode<int>* Insert(AVLNode<int>* avlt, int x);
	AVLNode<int>* Search(AVLNode<int>* avlt, int k);
	void Release(AVLNode<int>* avlt);
	void PreOrder(AVLNode<int>* avlt);
	void InOrder(AVLNode<int>* avlt);
	int Depth(AVLNode<int>* avlt);
	int getFactor(AVLNode<int>* avlt);
	void refreshFactors(AVLNode<int>*& avlt);
	void FactorIsTwo(AVLNode<int>*& avlt, AVLNode<int>*& p);
	void getFather(AVLNode<int>*& avlt, AVLNode<int>*& f, int x);
	void LLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void RRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void LRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void RLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f);
	void treeAdjust(AVLNode<int>*& avlt);
	AVLNode<int>* root;
};


AVLTree::AVLTree(int a[], int n) {
	root = nullptr;
	for (int i = 0; i < n; i++) { root = Insert(root, a[i]); treeAdjust(root); }
}

void AVLTree::Release(AVLNode<int>* avlt) {
	if (avlt == nullptr)return;
	else {
		Release(avlt->lchild);
		Release(avlt->rchild);
		delete avlt;
	}
}

void AVLTree::PreOrder(AVLNode<int>* avlt) {
	if (avlt == nullptr) return;
	else {
		std::cout << avlt->data << " ";
		PreOrder(avlt->lchild);
		PreOrder(avlt->rchild);
	}
}

void AVLTree::InOrder(AVLNode<int>* avlt) {
	if (avlt == nullptr) return;
	else {
		InOrder(avlt->lchild);
		std::cout << avlt->data << " ";
		InOrder(avlt->rchild);
	}
}

AVLNode<int>* AVLTree::Search(AVLNode<int>* avlt, int k) {
	if (avlt == nullptr) return nullptr;
	if (avlt->data == k) return avlt;
	else if (avlt->data > k) return Search(avlt->lchild, k);
	else return Search(avlt->rchild, k);
}

AVLNode<int>* AVLTree::Insert(AVLNode<int>* avlt, int x) {
	if (avlt == nullptr) {
		AVLNode<int>* s = new AVLNode<int>;
		s->data = x;
		s->lchild = s->rchild = nullptr;
		avlt = s;
	}
	else if (avlt->data > x) avlt->lchild = Insert(avlt->lchild, x);
	else avlt->rchild = Insert(avlt->rchild, x);
	return avlt;
}

void AVLTree::Delete(AVLNode<int>* p, AVLNode<int>* f) {
	if ((p->lchild == nullptr) && (p->rchild == nullptr)) {
		f->lchild = nullptr; delete p; return;
	}
	if (p->rchild == nullptr) {
		f->lchild = p->lchild; delete p; return;
	}
	if (p->lchild == nullptr) {
		f->lchild = p->rchild; delete p; return;
	}
	AVLNode<int>* par = p, * s = p->rchild;
	while (s->lchild != nullptr) {
		par = s;
		s = s->lchild;
	}
	p->data = s->data;
	if (par == p)par->rchild = s->rchild;
	else par->lchild = s->rchild;
	delete s;
}

int AVLTree::Depth(AVLNode<int>* avlt){
	if (avlt == nullptr) return 0;
	else {
		int m = Depth(avlt->lchild);
		int n = Depth(avlt->rchild);
		if (m > n) return m + 1;
		else return n + 1;
	}
}
//�����нڵ��ƽ������
int AVLTree::getFactor(AVLNode<int>* avlt){
	int m = 0, n = 0;
	if (avlt != nullptr){
		m = Depth(avlt->lchild);
		n = Depth(avlt->rchild);
	}
	return m - n;
}
//ˢ�����е�ÿ���ڵ��ƽ������
void AVLTree::refreshFactors(AVLNode<int>*& avlt){
	if (avlt != nullptr){
		avlt->factor = getFactor(avlt);
		refreshFactors(avlt->lchild);
		refreshFactors(avlt->rchild);
	}
}
//���ƽ������Ϊ2��-2�Ľڵ�
void AVLTree::FactorIsTwo(AVLNode<int>*& avlt, AVLNode<int>*& p){
    if (avlt != nullptr){
		if (avlt->factor == 2 || avlt->factor == -2) {
			p = avlt;
		}
        FactorIsTwo(avlt->lchild, p);
        FactorIsTwo(avlt->rchild, p);
    }
}
//�ҵ�����Ϊx�Ľ��ĸ��ڵ㲢�洢��f��
void AVLTree::getFather(AVLNode<int>*& avlt, AVLNode<int>*& f, int x){
	if (avlt != nullptr){
		if (avlt->lchild != nullptr){
			if (avlt->lchild->data == x) f = avlt;
		}
		if (avlt->rchild != nullptr){
			if (avlt->rchild->data == x) f = avlt;
		}
		getFather(avlt->lchild, f, x);
		getFather(avlt->rchild, f, x);
	}
}
//LL����
void AVLTree::LLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f){
    AVLNode<int>* r;
    if (avlt == p){				//���ڵ㼴Ϊ��С��ƽ�������ĸ��ڵ�
        avlt = p->lchild;        //��p����������Ϊ�µĸ��ڵ�
        r = avlt->rchild;
        avlt->rchild = p;        //��p��Ϊ�����ӵ��Һ���
        p->lchild = r;			//��pԭ�������ӵ��Һ���������p������
    }
    else {//��С��ƽ�������ĸ��ڵ㲻�Ǹ��ڵ�
        if (f->lchild == p){    //f��������p
            f->lchild = p->lchild;        //��p����������Ϊ�µĸ��ڵ�
            r = f->lchild->rchild;			//����
            f->lchild->rchild = p;        //��p��Ϊ�����ӵ��Һ���
            p->lchild = r;        //��pԭ�������ӵ��Һ���������p������
        }
        if (f->rchild == p){    //f���Һ�����p
            f->rchild = p->lchild;        //��p����������Ϊ�µĸ��ڵ�
            r = f->rchild->rchild;			//����
            f->rchild->rchild = p;        //��p��Ϊ�����ӵ��Һ���
            p->lchild = r;        //��pԭ�������ӵ��Һ���������p������
        }
    }
}
//LR����
void AVLTree::LRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f) {
    AVLNode<int>* l, * r;
    if (avlt == p){					//avlt->factor==2 && avlt->lchild->factor!=2
        avlt = p->lchild->rchild;    //��p�����ӵ��Һ�������Ϊ�µĸ��ڵ�
        r = avlt->rchild;
        l = avlt->lchild;
        avlt->rchild = p;
        avlt->lchild = p->lchild;
        avlt->lchild->rchild = l;
        avlt->rchild->lchild = r;
    }
    else {
        if (f->rchild == p){    //f���Һ�����p
            f->rchild = p->lchild->rchild;    //��p�����ӵ��Һ�������Ϊ�µĸ��ڵ�
            r = f->rchild->rchild;
            l = f->rchild->lchild;
            f->rchild->rchild = p;
            f->rchild->lchild = p->lchild;
            f->rchild->lchild->rchild = l;
            f->rchild->rchild->lchild = r;
        }
        if (f->lchild == p) {     //f��������p
            f->lchild = p->lchild->rchild;    //��p�����ӵ��Һ�������Ϊ�µĸ��ڵ�
            r = f->lchild->rchild;
            l = f->lchild->lchild;
            f->lchild->rchild = p;
            f->lchild->lchild = p->lchild;
            f->lchild->lchild->rchild = l;
            f->lchild->rchild->lchild = r;
        }
    }
}
//RL����
void AVLTree::RLAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f){
    AVLNode<int>* l, * r;
    if (avlt == p) {           //avlt->factor==-2 && avlt->rchild->factor!=-2
        avlt = p->rchild->lchild;
        r = avlt->rchild;
        l = avlt->lchild;
        avlt->lchild = p;
        avlt->rchild = p->rchild;
        avlt->lchild->rchild = l;
        avlt->rchild->lchild = r;
    }
    else {
        if (f->rchild == p){    //f���Һ�����p
            f->rchild = p->rchild->lchild;
            r = f->rchild->rchild;
            l = f->rchild->lchild;
            f->rchild->lchild = p;
            f->rchild->rchild = p->rchild;
            f->rchild->lchild->rchild = l;
            f->rchild->rchild->lchild = r;
        }
        if (f->lchild == p){     //f��������p
            f->lchild = p->rchild->lchild;
            r = f->lchild->rchild;
            l = f->lchild->lchild;
            f->lchild->lchild = p;
            f->lchild->rchild = p->rchild;
            f->lchild->lchild->rchild = l;
            f->lchild->rchild->lchild = r;
        }
    }
}
//RR����
void AVLTree::RRAdjust(AVLNode<int>*& avlt, AVLNode<int>*& p, AVLNode<int>*& f) {
    AVLNode<int>* l;
    if (avlt == p) {             //avlt->factor==-2 && avlt->rchild->factor!=-2
        avlt = p->rchild;        //��p���Һ�������Ϊ�µĸ��ڵ�
        l = avlt->lchild;
        avlt->lchild = p;        //��p��Ϊ���Һ��ӵ�����
        p->rchild = l;        //��pԭ�����Һ��ӵ�����������p���Һ���
    //ע��:p->rchild->factor==0����ڵ�ʱ�ò��ϣ�ɾ���ڵ�ʱ����
    }
    else {
        if (f->rchild == p){     //f���Һ�����p
            f->rchild = p->rchild;        //��P���Һ�������Ϊ�µĸ��ڵ�
            l = f->rchild->lchild;
            f->rchild->lchild = p;        //��p��Ϊ���Һ��ӵ�����
            p->rchild = l;        //��pԭ�����Һ��ӵ�����������p���Һ���
        }
        if (f->lchild == p){     //f��������p
            f->lchild = p->rchild;        //��p����������Ϊ�µĸ��ڵ�
            l = f->lchild->lchild;
            f->lchild->lchild = p;        //��p��Ϊ�����ӵ�����
            p->rchild = l;        //��pԭ�����Һ��ӵ�����������p���Һ���
        }
    }
}

void AVLTree::treeAdjust(AVLNode<int>*& avlt){
	AVLNode<int>* f = nullptr, * p = nullptr;
	refreshFactors(avlt);
	FactorIsTwo(avlt, p);
	if(p != nullptr) getFather(avlt,f, p->data);
	while (p != nullptr){
		refreshFactors(avlt);
		if (p->factor == 2 && (p->lchild->factor == 1 || p->lchild->factor == 0)) {
			LLAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		else if (p->factor == 2 && p->lchild->factor == -1){
			LRAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		else if (p->factor == -2 && p->rchild->factor == 1){
			RLAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		else if (p->factor == -2 && (p->rchild->factor == -1 || p->rchild->factor == 0)){
			RRAdjust(avlt, p, f);
			refreshFactors(avlt);
		}
		f = nullptr;
		p = nullptr;
		FactorIsTwo(avlt, p);
		if (p != nullptr) getFather(avlt, f, p->data);
	}
}