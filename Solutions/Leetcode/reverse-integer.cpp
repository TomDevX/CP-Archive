/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-04-11 23:23:04
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: 
 *    source: 
 *    submission: 
 *    status: WIP
 * ----------------------------------------------------------
 *    tags: 
 *    complexity: 
 *    note: 
**/

class Solution {
public:
    // const long long INF = ((1LL << 31)-1), NINF = -(1LL << 31);
    int reverse(int x) {
        long long ans = 0;
        while(x){
            ans = ans*10 + x%10;
            x /= 10;
        }
        return (ans <= INT_MAX && ans >= INT_MIN ? ans : 0);
    }
};