/**
 * author: TomDev - Tran Hoang Quan
 * My target: TOMDEV WILL AK VOI 2026
**/

#ifndef TomDev_will_AK_VOI
    #define TomDev_will_AK_VOI
#endif

// DEBUGGER
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& pair);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec);

template <typename T, size_t SZ>
std::ostream& operator<<(std::ostream& out, const std::array<T, SZ>& arr);

template <typename T, typename C, typename A>
std::ostream& operator<<(std::ostream& out, const std::set<T, C, A>& set);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::multiset<T>& set);

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::map<T1, T2>& map);

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& pair) {
    return out << '(' << pair.first << ", " << pair.second << ')';
}

// Chuyên biệt hóa cho vector 2 chiều để in xuống dòng
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    if (vec.empty()) {
        return out << "[]";
    }
    out << '[';
    for (int i = 0; i < (int)vec.size() - 1; i++) {
        out << vec[i] << ", ";
    }
    return out << vec.back() << ']';
}

template <typename T, size_t SZ>
std::ostream& operator<<(std::ostream& out, const std::array<T, SZ>& arr) {
    if (SZ == 0) {
        out << "[]";
        return out;
    }
    out << '[';
    for (int i = 0; i < SZ - 1; i++) {
        out << arr[i] << ", ";
    }
    return out << arr.back() << ']';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::deque<T>& deq) {
    if (deq.empty()) {
        out << "[]";
        return out;
    }
    out << '[';
    for (int i = 0; i < (int)deq.size() - 1; i++) {
        out << deq[i] << ", ";
    }
    return out << deq.back() << ']';
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::unordered_map<T1, T2>& map) {
    out << '{';
    for (auto it = map.begin(); it != map.end(); it++) {
        std::pair<T1, T2> element = *it;
        out << element.first << ": " << element.second;
        if (std::next(it) != map.end()) {
            out << ", ";
        }
    }
    return out << '}';
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::map<T1, T2>& map) {
    out << '{';
    for (auto it = map.begin(); it != map.end(); it++) {
        std::pair<T1, T2> element = *it;
        out << element.first << ": " << element.second;
        if (std::next(it) != map.end()) {
            out << ", ";
        }
    }
    return out << '}';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::unordered_set<T>& set) {
    out << '{';
    for (auto it = set.begin(); it != set.end(); it++) {
        T element = *it;
        out << element;
        if (std::next(it) != set.end()) {
            out << ", ";
        }
    }
    return out << '}';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::multiset<T>& set) {
    out << '{';
    for (auto it = set.begin(); it != set.end(); it++) {
        T element = *it;
        out << element;
        if (std::next(it) != set.end()) {
            out << ", ";
        }
    }
    return out << '}';
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::unordered_multiset<T>& set) {
    out << '{';
    for (auto it = set.begin(); it != set.end(); it++) {
        T element = *it;
        out << element;
        if (std::next(it) != set.end()) {
            out << ", ";
        }
    }
    return out << '}';
}

template <typename T, typename C, typename A>
std::ostream& operator<<(std::ostream& out, const std::set<T, C, A>& set) {
    out << '{';
    for (auto it = set.begin(); it != set.end(); it++) {
        T element = *it;
        out << element;
        if (std::next(it) != set.end()) {
            out << ", ";
        }
    }
    return out << '}';
}

// Source: https://stackoverflow.com/a/31116392/12128483
template <typename Type, unsigned N, unsigned Last>
struct TuplePrinter {
    static void print(std::ostream& out, const Type& value) {
        out << std::get<N>(value) << ", ";
        TuplePrinter<Type, N + 1, Last>::print(out, value);
    }
};

template <typename Type, unsigned N>
struct TuplePrinter<Type, N, N> {
    static void print(std::ostream& out, const Type& value) {
        out << std::get<N>(value);
    }
};

template <typename... Types>
std::ostream& operator<<(std::ostream& out, const std::tuple<Types...>& value) {
    out << '(';
    TuplePrinter<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(out, value);
    return out << ')';
}


// STATISTER

#include <iomanip>
#include <ctime>
#include <iomanip>
#include <sys/resource.h>

struct Statistic_Tracker {
    ~Statistic_Tracker() {
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        double time = 1.0 * clock() / CLOCKS_PER_SEC;
        
        double mem = usage.ru_maxrss;
        #ifdef __APPLE__
            mem /= (1024.0 * 1024.0);
        #else
            mem /= 1024.0;
        #endif

        std::cerr << "\033[1;32m\n--------------------------------\033[0m\n";
        std::cerr << "\033[1;32mNAH I'D WIN!\033[0m | ";
        std::cerr << "\033[1;33mTime: " << std::fixed << std::setprecision(3) << time << "s\033[0m | ";
        std::cerr << "\033[1;36mMem: " << std::fixed << std::setprecision(2) << mem << "MB\033[0m\n";
    }
} __TomDev_will_AK_VOI;