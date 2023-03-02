#pragma once
class HashTable {
public:
	HashTable();
	~HashTable() {};//��������Ϊ��
	int Insert(int k);
	int Delete(int k);//����ɾ��
	int Search(int k);
private:
	int H(int k);//��ϣ����
	int ht[MaxSize];//�չ�ϣ��
	int flag[MaxSize];//���
};

HashTable::HashTable() {
	for (int i = 0; i < MaxSize; i++) { 
		ht[i] = 0; flag[i] = 0; 
	}
}

int HashTable::H(int k) {
	int h = k % 47;
	return h;
}

int HashTable::Search(int k) {
	int i, j = H(k);
	i = j;
	while (flag[i] == 1) {
		if (ht[i] == k) return i;
		else i = (i + 1) % MaxSize;
	}
	return -1;
}

int HashTable::Insert(int k) {
	int result = Search(k);
	if (result == -1) {
		int j = H(k);
		int m = j;
		while (ht[j] != 0 && (j + 1) % MaxSize != m) {
			j = (j + 1) % MaxSize;
		}
		if ((j + 1) % 11 == m && ht[j] != 0) {
			return -1;//��ϣ������
		}
		if(ht[j] == 0){
			ht[j] = k;
			flag[j] = 1;
			return j;
		}
	}
	else return -1;
}

int HashTable::Delete(int k) {
	int result = Search(k);
	if (result != -1) {
		ht[result] = 0;
		if (H(ht[(result + 1) % MaxSize]) == 0 && flag[result] == 0) 
			flag[result] = 0;
		//����ɾ������δ������ͻ���ڳ�ͻ����ĩβ����flag����
		//�Է�ֹ�������ݴ���̫���Ժ�flagȫ����Ϊ1
		return k;
	}
	else return -1;
}