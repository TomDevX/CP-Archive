int nNode = 1;
const int N = 2e5+2;

struct node{
    int cnt, l, r;

    node(int _cnt = 0, int _l = 0, int _r = 0) : cnt(_cnt), l(_l), r(_r) {};
};

vector<node> st(30*N);

// ----------------------- [ FUNCTIONS ] -----------------------
void update(int id, int l, int r, int pos, int val){
    if(l == r){
        st[id].cnt += val;
        return;
    }

    int mid = l + ((r-l)>>1);

    if(pos <= mid){
        if(!st[id].l) st[id].l = ++nNode;
        update(st[id].l,l,mid,pos,val);    
    }
    else{
        if(!st[id].r) st[id].r = ++nNode;
        update(st[id].r, mid + 1, r, pos, val);
    }

    st[id].cnt = st[st[id].l].cnt + st[st[id].r].cnt;
}

int query(int id, int l, int r, int u, int v){
    if(l > v || r < u) return 0;
    if(l >= u && r <= v) return st[id].cnt;

    int mid = l + ((r-l)>>1);

    int ans = 0;
    if(st[id].l) ans += query(st[id].l,l,mid,u,v);
    if(st[id].r) ans += query(st[id].r,mid+1,r,u,v);

    return ans;
}