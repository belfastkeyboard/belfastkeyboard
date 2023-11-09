/*      Pythonic print() function
 *      
 *      Simple and concise method of printing to console.
 *      print() is a variadic function, it accepts as many arguments as you want.
 *      Arguments are separated with spaces, a full-stop is placed at the end, and a new line is added.
 *      Use print() with no arguments for a quick newline.
 *      print() the contents of your containers without creating your own loops or other specific access methods.
 *      Mix and match data types.
 * 
 * 
 *      Currently supports all fundamental data-types:
 * 
 *          > bool (prints 'true' | 'false', not '1' | '0')
 *          > char
 *          > C style strings
 *          > C++ style strings
 *          > all numeric types
 * 
 * 
 *      Supports these data-structures/containers:
 * 
 *          > const char* array
 *          > char array[]
 *          > std::pair
 *          > std::tuple
 *          > std::array
 *          > std::vector
 *          > std::list
 *          > std::deque
 *          > std::set
 *          > std::multiset
 *          > std::unordered_set
 *          > std::unordered_multiset
 *          > std::map
 *          > std::multimap
 *          > std::unordered_map
 *          > std::unordered_multimap
 *          > std::bitset
 * 
 *          Supported but only default container types have been tested:
 *              > std::stack
 *              > std::queue
 *              > std::priority_queue
 *           
 * 
 *      Supports smart pointers:
 *          
 *          > std::unique_ptr
 *          > std::shared_ptr
 *          > std::weak_ptr
 * 
 *              Currently no safety checks regarding undefined pointers. 
 * 
 * 
 *      Supports references (not fully tested.)
 *      Testing for non-default stack, queue, and priority_queue containers.
 * 
 * 
 *      Partial support for pointers:
 * 
 *          Pointer support limited to fundamental types.
 *          Container support to be implemented.
 *
 * 
 *      ***          <---KNOWN ISSUES--->          ***
 *      
 *      wchar_t representation
 * 
 *     
 *      ***          <---TO DO--->          ***
 * 
 *      C++17 features:
 * 
 *          std::variant<>
 *          std::optional<>
 *
 * 
 *      Further testing for reference& support.
 *      Add additional pointer* &support for containers.
 *      Support for print(&memory_address).
 * 
 *      Support for:
 *          > multidimensional containers
 *      
 * 
 *      Parameter support:
 *          
 *          Support for Pythonic print() keyword arguments.
 *          C++ only accepts positional arguments, not keyword arguments.
 * 
 *          > sep=""
 *          > end=""
 * 
 *      Improve documentation
 *      
 *      Improve preprocessor directives
 * 
 *      Improve error handling
 * 
 */

#ifndef     PYPRINT
#define     PYPRINT 1

#include    <iostream>
#include    <string>
#include    <sstream>

class PyPrint
{
private:
    std::stringstream   stream;
    std::string         output;

