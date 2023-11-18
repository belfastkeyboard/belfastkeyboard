/*      Pythonic print() function
 *      
 *      Simple and concise method of printing to console.
 *      Generic 
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
 *          > std::variant
 *          > std::optional
 * 
 *      Multidimensional containers tested and functional:
 *          
 *          > std::pair
 *          > std::tuple
 *          > std::array
 *          > std::vector
 *          > std::list
 *          > std::deque
 *          > std::set
 *          > std::map
 * 
 * 
 *      Supported but only default container types have been tested:
 * 
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
 * 
 * 
 *      Partial support for pointers:
 * 
 *          Pointer support limited to fundamental types.
 *          Container support to be implemented.
 *          
 *              Current container implementation:
 *
 *                  > std::array
 *                  > std::vector
 *                  > std::list
 *                  > std::deque
 *                  > std::set
 *                  > std::map
 * 
 *      Parameter support:
 *          
 *          > sep() for separation between arguments
 *          > end() for newline or other end behaviour
 * 
 *          Both parameters are structs and should be called 
 *          with their constructs like this:
 * 
 *              > sep(" ")
 *              > end("\n")
 *
 * 
 *      ***          <---KNOWN ISSUES--->          ***
 *      
 *      wchar_t representation
 * 
 *     
 *      ***          <---TO DO--->          *** 
 * 
 *      Further testing for reference& support.
 *      Add additional pointer* &support for containers.
 *      Support for print(&memory_address).
 *      Testing for non-default stack, queue, and priority_queue containers.
 * 
 *      Improve documentation
 *      
 *      Improve error handling
 * 
 */

#ifndef     PYPRINT
#define     PYPRINT 1

#include    <iostream>
#include    <string>
#include    <sstream>

struct sep
{
    std::string __arg = " ";
    sep(std::string __sep) : __arg(__sep) {}
};

struct end
{
    std::string __arg = " ";
    end(std::string __end) : __arg(__end) {}
};

