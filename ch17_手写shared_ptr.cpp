#include <iostream>
#include <string>
#include <cassert>
using namespace std;
class Person {
public:
    int age;
    string name;
    Person() :age(10), name("hah") { cout << "构造函数" << endl; }
    ~Person() { cout << "析构函数" << endl; }
};

template<class T>
class Smartptr {
public:
    T* _ptr;
    int* _pcount;
public:
    Smartptr(T* p = nullptr) {
        _ptr = p;
        if (p == nullptr) {
            _pcount = new int(0);
        }
        else {
            _pcount = new int(1);
        }
    }
    Smartptr(const Smartptr& s) :_ptr(s._ptr), _pcount(s._pcount) {
        ++* (_pcount);
    }
    Smartptr& operator=(const Smartptr* s) {

        if (s->_ptr == this->_ptr) {
            --* (this->_pcount);
            if (*(this->_pcount) == 0) {
                delete _pcount;
                _pcount = nullptr;
                delete _ptr;
                _ptr = nullptr;
            }
            this->_pcount = s->_pcount;
            this->_ptr = s->_ptr;
            ++* (_pcount);
        }
        return s;

    }
    ~Smartptr() {
        if (_ptr == nullptr) {
            cout << "指针为空" << endl;
            delete _pcount;
            return;
        }
        --* (_pcount);
        if (*(_pcount) == 0) {
            delete _pcount;
            _pcount = nullptr;
            delete _ptr;
            _ptr = nullptr;
            cout << "智能指针指向的对象已经释放" << endl;
        }
    }

    T* operator->() {
        assert(_ptr != nullptr);
        return this->_ptr;
    }
    T& operator*() {
        assert(_ptr != nullptr);
        return *(this->_ptr);
    }
    int use_count() {
        return *(_pcount);
    }
};
int main() {
    Smartptr<Person> sp(new Person());
    cout << (*sp).age << endl;
    cout << sp->name << endl;

    Smartptr<Person> sp1(sp);
    cout << sp1.use_count() << endl;

    // Smartptr<Person> sp2=sp1;
    // cout<<sp2.use_count()<<endl;

    sp = sp1;
    cout << "&sp= " << &sp << endl;
    cout << "&sp1= " << &sp1 << endl;
    cout << "&sp->_ptr= " << sp._ptr << endl;
    cout << "&sp1->_ptr= " << sp1._ptr << endl;
    cout << sp1.use_count() << endl;
}