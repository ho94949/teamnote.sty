namespace Meldable {
mt19937 gen(0x94949);
template<typename T>
struct Node {
	Node *l, *r;
	T v;
	Node(T x): l(0), r(0), v(x){}
};
template<typename T>
Node<T>* Meld(Node<T>* A, Node<T>* B) {
	if(!A) return B; if(!B) return A;
	if(B->v < A->v) swap(A, B);
	if(gen()&1) A->l = Meld(A->l, B);
	else A->r = Meld(A->r, B);
	return A;
}
template<typename T>
struct Heap {
	Node<T> *r; int s;
	Heap(): r(0), s(0){}
	void push(T x) {
		r = Meld(new Node<T>(x), r);
		++s;
	}
	int size(){ return s; }
	bool empty(){ return s == 0;}
	T top(){ return r->v; }
	void pop() {
		Node<T>* p = r;
		r = Meld(r->l, r->r);
		delete p;
		--s;
	}
	void Meld(Heap x) {
		s += x->s;
		r = Meld(r, x->r);
	}
};
}
