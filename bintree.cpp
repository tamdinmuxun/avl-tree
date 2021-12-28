#include <iostream>
#include <string>

using namespace std;

struct tree{
    int val, h;
    tree* left, *right;

//    tree(){
//        h = 0;
//        left = nullptr;
//        right = nullptr;
//    }
    tree(int x){
        val = x;
        h = 1;
        left = nullptr;
        right = nullptr;
    }

    int dist(); //ok
    void fix(); //ok
    tree* insert(int x);//ok
    tree* rrotate();//ok
    tree* lrotate();//ok
    tree* rotate();//ok
    tree* find(int x);//ok
    tree* min();//ok
    tree* pop_min(); //ok
    tree* pop(int x);
    void print();
};

int height(tree* p){
    if (p == nullptr) return 0;
    else return p->h;
}

int tree::dist() {
    return height(right) - height(left);
}
void tree::fix() {
    h = max(height(right), height(left)) + 1;
}
tree* tree:: rrotate(){
    tree* q = left;
    left = left->right;
    q->right = this;
    this->fix();
    q->fix();
    return q;
}

tree* tree:: lrotate(){
    tree* q = right;
    right = right->left;
    q->left = this;
    this->fix();
    q->fix();
    return q;
}

tree* tree::rotate() {
    fix();
    if (dist() == 2){
        if (right->dist() < 0){
            right = right->rrotate();
        }
        return lrotate();
    }else if (dist() == -2){
        if (left->dist() > 0){
            left = left->lrotate();
        }
        return rrotate();
    }
    return this;
}

tree* tree::insert(int x) {
    if (x < val){
        if (left != nullptr) left = left->insert(x);
        else {
            left = new tree(x);
        }
    }else{
        if (right != nullptr) right = right->insert(x);
        else {
            right = new tree(x);
        }
    }
    return rotate();
}

tree *tree::find(int x) {
    if (x < val){
        return left->find(x);
    }else if (x > val){
        return right->find(x);
    }
    return this;
}

tree* tree::min() {
    if (left == nullptr) return this;
    return left->min();
}


tree* tree::pop_min() {
    if (left == nullptr) {
        delete this;
        return right;
    }
    left = left->pop_min();
    return rotate();
}

tree* tree::pop(int x) {
    if (x < val) {
        if (left != nullptr)left = left->pop(x);
        else return nullptr;
    }else if (x > val){
        if (right != nullptr){
            right = right->pop(x);
        }else return nullptr;
    }else{
        auto l = left;
        auto r = right;
        delete this;
        if (r == nullptr) return l;
        auto m = r->min();
        m->right = r->pop_min();
        m->left = l;
        return m->rotate();
    }
    return rotate();
}

void tree::print() {
    cout << this << ' ' << val << ' ' << h << ' ' <<  left << ' ' << right << '\n';
    if (left != nullptr) left->print();
    if (right != nullptr) right->print();
}



int main(){
    string ans;
    tree* root = nullptr;
    while (true){
        cout << "choose command\ninsert\nfind minimum \nfind \npop minimum \npop \nprint \nexit\n";
        getline(cin, ans);
        if (ans == "exit"){
            break;
        }else if (ans == "insert"){
            int x;
            cin >> x;
            if (root == nullptr){
                root = new tree(x);
            }else root = root->insert(x);
        }else if (ans == "find minimum"){
            cout << root->min() << '\n';
        }else if (ans == "find"){
            int x;
            cin >> x;
            cout << root->find(x) << '\n';
        }else if (ans == "pop minimum"){
            if (root != nullptr) root = root->pop_min();
        }else if (ans == "pop"){
            int x;
            cin >> x;
            root = root->pop(x);
        }else if (ans == "print"){
            if (root) root->print();
            cout << '\n';
        }
    }
    return 0;
}