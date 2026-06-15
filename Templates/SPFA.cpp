void SPFA(int src){
    dis[src] = 0;
    deque<int> qu;
 
    qu.push_back(src);
    cnt[src] = 1;
    inqueue[src] = 1;
 
    while(!qu.empty()){
        int u = qu.front();
        qu.pop_front();
        inqueue[u] = 0;
 
        for(pair<int,ll> p : adj1[u]){
            if(dis[p.fi] > dis[u] + p.se){
                dis[p.fi] = dis[u] + p.se;
 
                if(!inqueue[p.fi]){
                    cnt[p.fi]++;
                    if(cnt[p.fi] > n && vis1[p.fi] && vis2[p.fi]){
                        dis[n] = 1; // unavailble
                        return;
                    }
                    if(cnt[p.fi] > n) continue;

                    if(!qu.empty() && dis[p.fi] < dis[qu.front()]){
                        qu.push_front(p.fi);
                    }
                    else qu.push_back(p.fi);

                    inqueue[p.fi] = 1;
                }
            }
        }
    }
}