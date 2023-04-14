#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace utility {

// 线程不安全
template<typename T>
class Singleton {
public:
    static T* instance() {
        if (m_instance == nullptr) m_instance = new T();
        return m_instance;
    }
    
private:
    Singleton() {}
    ~Singleton() {}

    Singleton(const Singleton<T>&) = delete;
    Singleton<T>& operator = (const Singleton<T>&) = delete;

private:
    static T* m_instance;
};

template<typename T>
T* Singleton<T>::m_instance = nullptr;
    
}

#endif