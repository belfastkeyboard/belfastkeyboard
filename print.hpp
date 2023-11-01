#pragma once

/*
 *
 *      Pythonic print() function
 *      
 *      Simple and concise method of printing to console.
 *      print() is a variadic function, it accepts as many arguments as you want.
 *      Arguments are separated with spaces, a full-stop is placed at the end, and a new line is added.
 *      Use print() with no arguments for a quick newline.
 *      print() the contents of your containers without creating your own loops or other specific access methods.
 *      Mix and match data types.
 * 
 *      Requires C++14.
 * 
 * 
 *      Currently supports all fundamental data-types:
 * 
 *          > bool (prints 'true' | 'false', not '1' | '0')
 *          > char
 *          > C style strings
 *          > C++ style strings e.g. std::string
 *          > all numeric values, int- or float-based, signed, unsigned, size_t, etc.
 * 
 * 
 *      Supports these data-structures/containers:
 * 
 *          > std::pair
 *          > std::tuple
 *          > std::array
 *          > std::vector
 *          > std::list
 *          > std::deque
 *          > std::set
 *          > std::unordered_set
 *          > std::map
 *          > std::unordered_map
 *           
 * 
 *      Partial support for smart pointers:
 *          
 *          > std::unique_ptr (use ptr.get() in the print() function's argument)
 *          > std::shared_ptr
 *          > std::weak_ptr
 * 
 *          Smart pointer support limited to:
 * 
 *              > numeric types
 *              > bool
 *              Further implementation pending.
 * 
 * 
 *      Supports references (not fully tested.)
 * 
 * 
 *      Partial support for pointers:
 * 
 *          Pointer support limited to:
 * 
 *          > bool
 *          > numeric types
 *      
 *     
 *      ***          <---TO DO--->          ***
 * 
 *      Some C++17 features:
 * 
 *          std::variant<>
 *          std::optional<>
 *
 * 
 *      Further testing for reference& support.
 *      Add additional pointer* &support.
 *      Support for print(&memory_address).
 * 
 *      Support for C-style arrays.
 *      Support for multidimensional vectors, arrays, etc.
 *      Support for unions.
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
 *      Refactor code:
 * 
 *          Implementation is currently a bit banjaxed and needs to be cleaned up.
 *
 *      Improve documentation
 *      
 *      Improve preprocessor directives
 * 
 *      Improve error handling
 * 
 * 
 */

#if __cplusplus >= 201402L

#include    <iostream>
#include    <string>
#include    <typeinfo>

class PyPrint
{
private:
    typedef std::string    string;
    string  output = "";

    void print(bool sep, bool __arg)
    {
        output += ((__arg) ? "true" : "false");
        if (sep) output += ' ';
    }
    void print(bool sep, bool* __arg)
    {
        output += ((*__arg) ? "true" : "false");
        if (sep) output += ' ';
    }
    void print(bool sep, char __arg)
    {
        output += __arg;
        if (sep) output += ' ';
    }
    void print(bool sep, wchar_t __arg)
    {
        output += __arg;
        if (sep) output += ' ';
    }
    void print(bool sep, const char* __arg)
    {
        output.append(__arg);
        if (sep) output += ' ';
    }
    void print(bool sep, string __arg)
    {
        output += __arg;
        if (sep) output += ' ';
    }
    template <typename T>
    void print(bool sep, T __arg)
    {
        if (std::is_integral_v<T>)
        {
            output += std::to_string(__arg);
        }
        else if (std::is_floating_point_v<T>)
        {
            std::string fl = std::to_string(__arg);
            while (fl[fl.size() - 1] == fl[fl.size() - 2]) {fl.pop_back();}
            output += fl;
        }
        if (sep) output += ' ';
    }
    template <typename T>
    void print(bool sep, T* __arg)
    {
        if (std::is_integral_v<T>)
        {
            output += std::to_string(*__arg);
        }
        else if (std::is_floating_point_v<T>)
        {
            std::string fl = std::to_string(*__arg);
            while (fl[fl.size() - 1] == fl[fl.size() - 2]) {fl.pop_back();}
            output += fl;
        }
        if (sep) output += ' ';
    }

    #ifdef      _GLIBCXX_UTILITY        // std::pair
    template <typename T, typename U>
    void print(bool sep, std::pair<T, U> __arg)
    {
        output += '(';
        print(false, __arg.first);
        output += ", ";
        print(false, __arg.second);
        output += ')';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_TUPLE          // std::tuple
    template <typename... T>
    void print(bool sep, std::tuple<T...>& __arg)
    {
        output += '[';
        print_tuple(false, __arg);
        while (output.back() == ' ' || output.back() == ',') output.pop_back();
        output += ']';
        if (sep) output += ' ';
    }
    template <size_t I = 0, typename... T>
    void print_tuple(bool sep, std::tuple<T...>& __arg)
    {
        if constexpr (I < sizeof...(T)) {
        print(false, std::get<I>(__arg));
        output += ", ";
        print_tuple<I + 1>(false, __arg);
        }
    }
    #endif

    #ifdef      _GLIBCXX_ARRAY          // std::array
    template <typename T, size_t U>
    void print(bool sep, std::array<T, U> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_VECTOR         // std::vector
    template <typename T>
    void print(bool sep, std::vector<T> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _STL_LIST_H             // std::list
    template <typename T>
    void print(bool sep, std::list<T> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += "] ";
    }
    #endif

    #ifdef      _GLIBCXX_DEQUE          // std::deque
    template <typename T>
    void print(bool sep, std::deque<T> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_SET            // std::set
    template <typename T>
    void print(bool sep, std::set<T> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_UNORDERED_SET  // std::unordered_set
    template <typename T>
    void print(bool sep, std::unordered_set<T> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, *it);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_MAP            // std::map
    template <typename T, typename U>
    void print(bool sep, std::map<T, U> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, it->first);
            output += ": ";
            print(false, it->second);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_UNORDERED_MAP  // std::unordered_map
    template <typename T, typename U>
    void print(bool sep, std::unordered_map<T, U> __arg)
    {
        output += '[';
        for (auto it = __arg.begin(); it != __arg.end(); it++)
        {
            print(false, it->first);
            print(false, ": ");
            print(false, it->second);
            if (std::next(it) != __arg.end())  output += ", ";
        }
        output += ']';
        if (sep) output += ' ';
    }
    #endif

    #ifdef      _GLIBCXX_MEMORY         // smart pointers
    template <typename T>
    void print(bool sep, std::unique_ptr<T>& __arg)
    {
        print(true, __arg.get());
    }
    template <typename T>
    void print(bool sep, std::shared_ptr<T>& __arg)
    {
        print(true, __arg.get());
    }
    template <typename T>
    void print(bool sep, std::weak_ptr<T>& __arg)
    {
        print(true, __arg.get());
    }
    #endif

public:
    template <typename... Arg>
    PyPrint(Arg... __args) {
        (print(true, __args), ...);
        while (output.back() == ' ') {output.pop_back();}
        output += '.';
        std::cout << output << std::endl;
    }
};

inline void print()
{
    std::cout << std::endl;
}
template <typename... T>
void print(T... __args)
{
    PyPrint python_print(__args...);
}

#endif