    // fundamental data types 
    template <typename T>
    void print(bool sep, T& __arg)
    {
        stream << __arg;
        if (sep) stream << " ";
    }
    // fundamental type pointers
    template <typename T>
    void print(bool sep, T* __arg)
    {
        stream << *__arg;
        if (sep) stream << " ";
    }
    // C style string handlers
    void print(bool sep, char __arg[])
    {
        stream << __arg;
        if (sep) stream << " ";
    }
    void print(bool sep, const char* __arg)
    {
        stream << __arg;
        if (sep) stream << " ";
    }
    // std::pair<T, U>
    #ifdef      _GLIBCXX_UTILITY
        template <typename T, typename U>
        void print(bool sep, std::pair<T, U> __arg)
        {
            stream << "(";
            print(false, __arg.first);
            stream << ", ";
            print(false, __arg.second);
            stream << ")";
            if (sep) stream << " ";
        }
    #endif
    // std::tuple<T...>
    #ifdef      _GLIBCXX_TUPLE
    template <typename... T>
    void print(bool sep, std::tuple<T...>& __arg)
    {
        stream << "(";
        print_tuple(false, __arg);
        stream << ")";
        if (sep) stream << " ";
    }
    template <size_t I = 0, typename... T>
    void print_tuple(bool sep, std::tuple<T...>& __arg)
    {
        if constexpr (I < sizeof...(T)) {
        print(false, std::get<I>(__arg));
        if (I + 1 < sizeof...(T)) stream << ", ";
        print_tuple<I + 1>(false, __arg);
        }
    }
    #endif
    // std::array<T, U>
    #ifdef      _GLIBCXX_ARRAY
    template <typename T, size_t U>
    void print(bool sep, std::array<T, U> __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    #endif
    // std::vector<T>
    #ifdef      _GLIBCXX_VECTOR
    template <typename T>
    void print(bool sep, std::vector<T> __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    #endif
    // std::list<T>
    #ifdef      _STL_LIST_H
    template <typename T>
    void print(bool sep, std::list<T> __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    #endif
    // std::deque<T>
    #ifdef      _GLIBCXX_DEQUE
    template <typename T>
    void print(bool sep, std::deque<T> __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    #endif
    // std::set<T>
    #ifdef      _GLIBCXX_SET
    template <typename T>
    void print(bool sep, std::set<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::multiset<T>
    #ifdef      _STL_MULTISET_H
    template <typename T>
    void print(bool sep, std::multiset<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::unordered_set<T>
    #ifdef      _GLIBCXX_UNORDERED_SET
    template <typename T>
    void print(bool sep, std::unordered_set<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::unordered_multiset<T>
    #ifdef      _UNORDERED_SET_H
    template <typename T>
    void print(bool sep, std::unordered_multiset<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::map<T, U>
    #ifdef      _GLIBCXX_MAP
    template <typename T, typename U>
    void print(bool sep, std::map<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, it->first);
            stream << ": ";
            print(false, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::multimap<T, U>
    #ifdef      _STL_MULTIMAP_H
    template <typename T, typename U>
    void print(bool sep, std::multimap<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, it->first);
            stream << ": ";
            print(false, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::unordered_map<T, U>
    #ifdef      _GLIBCXX_UNORDERED_MAP
    template <typename T, typename U>
    void print(bool sep, std::unordered_map<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, it->first);
            stream << ": ";
            print(false, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::unordered_multimap<T, U>
    #ifdef      _UNORDERED_MAP_H
    template <typename T, typename U>
    void print(bool sep, std::unordered_multimap<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, it->first);
            stream << ": ";
            print(false, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (sep) stream << " ";
    }
    #endif
    // std::stack<T>
    #ifdef      _GLIBCXX_STACK
    template <typename T>
    void print(bool sep, std::stack<T> __arg)
    {
        stream << "[";
        while (!__arg.empty())
        {
            print(false, __arg.top());
            __arg.pop();
            if (__arg.size() > 0) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    #endif
    // std::queue<T>, std::priority_queue<T>
    #ifdef      _GLIBCXX_QUEUE
    template <typename T>
    void print(bool sep, std::queue<T> __arg)
    {
        stream << "[";
        while (!__arg.empty())
        {
            print(false, __arg.front());
            __arg.pop();
            if (__arg.size() > 0) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    template <typename T>
    void print(bool sep, std::priority_queue<T> __arg)
    {
        stream << "[";
        while (!__arg.empty())
        {
            print(false, __arg.top());
            __arg.pop();
            if (__arg.size() > 0) stream << ", ";
        }
        stream << "]";
        if (sep) stream << " ";
    }
    #endif
    // std::unique_ptr<T>, std::shared_ptr<T>, std::weak_ptr<T>
    #ifdef      _GLIBCXX_MEMORY
    template <typename T>
    void print(bool sep, std::unique_ptr<T>& __arg)
    {
        print(true, *__arg.get());
    }
    template <typename T>
    void print(bool sep, std::shared_ptr<T>& __arg)
    {
        print(true, *__arg.get());
    }
    template <typename T>
    void print(bool sep, std::weak_ptr<T>& __arg)
    {
        print(true, *__arg.lock());
    }
    #endif
    // std::bitset<T>
    #ifdef      _GLIBCXX_BITSET
    template <size_t T>
    void print(bool sep, std::bitset<T>& __arg)
    {
        stream << __arg.to_string();
        if (sep) stream << " ";
    }    
    #endif

public:
    template <typename... Arg>
    PyPrint(Arg&&... __args)
    {
        stream << std::boolalpha;
        (print(true, __args), ...);
        std::string output = stream.str();
        while (output.back() == ' ') output.pop_back();
        if (output.back() != '!' && output.back() != '.') output += '.';
        std::cout << output << std::endl;
    }
};

inline void print()
{
    std::cout << std::endl;
}
template <typename... T>
void print(T&&... __args)
{
    PyPrint python_print(__args...);
}

#endif
