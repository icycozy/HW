#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <iostream>

#define USE_OS

class error : public std::exception {
private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};

template <typename T>
class ArrayList {
private:
  int l; T *p{nullptr};

public:
    // constructor with a given array (T* arr, int length) 从已有的数组构造
    explicit ArrayList(T* arr, int length){
      if(length < 0) throw error("invalid length");
      l = length;
      p = new T[l];
      for(int i=0;i<l;i++) p[i]=arr[i];
    }
    // constructor with fixed length (int length) 构造一个固定长度的数组
    explicit ArrayList(int length){
      if(length < 0) throw error("invalid length");
      l = length;
      p = new T[l];
    }
    // copy constructor 拷贝构造函数
    ArrayList(const ArrayList<T> &a){
      l = a.l;
      p = new T[l];
      for(int i=0;i<l;i++) p[i] = a.p[i];
    }
    // size()
    int size() const {return this->l;}
    // operator[]
    T& operator [] (const int& k) const{
      if(k<0 || k>=l) throw error("index out of bound");
      return this->p[k];
    }
    // operator+ 
    ArrayList operator + (const ArrayList<T> &a) const{
      ArrayList<T> sum(l + a.l);
      for(int i=0;i<l;i++) sum.p[i] = p[i];
      for(int i=l;i<sum.l;i++) sum.p[i] = a.p[i-l];
      return sum;
    }
    // operator=
    ArrayList& operator = (const ArrayList<T> &a){
      if(this == &a) return *this; // !!
      if(p!=nullptr) delete[] p; // Leak
      l = a.l;
      p = new T[l];
      for(int i=0;i<l;i++) p[i] = a.p[i];
      return *this;
    }
    // operator==
    bool operator == (const ArrayList<T> &a) const{
      if(l!=a.l) return 0;
      for(int i=0;i<l;i++) if(p[i]!=a.p[i]) return 0;
      return 1;
    }
    // operator!=
    bool operator != (const ArrayList<T> &a) const{
      if(l!=a.l) return 1;
      for(int i=0;i<l;i++) if(p[i]!=a.p[i]) return 1;
      return 0;
    }

#ifdef USE_OS
    // operator<<
    friend std::ostream & operator << (std::ostream &o, const ArrayList<T> &list){
      for(int i=0;i<list.l;i++) o<<list.p[i]<<" ";
      return o;
    }

#endif
    //destructor 析构函数
    ~ArrayList() {delete[] p;}
};

#endif // ARRAY_LIST_HPP