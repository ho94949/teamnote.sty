int good_random();

struct Node {
  Node *L, *R;
  ll val, sum;
  int y, sz, rev;
  Node() {}
  Node(ll _val) : val(_val), sum(_val) {
    y = good_random(), sz = 1, rev = 0, L = R = NULL;
  }
};

int good_random() { return (rand() << 16) | rand(); }

inline void push(Node *T) {
  if (T == NULL)
    return;
  if (T->rev) {
    if (T->L != NULL)
      T->L->rev ^= 1;
    if (T->R != NULL)
      T->R->rev ^=1;
    swap(T->L, T->R);
    T->rev ^= 1;
  }
}

inline void recalc(Node *T) {
  if (T == NULL)
    return;
  T->sz = 1;
  T->sum = T->val;
  if (T->L != NULL) {
    T->sz += T->L->sz;
    T->sum += T->L->sum;
  }
  if (T->R != NULL) {
    T->sz += T->R->sz;
    T->sum += T->R->sum;
  }
}

Node *merge(Node *L, Node *R) {
  push(L), push(R);
  if (L == NULL) {
    return R;
  }
  if (R == NULL) {
    return L;
  }
  if (L->y > R->y) {
    L->R = merge(L->R, R);
    recalc(L);
    return L;
  } else {
    R->L = merge(L, R->L);
    recalc(R);
    return R;
  }
}

void split(Node *T, int key, Node *&L, Node *&R) {
  push(T);
  if (T == NULL) {
    L = R = NULL;
    return;
  }
  int le_sz = T->L == NULL ? 0 : T->L->sz;
  if (key < le_sz + 1) {
    R = T;
    split(T->L, key, L, R->L);
  } else {
    L = T;
    split(T->R, key - le_sz - 1, L->R, R);
  }
  recalc(T);
}

Node *head;

void push_back(int val) {
  Node *v = new Node(val);
  head = merge(head, v);
}

ll get_sum(int l, int r) {
  Node *t1, *t2, *t3, *t4;
  split(head, r, t3, t4);
  split(t3, l - 1, t1, t2);
  ll ans = t2->sum;
  t3 = merge(t1, t2);
  head = merge(t3, t4);
  return ans;
}

void rev(int l, int r) {
  Node *t1, *t2, *t3, *t4;
  split(head, r, t3, t4);
  split(t3, l - 1, t1, t2);
  t2->rev ^= 1;
  t3 = merge(t1, t2);
  head = merge(t3, t4);
}