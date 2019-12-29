#pragma once
#include <memory>
#include <algorithm>

static int counter = 0;

template<typename elem, typename priority>
class Node;

template<typename elem, typename priority>
using nodePtr = std::shared_ptr<Node<elem, priority>>;

template<typename elem, typename priority>
class Node {
public:
	elem key;
	priority prior;

	nodePtr<elem, priority> left, right;

	Node() = default;

	//default copy constructor and operator= are intended

	~Node() = default;

	Node(elem key, priority prior) : key(key), prior(prior), left(nullptr), right(nullptr) { }

	static void split(nodePtr<elem, priority>, elem, nodePtr<elem, priority> &, nodePtr<elem, priority> &);

	static void insert(nodePtr<elem, priority> &, nodePtr<elem, priority>);

	static void merge(nodePtr<elem, priority> &, nodePtr<elem, priority>, nodePtr<elem, priority>);

	static bool erase(nodePtr<elem, priority> &, elem);

	static bool search(nodePtr<elem, priority> &, elem);

	static int depth(nodePtr<elem, priority> &);
};


template<typename elem, typename priority>
bool Node<elem, priority>::search(nodePtr<elem, priority>& head, elem key)
{
	++counter;

	if (!head)
		return false;


	if (head->key == key)
		return true;

	return search(head->key < key ? head->right : head->left, key);


}





template<typename elem, typename priority>
void Node<elem, priority>::split(nodePtr<elem, priority> head, elem key, nodePtr<elem, priority> & left, nodePtr<elem, priority> & right) {
	++counter;

	if (!head) {
		left = nullptr;
		right = nullptr;
	}

	else if (key < head->key) {
		split(head->left, key, left, head->left);
		right = head;
	}

	else {
		split(head->right, key, head->right, right);
		left = head;
	}
}

template<typename elem, typename priority>
void Node<elem, priority>::insert(nodePtr<elem, priority> &t, nodePtr<elem, priority> it) {
	++counter;

	if (!t)
		t = it;

	else if (it->prior > t->prior) {
		split(t, it->key, it->left, it->right);
		t = it;
	}

	else
		insert(it->key < t->key ? t->left : t->right, it);
}

template<typename elem, typename priority>
void Node<elem, priority>::merge(nodePtr<elem, priority> & t, nodePtr<elem, priority> l, nodePtr<elem, priority> r) {
	++counter;

	if (!l || !r)
		t = l ? l : r;

	else if (l->prior > r->prior) {
		merge(l->right, l->right, r);
		t = l;
	}

	else {
		merge(r->left, l, r->left);
		t = r;
	}
}

template<typename elem, typename priority>
bool Node<elem, priority>::erase(nodePtr<elem, priority> & t, elem key) {
	++counter;

	if (!t)
		return false;

	if (t->key == key) {
		merge(t, t->left, t->right);

		return true;
	}

	return erase(key < t->key ? t->left : t->right, key);

}


template<typename elem, typename priority>
int Node<elem, priority>::depth(nodePtr<elem, priority> &head)
{
	if (!head)
		return 0;

	return std::max(depth(head->left), depth(head->right)) + 1;
}