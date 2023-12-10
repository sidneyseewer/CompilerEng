#ifndef __SINGELTON_H__
#define __SINGELTON_H__

#include <memory>
#include <utility>
template <class T>
class Singelton{
public:
template<typename ...Args> static T& GetInstance(Args... args){
    if(mInstance==nullptr)
    {
        mInstance=std::unique_ptr<T>{std::forward<args>(args)...};
    }
    return *mInstance;
}
protected:
Singelton()=default;
private:
    Singelton(Singelton const&s)=delete;
    Singelton& operator=(Singelton const&s)=delete;
    static std::unique_ptr<T> mInstance;
};
#endif //!__SINGELTON_H__