#include <bits/stdc++.h>
#define order 64

using namespace std;
using namespace std::chrono;

struct node {
    bool leaf;
    int count;
    int keys[order];
    node* pointers[order+1];
    node *next;
    node(bool Leaf) {
        count = 0;
        leaf = Leaf;
        next = NULL;
    }
};

void print_node(node *p) {
    if(p == NULL) {
        cout << "{NULL NODE}" << endl;
        return;
    }
    cout << "{";
    cout << "count : " << p->count << ", ";
    cout << "leaf : " << p->leaf << ", ";
    cout << "keys : ";
    for(int i = 0; i < p->count; i++) {
        cout << p->keys[i] << " ";
    }
    cout << "}\n";
}

void print_tree(node *p, int d) {
    if(p == NULL) {
        return;
    }
    for(int i = 0; i < d; i++) {
        cout << "\t";
    }
    cout  << " ";print_node(p);
    for(int i = 0; i <= p->count; i++) {
        print_tree(p->pointers[i], d+1);
    }
}

void print_leaves(node *p) {

    while(!p->leaf) {
        p = p->pointers[0];
    }

    cout << "[" << endl;
    while(p != NULL) {
        cout << "\t";
        print_node(p);
        p = p->next;
    }
    cout << "]" << endl;
}

void insert_int(node* p, int idx, int x) {
    for(int i = p->count - 1; i >= idx; i--) {
        p->keys[i+1] = p->keys[i];
    }
    p->keys[idx] = x;
}

void insert_pointer(node* p, int idx, node* child) {
    for(int i = p->count; i >= idx; i--) {
        p->pointers[i+1] = p->pointers[i];
    }
    p->pointers[idx] = child;
}

pair<int, node*> insert_helper(int x, node *child, node *p) {
    int idx = 0;
    while(idx < p->count && p->keys[idx] < x) {
        idx++;
    }
    insert_int(p, idx, x);
    
    // int idx = p->count - 1;
    // while(p->keys[idx] >= x) {
    //   p->keys[idx + 1] = p->keys[idx];
    //   idx--;
    // }
    // idx++;
    // p->keys[idx] = x;

    if(!p->leaf) {
        insert_pointer(p, idx + 1, child);
    }
    p->count++;
    if(p->count < order) {
        return {INT_MIN, NULL};
    } else {
        int sz = order / 2;
        node *temp = new node(p->leaf);
        int return_value = p->keys[sz];
        if(p->leaf) { 
            int i;
            for(i = sz; i < p->count; i++) {
                temp->keys[i - sz] = p->keys[i];
            }
            temp->count = i - sz;
        } else {
            int i;
            for(i = sz + 1; i < p->count; i++) {
                temp->keys[i - sz - 1] = p->keys[i];
            }
            temp->count = i - sz - 1;
            for(i = sz + 1; i <= p->count; i++) {
                temp->pointers[i - sz - 1] = p->pointers[i];
            }
        }
        p->count = sz;

        temp->next = temp;
        swap(temp->next, p->next);

        return {return_value, temp};
    }
}

node* search_node(int x, node *p) {
    node *temp = p;
    while(!temp->leaf) {
        if(x <= temp->keys[0]) {
            temp = temp->pointers[0];
        } else if(x > temp->keys[temp->count - 1]) {
            temp = temp->pointers[temp->count];
        } else {
            for(int i = 1; i < temp->count; i++) {
                if(x > temp->keys[i-1] && x <= temp->keys[i]) {
                    temp = temp->pointers[i];
                    break;
                }
            }
        }
    }
    return temp;
}

bool search_tree(int x, node *p) {
    node *temp = search_node(x, p);
    while(temp != NULL && temp->keys[0] <= x) {
        bool res = false;
        for(int i = 0; i < temp->count; i++) {
            if(temp->keys[i] == x) {
                res = true;
            }
        }
        if(res)
            return true;
        temp = temp->next;
    }
    return false;
}

int range_query(int x, int y, node  *p) {
    node *temp = search_node(x, p);
    int i = 0, res = 0;
    bool flag = true;
    while(flag && temp != NULL) {
        for(i = 0; i < temp->count; i++) {
            if(temp->keys[i] >= x) {
                flag = false;
                break;
            }
        }
        if(flag)
            temp = temp->next;
    }
    if(temp == NULL) {
        return 0;
    }
    while(temp != NULL && temp->keys[temp->count - 1] <= y) {
        res += (temp->count - i);
        i = 0;
        temp = temp->next;
    }
    if(temp == NULL) {
        return res;
    }
    for(; i < temp->count; i++) {
        if(temp->keys[i] <= y) {
            res++;
        } else {
            return res;
        }
    }
}

node* insert(int x, node *p) {
    node *child = NULL;
    node *temp = p;
    stack<node*> s;

    // searching the node where the key X belongs
    while(!temp->leaf) {
        s.push(temp);
        if(x <= temp->keys[0]) {
            temp = temp->pointers[0];
        } else if(x > temp->keys[temp->count - 1]) {
            temp = temp->pointers[temp->count];
        } else {
            for(int i = 1; i < temp->count; i++) {
                if(x > temp->keys[i-1] && x <= temp->keys[i]) {
                    temp = temp->pointers[i];
                    break;
                }
            }
        }
    }
    pair<int, node*> pr;
    while(true) {
        pr = insert_helper(x, child, temp);
        if(pr.second == NULL) {
            break;
        }
        if(s.empty())
            break;
        temp = s.top(); s.pop();
        child = pr.second;
        x = pr.first;
    }
    if(s.empty() && pr.second != NULL) {
        node *root = new node(false);
        root->keys[0] = pr.first;
        root->pointers[0] = temp;
        root->pointers[1] = pr.second;
        root->count = 1;
        return root;
    }
    while(!s.empty()) {
        temp = s.top(); s.pop();
    }
    return temp;
}

int main() {
    node *p = new node(true);

    
    return 0;
}
