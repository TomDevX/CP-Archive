# 📁 CSES Solutions

### 📊 CSES Stats

![Progress](https://img.shields.io/badge/Progress-60/62-4c1?style=for-the-badge&logo=target) ![Last Update](https://img.shields.io/badge/Last_Update-Jul_22%2C_2026_--_17%3A14_(GMT+7)-0078d4?style=for-the-badge&logo=github)

- **Total Unique Problems:** 62
- **Solved (AC):** 60

> 💡 **Tips:** Press `ctrl + f` (Windows) or `cmd + f` (MacOS) to search problems by ID or Name.

---
## 📌 Table of Contents

* [📁 CSES (62)](#-cses-62)
  * [📁 Advanced Techniques (2)](#-advanced-techniques-2)
  * [📁 Dynamic Programming (12)](#-dynamic-programming-12)
  * [📁 Geometry (6)](#-geometry-6)
  * [📁 Graph (10)](#-graph-10)
  * [📁 Mathematics (9)](#-mathematics-9)
  * [📁 Range Queries (10)](#-range-queries-10)
  * [📁 Sliding Windơows Problem (2)](#-sliding-windơows-problem-2)
  * [📁 Sorting and Searching (4)](#-sorting-and-searching-4)
  * [📁 String (6)](#-string-6)

---
## 📂 CSES (62)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [2421 - Counting Reorders](https://cses.fi/problemset/task/2421) | `DP`, `Inclusion-Exclusion`, `Math` | ${\mathcal{O}(26 \cdot n^2)}$ | Jul&nbsp;18,&nbsp;2026 | [Code](2421.cpp) \| [Sub](https://cses.fi/problemset/result/17982326/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Advanced Techniques (2)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1628 - Meet in the Middle](https://cses.fi/problemset/task/1628/) | `Dynamic Programming`, `Implementation`, `Optimization` | ${\mathcal{O}(2^{\frac{n}{2}} \cdot \log(\frac{n}{2}) + 2^{\frac{n}{2}} \cdot \log(\frac{n}{2}))}$ | Feb&nbsp;05,&nbsp;2026 | [Code](Advanced%20Techniques/1628.cpp) \| [Sub](https://cses.fi/paste/39bb411c336d08d8f6c8f1/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [2136 - Hamming Distance](https://cses.fi/problemset/task/2136) | `bit` | ${\mathcal{O}(n^2)}$ | Feb&nbsp;05,&nbsp;2026 | [Code](Advanced%20Techniques/2136.cpp) \| [Sub](https://cses.fi/paste/9254599d71bb5d60f6b997/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Dynamic Programming (12)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [141 - Knapsack 2](https://marisaoj.com/problem/141) | `Dynamic Programming` | ${\mathcal{O}(n \cdot S)}$ | Mar&nbsp;09,&nbsp;2026 | [Code](Dynamic%20Programming/141.cpp) \| [Sub](https://marisaoj.com/submission/1117110) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [144 - Longest common subsequence](https://marisaoj.com/problem/144) | `Dynamic Programming` | ${\mathcal{O}(n^2)}$ | Mar&nbsp;09,&nbsp;2026 | [Code](Dynamic%20Programming/144.cpp) \| [Sub](https://marisaoj.com/submission/1117153) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [575 - Hall](https://marisaoj.com/problem/575) | `Dynamic Programming` | ${\mathcal{O}(n)}$ | Mar&nbsp;10,&nbsp;2026 | [Code](Dynamic%20Programming/575.cpp) \| [Sub](https://marisaoj.com/submission/1117926) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1140 - Projects](https://cses.fi/problemset/task/1140) | `Dynamic Programming` | ${\mathcal{O}(n)}$ | Feb&nbsp;13,&nbsp;2026 | [Code](Dynamic%20Programming/1140.cpp) \| [Sub](https://cses.fi/problemset/result/16252002/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1653-2 - Elevator Rides (Approach 2)](https://cses.fi/problemset/task/1653/) | `Dynamic Programming`, `Bitmask` | ${\mathcal{O}(n \cdot 2^n)}$ | Feb&nbsp;16,&nbsp;2026 | [Code](Dynamic%20Programming/1653-2.cpp) \| [Sub](https://cses.fi/problemset/result/16280676/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [1653 - Elevator Rides (Approach 1)](https://cses.fi/problemset/task/1653/) | `Dynamic Programming`, `Bitmask` | ${\mathcal{O}(n \cdot 2^n)}$ | Feb&nbsp;16,&nbsp;2026 | [Code](Dynamic%20Programming/1653.cpp) \| [Sub](https://cses.fi/problemset/result/16280676/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [1744 - Rectangle Cutting](https://cses.fi/problemset/task/1744) | `Dynamic Programming` | ${\mathcal{O}(n \cdot m \cdot (n+m))}$ | Feb&nbsp;11,&nbsp;2026 | [Code](Dynamic%20Programming/1744.cpp) \| [Sub](https://cses.fi/problemset/result/16234536/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 8 | [1748 - Increasing Subsequence II](https://cses.fi/problemset/task/1748) | `Dynamic Programming`, `Range Query` | ${\mathcal{O}(n \log n)}$ | Feb&nbsp;13,&nbsp;2026 | [Code](Dynamic%20Programming/1748.cpp) \| [Sub](https://cses.fi/problemset/result/16251418/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 9 | [2181 - Counting Tilings](https://cses.fi/problemset/task/2181) | `DP on Broken Profile` | ${\mathcal{O}(n \cdot m \cdot 2^n)}$ | Feb&nbsp;17,&nbsp;2026 | [Code](Dynamic%20Programming/2181.cpp) \| [Sub](https://cses.fi/problemset/result/16290752/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 10 | [2220 - Counting Numbers](https://cses.fi/problemset/task/2220) | `DP Digit` | ${\mathcal{O}(digit(n) \cdot 9 \cdot 2 \cdot 2 \cdot 9)}$ | Feb&nbsp;18,&nbsp;2026 | [Code](Dynamic%20Programming/2220.cpp) \| [Sub](https://cses.fi/problemset/result/16314439/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 11 | [2413 - Counting Towers](https://cses.fi/problemset/task/2413) | `Dynamic Programming`, `AdHoc` | ${\mathcal{O}(n)}$ | Feb&nbsp;04,&nbsp;2026 | [Code](Dynamic%20Programming/2413.cpp) \| [Sub](https://cses.fi/paste/67df7ff1543072a9f68403/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 12 | [3314 - Mountain Range](https://cses.fi/problemset/task/3314) | N/A | N/A | Feb&nbsp;12,&nbsp;2026 | [Code](Dynamic%20Programming/3314.cpp) | ![WIP](https://img.shields.io/static/v1?label=&message=%20%20%20WIP%20%20%20&color=007ec6&style=for-the-badge) |
| 13 | [3359 - Minimal Grid Path](https://cses.fi/problemset/task/3359) | `Dynamic Programming` | ${\mathcal{O}(n \cdot m)}$ | Feb&nbsp;11,&nbsp;2026 | [Code](Dynamic%20Programming/3359.cpp) \| [Sub](https://cses.fi/problemset/result/16238561/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Geometry (6)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1740 - Intersection Points](https://cses.fi/problemset/task/1740/) | `Sweep Line 2D`, `Geometry`, `BIT` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;24,&nbsp;2026 | [Code](Geometry/1740.cpp) \| [Sub](https://cses.fi/problemset/result/16999159/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1741 - Area of Rectangles](https://cses.fi/problemset/task/1741/) | `Sweep Line 2D`, `Segment Tree`, `Geometry` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;25,&nbsp;2026 | [Code](Geometry/1741.cpp) \| [Sub](https://cses.fi/problemset/result/16999445/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [2189 - Point Location Test](https://cses.fi/problemset/task/2189) | `Geometry` | ${\mathcal{O}(1)}$ | Apr&nbsp;24,&nbsp;2026 | [Code](Geometry/2189.cpp) \| [Sub](https://cses.fi/problemset/result/16997530/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [2191 - Polygon Area](https://cses.fi/problemset/task/2191/) | `Geometry` | ${\mathcal{O}(n)}$ | Apr&nbsp;24,&nbsp;2026 | [Code](Geometry/2191.cpp) \| [Sub](https://cses.fi/problemset/result/16997561/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [2192 - Point in Polygon](https://cses.fi/problemset/task/2192/) | `Geometry` | ${\mathcal{O}(n)}$ | Apr&nbsp;24,&nbsp;2026 | [Code](Geometry/2192.cpp) \| [Sub](https://cses.fi/problemset/result/16998419/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [2193 - Polygon Lattice Points](https://cses.fi/problemset/task/2193/) | `Geometry` | ${\mathcal{O}(n)}$ | Apr&nbsp;24,&nbsp;2026 | [Code](Geometry/2193.cpp) \| [Sub](https://cses.fi/problemset/result/16998036/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Graph (10)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1192 - Counting Rooms](https://cses.fi/problemset/task/1192/) | `BFS`, `flood fill` | ${\mathcal{O}(V+E)}$ | Aug&nbsp;09,&nbsp;2025 | [Code](Graph/1192_Counting_Rooms.cpp) \| [Sub](https://cses.fi/paste/96f91e45fb63bc5dd6975e/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1195 - Flight Discount](https://cses.fi/problemset/task/1195) | `Graph`, `Dijkstra` | ${\mathcal{O}((n+m) \log m)}$ | Feb&nbsp;23,&nbsp;2026 | [Code](Graph/1195.cpp) \| [Sub](https://cses.fi/problemset/result/16352463/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [1197 - Cycle Finding](https://cses.fi/problemset/task/1197) | `Graph`, `Bellman Ford` | ${\mathcal{O}(n \cdot m)}$ | Feb&nbsp;26,&nbsp;2026 | [Code](Graph/1197.cpp) \| [Sub](https://cses.fi/problemset/result/16382838/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1668 - Building Teams](https://cses.fi/problemset/task/1668) | `Graph` | ${\mathcal{O}(V + E)}$ | Feb&nbsp;17,&nbsp;2026 | [Code](Graph/1668.cpp) \| [Sub](https://cses.fi/problemset/result/16295973/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1669 - Round Trip](https://cses.fi/problemset/task/1669) | `Graph` | ${\mathcal{O}(V+E)}$ | Feb&nbsp;17,&nbsp;2026 | [Code](Graph/1669.cpp) \| [Sub](https://cses.fi/problemset/result/16296787/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [1673 - High Score](https://cses.fi/problemset/task/1673) | `Graph`, `Bellman Ford` | ${\mathcal{O}(n \cdot m)}$ | Feb&nbsp;23,&nbsp;2026 | [Code](Graph/1673.cpp) \| [Sub](https://cses.fi/problemset/result/16352395/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [1679 - Course Schedule](https://cses.fi/problemset/task/1679/) | `Topo Sort` | ${\mathcal{O}(n)}$ | Jun&nbsp;06,&nbsp;2026 | [Code](Graph/1679.cpp) \| [Sub](https://cses.fi/problemset/result/17444915/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 8 | [1680 - Longest Flight Route](https://cses.fi/problemset/task/1680) | `Topo Sort`, `DP on DAG` | ${\mathcal{O}(n)}$ | Jun&nbsp;06,&nbsp;2026 | [Code](Graph/1680.cpp) \| [Sub](https://cses.fi/problemset/result/17445496/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 9 | [1681 - Game Routes](https://cses.fi/problemset/task/1681) | `Topo Sort`, `DP on DAG` | ${\mathcal{O}(n)}$ | Jun&nbsp;06,&nbsp;2026 | [Code](Graph/1681.cpp) \| [Sub](https://cses.fi/problemset/result/17445572/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 10 | [1750 - Planets Queries I](https://cses.fi/problemset/task/1750) | `Binary Lifting` | ${\mathcal{O}((n+q) \log n)}$ | Mar&nbsp;19,&nbsp;2026 | [Code](Graph/1750.cpp) \| [Sub](https://cses.fi/problemset/result/16614664/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Mathematics (9)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1008B - Turn the Rectangles](https://codeforces.com/contest/1008/problem/B) | `Implementation` | ${\mathcal{O}(n)}$ | Jul&nbsp;04,&nbsp;2026 | [Code](Mathematics/1008B.cpp) \| [Sub](https://codeforces.com/contest/1008/submission/381165532) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1081 - Common Divisors](https://cses.fi/problemset/task/1081/) | `Math` | ${\mathcal{O}(n \log n)}$ | Jun&nbsp;07,&nbsp;2026 | [Code](Mathematics/1081.cpp) \| [Sub](https://cses.fi/problemset/result/17462328/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [1082 - Sum of Divisors](https://cses.fi/problemset/task/1082) | `Math` | ${\mathcal{O}(\sqrt{n})}$ | Jun&nbsp;14,&nbsp;2026 | [Code](Mathematics/1082.cpp) \| [Sub](https://cses.fi/problemset/result/17568179/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1099 - Stair Game](https://cses.fi/problemset/task/1099) | `Game theory`, `Nim` | ${\mathcal{O}(n)}$ | Jul&nbsp;03,&nbsp;2026 | [Code](Mathematics/1099.cpp) \| [Sub](https://cses.fi/problemset/result/17810407/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1802B - Settlement of Guinea Pigs](https://codeforces.com/contest/1802/problem/B) | `Implementation` | ${\mathcal{O}(n)}$ | Jul&nbsp;03,&nbsp;2026 | [Code](Mathematics/1802B.cpp) \| [Sub](https://codeforces.com/contest/1802/submission/381162052) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [2064 - Bracket Sequences I](https://cses.fi/problemset/task/2064) | `Math`, `Catalan` | ${\mathcal{O}(n)}$ | Jun&nbsp;30,&nbsp;2026 | [Code](Mathematics/2064.cpp) \| [Sub](https://cses.fi/problemset/result/17761466/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [2182 - Divisor Analysis](https://cses.fi/problemset/task/2182/) | `Math` | ${\mathcal{O}(n \log k)}$ | Jun&nbsp;24,&nbsp;2026 | [Code](Mathematics/2182.cpp) \| [Sub](https://cses.fi/problemset/result/17688457/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 8 | [2207 - Grundy's Game](https://cses.fi/problemset/task/2207) | N/A | N/A | Jul&nbsp;04,&nbsp;2026 | [Code](Mathematics/2207.cpp) | ![WIP](https://img.shields.io/static/v1?label=&message=%20%20%20WIP%20%20%20&color=007ec6&style=for-the-badge) |
| 9 | [3398 - Permutation Rounds](https://cses.fi/problemset/task/3398) | `Math` | ${\mathcal{O}(n \log n)}$ | Jun&nbsp;07,&nbsp;2026 | [Code](Mathematics/3398.cpp) \| [Sub](https://cses.fi/problemset/result/17461968/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Range Queries (10)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1143 - Hotel Queries](https://cses.fi/problemset/task/1143) | `Walk on Segment Tree` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;04,&nbsp;2026 | [Code](Range%20Queries/1143.cpp) \| [Sub](https://cses.fi/problemset/result/16790807/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1144 - Salary Queries](https://cses.fi/problemset/task/1144) | `Segment Tree` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;09,&nbsp;2026 | [Code](Range%20Queries/1144.cpp) \| [Sub](https://cses.fi/problemset/result/16849486/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [1648 - Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | `BIT` | ${\mathcal{O}(n \log n)}$ | Mar&nbsp;26,&nbsp;2026 | [Code](Range%20Queries/1648.cpp) \| [Sub](https://cses.fi/problemset/result/16686889/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1734 - Distinct Values Queries](https://cses.fi/problemset/task/1734) | `BIT`, `Distinct Value` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;15,&nbsp;2026 | [Code](Range%20Queries/1734.cpp) \| [Sub](https://cses.fi/problemset/result/16918559/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1735 - Range Updates and Sums](https://cses.fi/problemset/task/1735) | `Segment Tree Lazy` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;10,&nbsp;2026 | [Code](Range%20Queries/1735.cpp) \| [Sub](https://cses.fi/problemset/result/16866469/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [1736 - Polynomial Queries](https://cses.fi/problemset/task/1736) | `Segment Tree Lazy Polynominal` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;11,&nbsp;2026 | [Code](Range%20Queries/1736.cpp) \| [Sub](https://cses.fi/problemset/result/16867163/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 7 | [1749 - List Removals - Fenwick Tree (BIT) Approach](https://cses.fi/problemset/task/1749/) | `Walk on BIT` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;04,&nbsp;2026 | [Code](Range%20Queries/1749_BIT.cpp) \| [Sub](https://cses.fi/problemset/result/16793996) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 8 | [1749 - List Removals - Segment Tree Approach](https://cses.fi/problemset/task/1749/) | `Walk on Segment Tree` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;04,&nbsp;2026 | [Code](Range%20Queries/1749_segtree.cpp) \| [Sub](https://cses.fi/problemset/result/16793927/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 9 | [2166 - Prefix Sum Queries](https://cses.fi/problemset/task/2166) | `Segment Tree` | ${\mathcal{O}(n \log n)}$ | May&nbsp;03,&nbsp;2026 | [Code](Range%20Queries/2166.cpp) \| [Sub](https://cses.fi/problemset/result/17063144/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 10 | [2184 - Missing Coin Sum Queries](https://cses.fi/problemset/task/2184) | `Sparse Table`, `MEX`, `bit` | ${\mathcal{O}(n \log n \log a_i)}$ | Mar&nbsp;25,&nbsp;2026 | [Code](Range%20Queries/2184.cpp) \| [Sub](https://cses.fi/problemset/result/16681741/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 11 | [3226 - Subarray Sum Queries II](https://cses.fi/problemset/task/3226) | `Segment Tree (Custom Operator)` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;08,&nbsp;2026 | [Code](Range%20Queries/3226.cpp) \| [Sub](https://cses.fi/problemset/result/16838741/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Sliding Windơows Problem (2)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1076 - Sliding Window Median](https://cses.fi/problemset/task/1076) | `Walk on BIT` | ${\mathcal{O}(n \log n)}$ | Apr&nbsp;05,&nbsp;2026 | [Code](Sliding%20Windơows%20Problem/1076.cpp) \| [Sub](https://cses.fi/problemset/result/16803462/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [3220 - Sliding Window Sum](https://cses.fi/problemset/task/3220) | `Sliding Windows` | ${\mathcal{O}(n)}$ | May&nbsp;03,&nbsp;2026 | [Code](Sliding%20Windơows%20Problem/3220.cpp) \| [Sub](https://cses.fi/problemset/result/17062878/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 Sorting and Searching (4)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1085 - Array Division](https://cses.fi/problemset/task/1085) | `Binary Search on Answer` | ${\mathcal{O}(n \log n)}$ | Jun&nbsp;09,&nbsp;2026 | [Code](Sorting%20and%20Searching/1085.cpp) \| [Sub](https://cses.fi/problemset/result/17482976/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1645 - Nearest Smaller Values](https://cses.fi/problemset/task/1645) | `Adhoc` | ${\mathcal{O}(n)}$ | Feb&nbsp;18,&nbsp;2026 | [Code](Sorting%20and%20Searching/1645.cpp) \| [Sub](https://cses.fi/problemset/result/16306582/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [2216 - Collecting Numbers](https://cses.fi/problemset/task/2216) | `Implementation` | ${\mathcal{O}(n)}$ | Feb&nbsp;10,&nbsp;2026 | [Code](Sorting%20and%20Searching/2216.cpp) \| [Sub](https://cses.fi/problemset/result/16218047/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [2217 - Collecting Numbers II](https://cses.fi/problemset/task/2217) | `Adhoc` | ${\mathcal{O}(n + m)}$ | Feb&nbsp;10,&nbsp;2026 | [Code](Sorting%20and%20Searching/2217.cpp) \| [Sub](https://cses.fi/problemset/result/16218382/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

### 📁 String (6)
| # | Problem Name | Tags | Complexity | Date | Solution | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | [1110-2 - Minimal Rotation - Approach 2](https://cses.fi/problemset/task/1110/) | `Booth's algorithm` | ${\mathcal{O}(n)}$ | May&nbsp;21,&nbsp;2026 | [Code](String/1110-2.cpp) \| [Sub](https://cses.fi/problemset/result/17246433/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 2 | [1110 - Minimal Rotation](https://cses.fi/problemset/task/1110) | `Hash` | ${\mathcal{O}(n \log n)}$ | May&nbsp;20,&nbsp;2026 | [Code](String/1110.cpp) \| [Sub](https://cses.fi/problemset/result/17233962/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 3 | [1732-2 - Finding Borders - Approach 2](https://cses.fi/problemset/result/17204250/) | `Hash` | ${\mathcal{O}(n)}$ | May&nbsp;17,&nbsp;2026 | [Code](String/1732-2.cpp) \| [Sub](https://cses.fi/problemset/result/17204343/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 4 | [1732 - Finding Borders - Approach 1](https://cses.fi/problemset/task/1732) | `Z-func` | ${\mathcal{O}(n)}$ | May&nbsp;17,&nbsp;2026 | [Code](String/1732.cpp) \| [Sub](https://cses.fi/problemset/result/17204250/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 5 | [1733 - Finding Periods](https://cses.fi/problemset/task/1733) | `Hash` | ${\mathcal{O}(n)}$ | May&nbsp;17,&nbsp;2026 | [Code](String/1733.cpp) \| [Sub](https://cses.fi/problemset/result/17204580/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |
| 6 | [2420 - Palindrome Queries](https://cses.fi/problemset/task/2420) | `Hash`, `Segment Tree` | ${\mathcal{O}(n \log n)}$ | May&nbsp;21,&nbsp;2026 | [Code](String/2420.cpp) \| [Sub](https://cses.fi/problemset/result/17253771/) | ![AC](https://img.shields.io/static/v1?label=&message=%20%20%20AC%20%20%20&color=4c1&style=for-the-badge) |

