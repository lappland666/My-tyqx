#include "mymath.h"
#include <cstdio>
/* 计算a的k次方模mod */
ll ksm(ll a, ll k, ll mod)
{
    ll result = 1;
    ll temp = a % mod;
    while(k)
    {
        if(k & 1)
        {
            result = ((result % mod) * (temp % mod)) % mod;
        }
        k >>= 1;
        temp = ((temp % mod) * (temp % mod)) % mod;
    }
    return result;
}

/* 求出xa+yp=1, x即为a模p的逆 */
void h(ll a, ll p, ll& x, ll& y)
{
    if(p == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    h(p, a % p, x, y);
    ll x1 = y;
    ll y1 = x - (a / p) * y;
    x = x1;
    y = y1;
}

/* 计算a模p的逆元 */
ll f(ll a, ll p)
{
    ll x, y;
    a = (a % p + p) % p;
    h(a, p, x, y);
    x = (x % p + p) % p;
    return x;
}

/* 椭圆曲线点加法 */
Node sum(Node n1, Node n2, ll a, ll b, ll p)
{
    if(n1.isFar()) return n2;
    if(n2.isFar()) return n1;
    
    ll x1 = (n1.x + p) % p;
    ll y1 = (n1.y + p) % p;
    ll x2 = (n2.x + p) % p;
    ll y2 = (n2.y + p) % p;
    
    if(x2 != x1)
    {
        ll k = ((((y2 - y1) % p + p) % p) * f(x2 - x1, p)) % p;
        ll x3 = ((k * k) % p - x1 - x2) % p;
        ll y3 = (k * (x1 - x3) - y1) % p;
        x3 = (x3 % p + p) % p;
        y3 = (y3 % p + p) % p;
        return Node(x3, y3);
    }
    else
    {
        if((y2 + y1) % p == 0)
        {
            return Node(-1, -1);
        }
        else
        {
            ll k = ((3 * x1 * x1 + a) * f(2 * y1, p)) % p;
            ll x3 = ((k * k % p) - x1 - x2) % p;
            ll y3 = (k * (x1 - x3) - y1) % p;
            x3 = (x3 % p + p) % p;
            y3 = (y3 % p + p) % p;
            return Node(x3, y3);
        }
    }
}

/* 倍加计算dP */
Node mul(ll d, Node P, ll a, ll b, ll p)
{
    Node ans(-1, -1);
    while(d)
    {
        if(d & 1)
        {
            ans = sum(ans, P, a, b, p);
        }
        d >>= 1;
        P = sum(P, P, a, b, p);
    }
    if(ans.isFar()) return ans;
    
    while(ans.x < 0) ans.x += p;
    while(ans.y < 0) ans.y += p;
    
    return ans;
}

// ========== 7个核心功能实现 ==========

/* 1. 判断E_p(a,b)是否为椭圆曲线 */
bool pdqx(ll a, ll b, ll p)
{
    if(p <= 3) return false;
    
    ll delta = (4 * ksm(a, 3, p) + 27 * ksm(b, 2, p)) % p;
    delta = (delta % p + p) % p;
    
    return delta != 0;
}

/* 2. 判断给定的点P是否在椭圆曲线E_p(a,b)上 */
bool pd(Node point, ll a, ll b, ll p)
{
    if(point.isFar()) return true;
    
    ll x = point.x;
    ll y = point.y;
    
    x = (x % p + p) % p;
    y = (y % p + p) % p;
    
    ll zuo = (y * y) % p;
    ll you = (ksm(x, 3, p) + a * x % p + b) % p;
    you = (you % p + p) % p;
    
    return zuo == you;
}

/* 3. 对在椭圆曲线E_p(a,b)上的两点P,Q，计算P+Q */
Node pdjf(Node P, Node Q, ll a, ll b, ll p)
{
    // 先检查点是否在曲线上
    if(!P.isFar() && !pd(P, a, b, p))
    {
        printf("错误：点");
        P.show();
        printf("不在曲线上！\n");
        return Node(-1, -1);
    }
    if(!Q.isFar() && !pd(Q, a, b, p))
    {
        printf("错误：点");
        Q.show();
        printf("不在曲线上！\n");
        return Node(-1, -1);
    }
    
    return sum(P, Q, a, b, p);
}

/* 4. 对在椭圆曲线E_p(a,b)上的点P，使用倍加-和算法计算mP */
Node jsdb(ll m, Node P, ll a, ll b, ll p)
{
    if(!P.isFar() && !pd(P, a, b, p))
    {
        printf("错误：点");
        P.show();
        printf("不在曲线上！\n");
        return Node(-1, -1);
    }
    
    return mul(m, P, a, b, p);
}

/* 5. 对在椭圆曲线E_p(a,b)上的点P，计算Word(P) */
ll jsdj(Node P, ll a, ll b, ll p)
{
    if(!P.isFar() && !pd(P, a, b, p))
    {
        printf("错误：点");
        P.show();
        printf("不在曲线上！\n");
        return 0;
    }
    
    if(P.isFar()) return 1;
    
    ll jd = 1;
    Node temp = P;
    
    while(!temp.isFar())
    {
        temp = sum(temp, P, a, b, p);
        jd++;
    }
    
    return jd;
}

/* 6. 对椭圆曲线E_p(a,b)，计算阶数E */
ll jsqxj(ll a, ll b, ll p)
{
    if(!pdqx(a, b, p))
    {
        printf("错误：这不是椭圆曲线！\n");
        return 0;
    }
    
    ll gs = 1;  // 包括无穷远点
    
    for(ll x = 0; x < p; x++)
    {
        ll zhi = (ksm(x, 3, p) + a * x % p + b) % p;
        zhi = (zhi % p + p) % p;
        
        int jg = 0;
        for(ll y = 0; y < p; y++)
        {
            if((y * y) % p == zhi)
            {
                jg++;
            }
        }
        
        if(jg > 0)
        {
            gs += jg;
        }
    }
    
    return gs;
}

/* 7. 对椭圆曲线E_p(a,b)，计算所有点 */
void scqxsd(ll a, ll b, ll p)
{
    if(!pdqx(a, b, p))
    {
        printf("错误：这不是椭圆曲线！\n");
        return;
    }
    
    printf("椭圆曲线 E_%lld(%lld,%lld) 上的所有点：\n", p, a, b);
    printf("1. O (无穷远点)\n");
    
    int gs = 1;
    int dh = 2;  // 点号从2开始
    
    for(ll x = 0; x < p; x++)
    {
        ll zhi = (ksm(x, 3, p) + a * x % p + b) % p;
        zhi = (zhi % p + p) % p;
        
        for(ll y = 0; y < p; y++)
        {
            if((y * y) % p == zhi)
            {
                printf("%d. (%lld, %lld)\n", dh, x, y);
                gs++;
                dh++;
            }
        }
    }
    
    printf("总点数（包括无穷远点）：%d\n", gs);
}