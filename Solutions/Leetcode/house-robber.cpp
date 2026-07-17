/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-05-31 14:59:42
 *    country: Vietnam - VNM
 *    repo: github.com/TomDevX/CP-Archive
 * ----------------------------------------------------------
 *    title: 198. House Robber
 *    source: https://leetcode.com/problems/house-robber
 *    submission: https://leetcode.com/problems/house-robber/submissions/2017960473
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n)
 *    note: Just get some dp cases about the adjacent ones
**/

class Solution {
public:
    int rob(vector<int>& a) {
        int n = a.size();
        vector<int> dp(n);
        for(int i = 0; i < n; i++){
            dp[i] = max((i-2 >= 0 ? dp[i-2] : 0), i-3 >= 0 ? dp[i-3] : 0) + a[i];
        }
        return max(dp[n-1], (n-2 >= 0 ? dp[n-2] : 0));
    }
};