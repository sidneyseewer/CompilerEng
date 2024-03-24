/**
 * @file Singelton.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Singelton base class
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __SINGELTON_H__
#define __SINGELTON_H__

#include <memory>
#include <utility>
/**
 * @brief Singelton base class
 * 
 * @tparam T 
 */
template <class T> class Singelton {
public:
  template <typename... Args> static T &GetInstance(Args... args) {
    if (mInstance == nullptr) {
      mInstance = std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
    }
    return *mInstance;
  }
  static void Delete() { mInstance.reset(); }

protected:
  Singelton() = default;

private:
  Singelton(Singelton const &s) = delete;
  Singelton &operator=(Singelton const &s) = delete;
  static std::unique_ptr<T> mInstance;
};
template <typename T> std::unique_ptr<T> Singelton<T>::mInstance{nullptr};
#endif //!__SINGELTON_H__