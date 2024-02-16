#ifndef __CONCEPTS_H__
#define __CONCEPTS_H__

    #include <type_traits>
template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;
#endif //!__CONCEPTS_H__