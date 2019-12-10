//Монастырский Егор, 18-САИ-1, Вариант 7

// Создать шаблон класса «бинарное дерево». Использовать его для сортировки целых чисел и строк, задаваемых с клавиатуры или из файла. 

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

template<class T>
class bstree {
	struct node {
		node* left;
		node* right;
		T     val;
		node(void) noexcept :left(nullptr), right(nullptr) {}
	};
private:
	node* tr;
public:
	bstree(void) noexcept :tr(nullptr) {}
	~bstree() { clear(); }

	bstree(const bstree&) = delete;
	bstree& operator = (const bstree&) = delete;
public:
	//добавить(только для уникальных значений)
	void add(const T& v) {
		node* p;
		if (tr == nullptr) {
			tr = new node();
			tr->val = v;
		}
		else {
			node** rp = _find(v);
			if (tr != nullptr) {
				p = new node();
				p->val = v;
				*rp = p;
			}
		}
	}

	void add(T&& v) {
		node* p;
		if (tr == nullptr) {
			tr = new node();
			tr->val = forward<T>(v);
		}
		else {
			node** rp = _find(v);
			if (tr != nullptr) {
				p = new node();
				p->val = forward<T>(v);
				*rp = p;
			}
		}
	}

	//удаление с возвращением min-значения
	T pop_min(void) noexcept {
		T v;
		node** rp = &tr, * p = tr;
		if (tr != nullptr) {
			while (p->left != nullptr) {
				rp = &p->left;
				p = p->left;
			}
		}

		if (p != nullptr) {
			v = forward<T>(p->val);
			_erase(rp, p);
		}
		return forward<T>(v);
	}

	//удаление с возвращением max-значения
	T pop_max(void) noexcept {
		T v;
		node** rp = &tr, * p = tr;
		if (tr != nullptr) {
			while (p->right != nullptr) {
				rp = &p->right;
				p = p->right;
			}
		}

		if (p != nullptr) {
			v = forward<T>(p->val);
			_erase(rp, p);
		}
		return forward<T>(v);
	}

	//удаление всех
	void clear(void) noexcept {
		_clear(tr);
		tr = nullptr;
	}

	bool empty(void) const noexcept { return (tr == nullptr); }
private:

	node** _find(const T& v) noexcept {
		node** rp = &tr, * p = tr;
		while (p != nullptr) {
			if (v == p->val)
				return nullptr;
			else if (v < p->val) {
				rp = &p->left;
				p = p->left;
			}
			else {
				rp = &p->right;
				p = p->right;
			}
		}
		return rp;
	}

	void _erase(node** rp, node* p) noexcept {
		if (p->right == nullptr)
			*rp = p->left;
		else {
			node* t = p->right;
			if (t->left == nullptr) {
				t->left = p->left;
				*rp = t;
			}
			else {
				node* i = t->left;
				while (i->left != nullptr) {
					t = i;
					i = t->left;
				}
				t->left = i->right;
				i->left = p->left;
				i->right = p->right;
				*rp = i;
			}
		}
		delete p;
	}

	void _clear(node* p) noexcept {
		if (p != nullptr) {
			if (p->left != nullptr)
				_clear(p->left);
			if (p->right != nullptr)
				_clear(p->right);
			delete p;
		}
	}
};

/* чтение массива данных из строки, консоли или файла
   N = кол-во элементов
   данные
   ...
*/
template<typename T>
void get_array(vector<T>& vs, istream& _in) {
	T v;
	size_t n;
	if (!(_in >> n) || !n)
		return;

	vs.resize(n);
	for (size_t i = 0; i < n; ++i) {
		if (!(_in >> vs[i]))
			break;
	}
}

int main(void) {
	vector<int>::size_type i;

	//сортировка целых чисел
	vector<int> ia;

	//ввод из консоли
		get_array<int>(ia, cin);

	bstree<int> ti;
	for (auto v : ia)
		ti.add(v);

	for (i = 0; !ti.empty(); ++i)
		ia[i] = ti.pop_min();

	for (auto v : ia)
		cout << v << ' ';
	cout << endl;

	//сортировка строк
	vector<string> sa;

	//ввод из строки
	char s[] = "10\n5 4 7 9 8 2 1 3 0 6";
	istringstream sp(s);
	get_array<int>(ia, sp);

	bstree<string> ts;
	for (i = 0; i < sa.size(); ++i)
		ts.add(move(sa[i]));

	for (i = 0; !ts.empty(); ++i)
		sa[i] = ts.pop_min();

	for (const auto& v : sa)
		cout << v << ' ';
	cout << endl;

	//сортировка действительных чисел по убыванию
	vector<double> da;

	//ввод из строки
	char s2[] = "5\n 3.4 -8.5 543.1 1.5 4.4";
	istringstream sp2(s2);
	get_array<double>(da, sp2);

	bstree<double> td;
	for (const auto& d : da)
		td.add(d);

	for (i = 0; !td.empty(); ++i)
		da[i] = td.pop_max();

	for (const auto& v : da)
		cout << v << ' ';
	cin.get();
	return 0;
}