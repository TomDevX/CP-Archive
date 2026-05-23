#include <bits/stdc++.h>
using namespace std;
#define ll long long

void open()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

}

int t;

void sol()
{
    if(!fopen("input.inp", "r")) return;
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    ll n;
    cin>>n;
    vector<ll> a(n+5);
    vector<ll> notprefix(n+5);
    bool ok1=0,ok2=0;
    ll t = 0;
    for(int i =0;i<n;i++)
    {
        cin>>a[i];
        if(a[i]>0)ok1=1;
        else ok2=1;
        t = t + a[i];
    }
    if(ok1==0 || ok2==0)
    {
        cout<<0<<'\n'<<'\n';
        return;
    }

    notprefix[n]=0;
    for(int i = n-1;i>=0;i--)
    {
        notprefix[i]=notprefix[i+1]+a[i];
    }

    vector<ll> ans,tmp;
    bool ok = 0;
    ll i = 0;
    ll sumtmp=0;
    while(a[i]>0)
    {
        sumtmp = sumtmp+a[i];
        i++;
    }
    ll pre_Loves_Only_You = i;
    while(i<n)
    {
        while(i<n&&a[i]<0)
        {
            sumtmp-=a[i];
            i++;
        }
        if(i==n)break;
        if(pre_Loves_Only_You != 0)tmp.push_back(pre_Loves_Only_You);
        tmp.push_back(i+1);
        pre_Loves_Only_You = i;

        if(sumtmp-a[i]+notprefix[i+1]>t)
        {
            t = sumtmp-a[i]+notprefix[i+1];
            while(ans.size()<tmp.size())
            {
                ans.push_back(tmp[ans.size()]);
            }
        }
        sumtmp+=a[i];
        i++;
    }
        cout<<ans.size()<<'\n';
        for(auto &it : ans)
        {
            cout<<it<<" ";
        }
        cout<<'\n';
}

int main() {
   // open();
    cin>>t;
    while(t--)
    {
        sol();

    }

}
