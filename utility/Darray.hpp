#ifndef D_ARRAY_
#define D_ARRAY_

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace tinys {
namespace utility{

template<typename T, int N>
class Array{
public:

    Array() : m_p(new T[N]), m_capacity(N){}

    ~Array() {delete [] m_p;}
    
    T& operator [] (int i) {
        if (i <0 || i >= m_length) {
            printf("Exception: Array Index out of bounds!\n");
            return nullptr;
        } 
        return m_p[i];
    }

    bool capcacity(int n) {
        if (n > 0) { // 增大数组
            int len = m_length + n;
            if (len <= m_capacity) {
                m_length = len;
                return true;
            } else {
                T *pTemp = new T[m_length + 2*n*sizeof(T)];
                memcpy(pTemp, m_p, m_length*sizeof(T));
                delete [] m_p;
                m_p = pTemp;
                m_capacity = m_length = len;
            }
        } else{  //收缩数组
            int len = m_length - abs(n);  //收缩后的数组长度
            if(len < 0){
                printf("Exception: Array length is too small!");
                return false;
            }else{
                m_length = len;
                return true;
            }
        }
    }

    size_t length() const {
        return m_length;
    }

private:
    int m_length;
    int m_capacity;
    T* m_p;
};


}
}

#endif

