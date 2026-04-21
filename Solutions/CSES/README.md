# 📁 CSES Solutions

### 📊 CSES Stats

![Progress](https://img.shields.io/badge/Progress-33/36-4c1?style=for-the-badge&logo=target) ![Last Update](https://img.shields.io/badge/Last_Update-Apr_21%2C_2026_--_17%3A09_(GMT+7)-0078d4?style=for-the-badge&logo=github)

- **Total Unique Problems:** 36
- **Solved (AC):** 33

> 💡 **Tips:** Press `ctrl + f` (Windows) or `cmd + f` (MacOS) to search problems by ID or Name.

---
## 📌 Table of Contents

  * [📁 Advanced Techniques (2)](#-advanced-techniques-2)
  * [📁 Dynamic Programming (12)](#-dynamic-programming-12)
  * [📁 Graph (7)](#-graph-7)
  * [📁 Range Queries (10)](#-range-queries-10)
  * [📁 Sliding Windơows Problem (2)](#-sliding-windơows-problem-2)
  * [📁 Sorting and Searching (3)](#-sorting-and-searching-3)

---
### 📁 Advanced Techniques (2)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1628 - Meet in the Middle](https://cses.fi/problemset/task/1628/) | `Dynamic Programming`, `Implementation`, `Optimization` | $\mathcal{O}(2^{\frac{n}{2}} \cdot \log(\frac{n}{2}) + 2^{\frac{n}{2}} \cdot \log(\frac{n}{2}))$ | Feb 05, 2026 | [Code](Advanced%20Techniques/1628.cpp) \| [Sub](https://cses.fi/paste/39bb411c336d08d8f6c8f1/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [2136 - Hamming Distance](https://cses.fi/problemset/task/2136) | `bit` | $\mathcal{O}(n^2)$ | Feb 05, 2026 | [Code](Advanced%20Techniques/2136.cpp) \| [Sub](https://cses.fi/paste/9254599d71bb5d60f6b997/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Dynamic Programming (12)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [141 - Knapsack 2](https://marisaoj.com/problem/141) | `Dynamic Programming` | $\mathcal{O}(n \cdot S)$ | Mar 09, 2026 | [Code](Dynamic%20Programming/141.cpp) \| [Sub](https://marisaoj.com/submission/1117110) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [144 - Longest common subsequence](https://marisaoj.com/problem/144) | `Dynamic Programming` | $\mathcal{O}(n^2)$ | Mar 09, 2026 | [Code](Dynamic%20Programming/144.cpp) \| [Sub](https://marisaoj.com/submission/1117153) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [575 - Hall](https://marisaoj.com/problem/575) | `Dynamic Programming` | $\mathcal{O}(n)$ | Mar 10, 2026 | [Code](Dynamic%20Programming/575.cpp) \| [Sub](https://marisaoj.com/submission/1117926) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1140 - Projects](https://cses.fi/problemset/task/1140) | `Dynamic Programming` | $\mathcal{O}(n)$ | Feb 13, 2026 | [Code](Dynamic%20Programming/1140.cpp) \| [Sub](https://cses.fi/problemset/result/16252002/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1653-2 - Elevator Rides (Approach 2)](https://cses.fi/problemset/task/1653/) | `Dynamic Programming`, `Bitmask` | $\mathcal{O}(n \cdot 2^n)$ | Feb 16, 2026 | [Code](Dynamic%20Programming/1653-2.cpp) \| [Sub](https://cses.fi/problemset/result/16280676/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [1653 - Elevator Rides (Approach 1)](https://cses.fi/problemset/task/1653/) | `Dynamic Programming`, `Bitmask` | $\mathcal{O}(n \cdot 2^n)$ | Feb 16, 2026 | [Code](Dynamic%20Programming/1653.cpp) \| [Sub](https://cses.fi/problemset/result/16280676/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [1744 - Rectangle Cutting](https://cses.fi/problemset/task/1744) | `Dynamic Programming` | $\mathcal{O}(n \cdot m \cdot (n+m))$ | Feb 11, 2026 | [Code](Dynamic%20Programming/1744.cpp) \| [Sub](https://cses.fi/problemset/result/16234536/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 8 | [1748 - Increasing Subsequence II](https://cses.fi/problemset/task/1748) | `Dynamic Programming`, `Range Query` | $\mathcal{O}(n \log n)$ | Feb 13, 2026 | [Code](Dynamic%20Programming/1748.cpp) \| [Sub](https://cses.fi/problemset/result/16251418/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 9 | [2181 - Counting Tilings](https://cses.fi/problemset/task/2181) | `DP on Broken Profile` | $\mathcal{O}(n \cdot m \cdot 2^n)$ | Feb 17, 2026 | [Code](Dynamic%20Programming/2181.cpp) \| [Sub](https://cses.fi/problemset/result/16290752/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 10 | [2220 - Counting Numbers](https://cses.fi/problemset/task/2220) | `DP Digit` | $\mathcal{O}(digit(n) \cdot 9 \cdot 2 \cdot 2 \cdot 9)$ | Feb 18, 2026 | [Code](Dynamic%20Programming/2220.cpp) \| [Sub](https://cses.fi/problemset/result/16314439/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 11 | [2413 - Counting Towers](https://cses.fi/problemset/task/2413) | `Dynamic Programming`, `AdHoc` | $\mathcal{O}(n)$ | Feb 04, 2026 | [Code](Dynamic%20Programming/2413.cpp) \| [Sub](https://cses.fi/paste/67df7ff1543072a9f68403/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 12 | [3314 - Mountain Range](https://cses.fi/problemset/task/3314) | N/A | N/A | Feb 12, 2026 | [Code](Dynamic%20Programming/3314.cpp) | ![WIP](https://img.shields.io/static/v1?label=&message=%20%20%20WIP%20%20%20&color=007ec6&style=for-the-badge) |
| 13 | [3359 - Minimal Grid Path](https://cses.fi/problemset/task/3359) | `Dynamic Programming` | $\mathcal{O}(n \cdot m)$ | Feb 11, 2026 | [Code](Dynamic%20Programming/3359.cpp) \| [Sub](https://cses.fi/problemset/result/16238561/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Graph (7)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1192 - Counting Rooms](https://cses.fi/problemset/task/1192/) | `BFS`, `flood fill` | $\mathcal{O}(V+E)$ | Aug 09, 2025 | [Code](Graph/1192_Counting_Rooms.cpp) \| [Sub](https://cses.fi/paste/96f91e45fb63bc5dd6975e/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1195 - Flight Discount](https://cses.fi/problemset/task/1195) | `Graph`, `Dijkstra` | $\mathcal{O}((n+m) \log m)$ | Feb 23, 2026 | [Code](Graph/1195.cpp) \| [Sub](https://cses.fi/problemset/result/16352463/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [1197 - Cycle Finding](https://cses.fi/problemset/task/1197) | `Graph`, `Bellman Ford` | $\mathcal{O}(n \cdot m)$ | Feb 26, 2026 | [Code](Graph/1197.cpp) \| [Sub](https://cses.fi/problemset/result/16382838/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1668 - Building Teams](https://cses.fi/problemset/task/1668) | `Graph` | $\mathcal{O}(V + E)$ | Feb 17, 2026 | [Code](Graph/1668.cpp) \| [Sub](https://cses.fi/problemset/result/16295973/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1669 - Round Trip](https://cses.fi/problemset/task/1669) | `Graph` | $\mathcal{O}(V+E)$ | Feb 17, 2026 | [Code](Graph/1669.cpp) \| [Sub](https://cses.fi/problemset/result/16296787/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [1673 - High Score](https://cses.fi/problemset/task/1673) | `Graph`, `Bellman Ford` | $\mathcal{O}(n \cdot m)$ | Feb 23, 2026 | [Code](Graph/1673.cpp) \| [Sub](https://cses.fi/problemset/result/16352395/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [1750 - Planets Queries I](https://cses.fi/problemset/task/1750) | `Binary Lifting` | $\mathcal{O}((n+q) \log n)$ | Mar 19, 2026 | [Code](Graph/1750.cpp) \| [Sub](https://cses.fi/problemset/result/16614664/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Range Queries (10)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1143 - Hotel Queries](https://cses.fi/problemset/task/1143) | `Walk on Segment Tree` | $\mathcal{O}(n \log n)$ | Apr 04, 2026 | [Code](Range%20Queries/1143.cpp) \| [Sub](https://cses.fi/problemset/result/16790807/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1144 - Salary Queries](https://cses.fi/problemset/task/1144) | `Segment Tree` | $\mathcal{O}(n \log n)$ | Apr 09, 2026 | [Code](Range%20Queries/1144.cpp) \| [Sub](https://cses.fi/problemset/result/16849486/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [1648 - Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | `BIT` | $\mathcal{O}(n \log n)$ | Mar 26, 2026 | [Code](Range%20Queries/1648.cpp) \| [Sub](https://cses.fi/problemset/result/16686889/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1734 - Distinct Values Queries](https://cses.fi/problemset/task/1734) | `BIT`, `Distinct Value` | $\mathcal{O}(n \log n)$ | Apr 15, 2026 | [Code](Range%20Queries/1734.cpp) \| [Sub](https://cses.fi/problemset/result/16918559/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1735 - Range Updates and Sums](https://cses.fi/problemset/task/1735) | `Segment Tree Lazy` | $\mathcal{O}(n \log n)$ | Apr 10, 2026 | [Code](Range%20Queries/1735.cpp) \| [Sub](https://cses.fi/problemset/result/16866469/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [1736 - Polynomial Queries](https://cses.fi/problemset/task/1736) | `Segment Tree Lazy Polynominal` | $\mathcal{O}(n \log n)$ | Apr 11, 2026 | [Code](Range%20Queries/1736.cpp) \| [Sub](https://cses.fi/problemset/result/16867163/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [1749 - List Removals - Fenwick Tree (BIT) Approach](https://cses.fi/problemset/task/1749/) | `Walk on BIT` | $\mathcal{O}(n \log n)$ | Apr 04, 2026 | [Code](Range%20Queries/1749_BIT.cpp) \| [Sub](https://cses.fi/problemset/result/16793996) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 8 | [1749 - List Removals - Segment Tree Approach](https://cses.fi/problemset/task/1749/) | `Walk on Segment Tree` | $\mathcal{O}(n \log n)$ | Apr 04, 2026 | [Code](Range%20Queries/1749_segtree.cpp) \| [Sub](https://cses.fi/problemset/result/16793927/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 9 | [2166 - Prefix Sum Queries](https://cses.fi/problemset/task/2166) | N/A | N/A | Apr 11, 2026 | [Code](Range%20Queries/2166.cpp) | ![WIP](https://img.shields.io/static/v1?label=&message=%20%20%20WIP%20%20%20&color=007ec6&style=for-the-badge) |
| 10 | [2184 - Missing Coin Sum Queries](https://cses.fi/problemset/task/2184) | `Sparse Table`, `MEX`, `bit` | $\mathcal{O}(n \log n \log a_i)$ | Mar 25, 2026 | [Code](Range%20Queries/2184.cpp) \| [Sub](https://cses.fi/problemset/result/16681741/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 11 | [3226 - Subarray Sum Queries II](https://cses.fi/problemset/task/3226) | `Segment Tree (Custom Operator)` | $\mathcal{O}(n \log n)$ | Apr 08, 2026 | [Code](Range%20Queries/3226.cpp) \| [Sub](https://cses.fi/problemset/result/16838741/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Sliding Windơows Problem (2)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1076 - Sliding Window Median](https://cses.fi/problemset/task/1076) | `Walk on BIT` | $\mathcal{O}(n \log n)$ | Apr 05, 2026 | [Code](Sliding%20Windơows%20Problem/1076.cpp) \| [Sub](https://cses.fi/problemset/result/16803462/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [3220 - Sliding Window Sum](https://cses.fi/problemset/task/3220) | N/A | N/A | Feb 11, 2026 | [Code](Sliding%20Windơows%20Problem/3220.cpp) | ![WIP](https://img.shields.io/static/v1?label=&message=%20%20%20WIP%20%20%20&color=007ec6&style=for-the-badge) |

### 📁 Sorting and Searching (3)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1645 - Nearest Smaller Values](https://cses.fi/problemset/task/1645) | `Adhoc` | $\mathcal{O}(n)$ | Feb 18, 2026 | [Code](Sorting%20and%20Searching/1645.cpp) \| [Sub](https://cses.fi/problemset/result/16306582/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [2216 - Collecting Numbers](https://cses.fi/problemset/task/2216) | `Implementation` | $\mathcal{O}(n)$ | Feb 10, 2026 | [Code](Sorting%20and%20Searching/2216.cpp) \| [Sub](https://cses.fi/problemset/result/16218047/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [2217 - Collecting Numbers II](https://cses.fi/problemset/task/2217) | `Adhoc` | $\mathcal{O}(n + m)$ | Feb 10, 2026 | [Code](Sorting%20and%20Searching/2217.cpp) \| [Sub](https://cses.fi/problemset/result/16218382/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