class PyPrint
{
private:
    std::stringstream   stream;
    std::string         output = "";
    sep                 _sep;
    end                 _end;
    enum class separation {off, on};
    // fundamental data types 
    template <typename T>
    void print(separation __separation, T& __arg)
    {
        stream << __arg;
        if (__separation == separation::on) stream << _sep.__arg;
    }
    // fundamental type pointers
    template <typename T>
    void print(separation __separation, T* __arg)
    {
        stream << *__arg;
        if (__separation == separation::on) stream << _sep.__arg;
    }
    // C style string handlers
    void print(separation __separation, char __arg[])
    {
        stream << __arg;
        if (__separation == separation::on) stream << _sep.__arg;
    }
    void print(separation __separation, const char* __arg)
    {
        stream << __arg;
        if (__separation == separation::on) stream << _sep.__arg;
    }
    // std::pair<T, U>
    #ifdef      _GLIBCXX_UTILITY
        template <typename T, typename U>
        void print(separation __separation, std::pair<T, U>& __arg)
        {
            stream << "(";
            print(separation::off, __arg.first);
            stream << ", ";
            print(separation::off, __arg.second);
            stream << ")";
            if (__separation == separation::on) stream << _sep.__arg;
        }
    #endif
    // std::tuple<T...>
    #ifdef      _GLIBCXX_TUPLE
    template <typename... T>
    void print(separation __separation, std::tuple<T...>& __arg)
    {
        stream << "(";
        print_tuple(false, __arg);
        stream << ")";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <size_t I = 0, typename... T>
    void print_tuple(separation __separation, std::tuple<T...>& __arg)
    {
        if constexpr (I < sizeof...(T)) {
        print(separation::off, std::get<I>(__arg));
        if (I + 1 < sizeof...(T)) stream << ", ";
        print_tuple<I + 1>(false, __arg);
        }
    }
    #endif
    // std::array<T, U>
    #ifdef      _GLIBCXX_ARRAY
    template <typename T, size_t U>
    void print(separation __separation, std::array<T, U>& __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T, size_t U>
    void print(separation __separation, std::array<T, U>* __arg)
    {
        stream << "[";
        for (auto it = __arg->begin(); it != __arg->end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg->end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::vector<T>
    #ifdef      _GLIBCXX_VECTOR
    template <typename T>
    void print(separation __separation, std::vector<T>& __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T>
    void print(separation __separation, std::vector<T>* __arg)
    {
        stream << "[";
        for (auto it = __arg->begin(); it != __arg->end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg->end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::list<T>
    #ifdef      _STL_LIST_H
    template <typename T>
    void print(separation __separation, std::list<T>& __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T>
    void print(separation __separation, std::list<T>* __arg)
    {
        stream << "[";
        for (auto it = __arg->begin(); it != __arg->end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg->end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::deque<T>
    #ifdef      _GLIBCXX_DEQUE
    template <typename T>
    void print(separation __separation, std::deque<T>& __arg)
    {
        stream << "[";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T>
    void print(separation __separation, std::deque<T>* __arg)
    {
        stream << "[";
        for (auto it = __arg->begin(); it != __arg->end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg->end()) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::set<T>
    #ifdef      _GLIBCXX_SET
    template <typename T>
    void print(separation __separation, std::set<T>& __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T>
    void print(separation __separation, std::set<T>* __arg)
    {
        stream << "{";
        for (auto it = __arg->begin(); it != __arg->end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg->end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::multiset<T>
    #ifdef      _STL_MULTISET_H
    template <typename T>
    void print(separation __separation, std::multiset<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::unordered_set<T>
    #ifdef      _GLIBCXX_UNORDERED_SET
    template <typename T>
    void print(separation __separation, std::unordered_set<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::unordered_multiset<T>
    #ifdef      _UNORDERED_SET_H
    template <typename T>
    void print(separation __separation, std::unordered_multiset<T> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, *it);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::map<T, U>
    #ifdef      _GLIBCXX_MAP
    template <typename T, typename U>
    void print(separation __separation, std::map<T, U>& __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, it->first);
            stream << ": ";
            print(separation::off, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T, typename U>
    void print(separation __separation, std::map<T, U>* __arg)
    {
        stream << "{";
        for (auto it = __arg->begin(); it != __arg->end(); it++)
        {
            print(separation::off, it->first);
            stream << ": ";
            print(separation::off, it->second);
            if (std::next(it) != __arg->end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::multimap<T, U>
    #ifdef      _STL_MULTIMAP_H
    template <typename T, typename U>
    void print(separation __separation, std::multimap<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, it->first);
            stream << ": ";
            print(separation::off, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::unordered_map<T, U>
    #ifdef      _GLIBCXX_UNORDERED_MAP
    template <typename T, typename U>
    void print(separation __separation, std::unordered_map<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, it->first);
            stream << ": ";
            print(separation::off, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::unordered_multimap<T, U>
    #ifdef      _UNORDERED_MAP_H
    template <typename T, typename U>
    void print(separation __separation, std::unordered_multimap<T, U> __arg)
    {
        stream << "{";
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(separation::off, it->first);
            stream << ": ";
            print(separation::off, it->second);
            if (std::next(it) != __arg.end()) stream << ", ";
        }
        stream << "}";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::stack<T>
    #ifdef      _GLIBCXX_STACK
    template <typename T>
    void print(separation __separation, std::stack<T> __arg)
    {
        stream << "[";
        while (!__arg.empty())
        {
            print(separation::off, __arg.top());
            __arg.pop();
            if (__arg.size() > 0) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::queue<T>, std::priority_queue<T>
    #ifdef      _GLIBCXX_QUEUE
    template <typename T>
    void print(separation __separation, std::queue<T> __arg)
    {
        stream << "[";
        while (!__arg.empty())
        {
            print(separation::off, __arg.front());
            __arg.pop();
            if (__arg.size() > 0) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    template <typename T>
    void print(separation __separation, std::priority_queue<T> __arg)
    {
        stream << "[";
        while (!__arg.empty())
        {
            print(separation::off, __arg.top());
            __arg.pop();
            if (__arg.size() > 0) stream << ", ";
        }
        stream << "]";
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::unique_ptr<T>, std::shared_ptr<T>, std::weak_ptr<T>
    #ifdef      _GLIBCXX_MEMORY
    template <typename T>
    void print(separation __separation, std::unique_ptr<T>& __arg)
    {
        print(true, *__arg.get());
    }
    template <typename T>
    void print(separation __separation, std::shared_ptr<T>& __arg)
    {
        print(true, *__arg.get());
    }
    template <typename T>
    void print(separation __separation, std::weak_ptr<T>& __arg)
    {
        print(true, *__arg.lock());
    }
    #endif
    // std::bitset<T>
    #ifdef      _GLIBCXX_BITSET
    template <size_t T>
    void print(separation __separation, std::bitset<T>& __arg)
    {
        stream << __arg.to_string();
        if (__separation == separation::on) stream << _sep.__arg;
    }    
    #endif
    // std::variant<T...>
    #ifdef      _GLIBCXX_VARIANT
    template <typename... T>
    void print(separation __separation, std::variant<T...>& __arg)
    {
        auto __vis = [this](const auto& __type) {
            print(separation::off, __type);
        };
        std::visit(__vis, __arg);
        if (__separation == separation::on) stream << _sep.__arg;
    }
    #endif
    // std::optional<T>
    #ifdef      _GLIBCXX_OPTIONAL
    template <typename T>
    void print(separation __separation, std::optional<T>& __arg)
    {
        if (__arg.has_value()) {print(separation::off, __arg.value());} else {stream << "No value!";}
        if (__separation == separation::on) stream << _sep.__arg;
    }    
    #endif
public:
    template <typename... Arg>
    void start_print(Arg&&... __args)
    {
        stream << std::boolalpha;
        (print(separation::on, __args), ...);
        std::string output = stream.str();
        size_t found = output.rfind(_sep.__arg);
        output.erase(found, found + (_sep.__arg.size() - 1));
        if (output.back() != '!' && output.back() != '.') output += ".";
        std::cout << output << _end.__arg;
    }
    PyPrint(sep __s = sep(" "), end __e = end("\n")) : _sep(__s), _end(__e) {}
};

inline void print()
{
    std::cout << std::endl;
}
template <typename... T>
void print(T&&... __args)
{
    PyPrint python_print;
    python_print.start_print(__args...);
}
template <typename... T>
void print(sep __sep, T&&... __args)
{
    PyPrint python_print(__sep, end("\n"));
    python_print.start_print(__args...);
}
template <typename... T>
void print(end __end, T&&... __args)
{
    PyPrint python_print(sep(" "), __end);
    python_print.start_print(__args...);
}
template <typename... T>
void print(sep __sep, end __end, T&&... __args)
{
    PyPrint python_print(__sep, __end);
    python_print.start_print(__args...);
}

#endif
