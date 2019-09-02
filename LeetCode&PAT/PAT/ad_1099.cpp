#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct node{
    int data;
    node *left,*right;
};

vector<node> tree;
vector<int> vec;

int data_index = 0;
int N;

void trav_in(node* a){
    if(a == nullptr) return;
    trav_in(a->left);
    a->data = vec[data_index++];
    trav_in(a->right);
}

void trav_level(node * a) {
	queue<node*> que;
	que.push(a);
	int num = 0;
	while (!que.empty()) {
		auto ptr = que.front();
		cout << ptr->data;
		if ((num++) != N - 1) cout << ' ';
		que.pop();
		if (ptr->left)
			que.push(ptr->left);
		if (ptr->right)
			que.push(ptr->right);
	}
}

int main(){
    cin>>N;
    tree.resize(N);
    vec.resize(N);
    for(int i=0; i<N; ++i){
        int l,r;
        cin>>l>>r;
        tree[i].left  = (l==-1) ? nullptr : &tree[l];
        tree[i].right = (r==-1) ? nullptr : &tree[r];
    }

    for(int i=0; i<N; ++i){
        cin>>vec[i];
    }
    sort(vec.begin(), vec.end());
    trav_in(&tree[0]);
    trav_level(&tree[0]);
    return 0;
}