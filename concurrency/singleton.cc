/**
 * File: singleton.cc
 * Date: 01/14/2016
 * Author: Qirong Ma
 *
 * Synopsis: Common singleton patterns in C++
 * Reference: http://www.cnblogs.com/loveis715/archive/2012/07/18/2598409.html
 *            http://blog.csdn.net/hackbuteer1/article/details/7460019
 */
#include <cstdio>
#include <cstdlib>
#include <mutex>
using namespace std;

/**
 * Basic version
 */
class Singleton1 {
public:
  static Singleton1& GetInstance() {
    static Singleton1 singleton;
    return singleton;
  }

private:
  Singleton1() {}
  ~Singleton1() {}
  Singleton1(const Singleton1& other);
  Singleton1& operator=(const Singleton1& other);
};

/**
 * CRTP (Curiously Recurring Template Pattern)
 */
template <typename T>
class Singleton2 {
public:
  static T& GetInstance() {
    static T singleton;
    return singleton;
  }

protected:
  Singleton2() {}
  ~Singleton2() {}

private:
  Singleton2(const Singleton2& other);
  Singleton2& operator=(const Singleton2& other);
};

class Singleton20 : public Singleton2<Singleton20> {
};

/**
 * Using pointer rather than reference with automatic delete
 * *NOT* thread safe
 */
template <typename T>
class Singleton3 {
public:
  static T* GetInstance() {
    if (m_pInstance == nullptr)
      m_pInstance = new T();
    return m_pInstance;
  }

protected:
  Singleton3() {
    printf("Singleton3 = 0x%016llx created\n", (uint64_t)this);
  }
  ~Singleton3() {
    printf("Singleton3 = 0x%016llx deleted\n", (uint64_t)this);
  }

private:
  Singleton3(const Singleton3& other);
  Singleton3& operator=(const Singleton3& other);

  class Garbo {
  public:
    ~Garbo() {
      if (Singleton3::m_pInstance) {
        delete Singleton3::m_pInstance;
      }
    }
  };

  static Garbo garbo;
  static T* m_pInstance;
};

template<typename T>
T* Singleton3<T>::m_pInstance = nullptr;

// Why this does not compile?
// template<typename T>
// Singleton3<T>::Garbo Singleton3<T>::garbo;

class Singleton30 : public Singleton3<Singleton30> {
public:
  void hello() {
    printf("Hello from Singleton30 = 0x%016llx\n", (uint64_t)this->GetInstance());
  }
};

template<>
Singleton3<Singleton30>::Garbo Singleton3<Singleton30>::garbo;

/**
 * Thread-safe version
 */
template <typename T>
class Singleton4 {
public:
  static T& GetInstance() {
    if (!m_pInstance) {
      lock_guard<mutex> lock(m_mutex);
      if (!m_pInstance) {
        m_pInstance = new T();
        atexit(Destroy);
      }
      return *m_pInstance;
    }
    return *m_pInstance;
  }

protected:
  Singleton4() {
    printf("Singleton4 = 0x%016llx created\n", (uint64_t)this);
  }
  ~Singleton4() {
    printf("Singleton4 = 0x%016llx deleted\n", (uint64_t)this);
  }

private:
  Singleton4(const Singleton4& rhs);
  Singleton4& operator=(const Singleton4& rhs);

  void static Destroy() {
    if (m_pInstance)
      delete m_pInstance;
    m_pInstance = nullptr;
  }

  static mutex m_mutex;
  static T* volatile m_pInstance;
};

template <typename T>
T* volatile Singleton4<T>::m_pInstance = nullptr;

template <typename T>
mutex Singleton4<T>::m_mutex;

class Singleton40 : public Singleton4<Singleton40> {
public:
  void hello() {
    printf("Hello from Singleton40 = 0x%016llx\n", (uint64_t)&GetInstance());
  }
};

int main() {
  auto& s1 = Singleton1::GetInstance();

  auto& s2 = Singleton20::GetInstance();

  Singleton30::GetInstance()->hello();

  Singleton40::GetInstance().hello();

  return 0;
}
