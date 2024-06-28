inline int ls(int p) {return p<<1;}
inline int rs(int p) {return p<<1|1;}

inline void pushUp(int p) {
    t[p] = t[ls(p)] + t[rs(p)];
}

int t[MAXN << 2], a[MAXN << 2];
inline void build(int p, int l, int r) {
    if(l == r) {
        t[p] = a[l];
    }
    else {
        int mid = (l + r) >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        pushUp(p);
    }
}

int tag[MAXN << 2];
inline void f(int p, int k, int l, int r) {
    t[p] += k * (r - l + 1), tag[p] += k;
}
inline void pushDown(int p, int l, int r) {
    int mid = (l + r) >> 1;
    f(ls(p), tag[p], l, mid);
    f(rs(p), tag[p], mid + 1, r);
    tag[p] = 0;
}

inline void update(int nl, int nr, int l, int r, int p, int k) {
    if(nl <= l && r <= nr) {
        t[p] += k * (r - l + 1), tag[p] += k;
    }
    else {
        int mid = (l + r) >> 1;
        pushDown(p, l, r);
        if(mid >= nl) update(nl, nr, l, mid, ls(p), k);
        if(mid < nr) update(nl, nr, mid + 1, r, rs(p), k);
        pushUp(p);
    }
}

inline int query(int nl, int nr, int l, int r, int p) {
    if(nl <= l && r <= nr) return t[p];
    int mid = (l + r) >> 1, res = 0;
    pushDown(p, l, r);
    if(mid >= nl) res += query(nl, nr, l, mid, ls(p));
    if(mid < nr) res += query(nl, nr, mid + 1, r, rs(p));
    return res;
}