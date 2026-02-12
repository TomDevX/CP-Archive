/**
 *    author: TomDev - Tran Hoang Quan
 *    created: 2026-02-12 00:20:05
 *    country: Vietnam - VNM
 * ----------------------------------------------------------
 *    title: Minimum Path Sum
 *    source: https://leetcode.com/problems/minimum-path-sum
 *    submission: https://leetcode.com/problems/minimum-path-sum/submissions/1916094804
 *    status: AC
 * ----------------------------------------------------------
 *    tags: Dynamic Programming
 *    complexity: O(n \cdot m)
 *    note: Classical Grid path DP
**/

class Solution {
public:
    int minPathSum(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        vector<vector<int>> dp(n+1,vector<int>(m+1, 2e9));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]);
                if(dp[i][j] == 2e9) dp[i][j] = 0;
                dp[i][j] += a[i-1][j-1];
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cout << dp[i][j] << ' ';
            }
            cout << endl;
        }
        return dp[n][m];
    }
};