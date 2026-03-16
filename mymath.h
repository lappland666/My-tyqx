#pragma once
#include <iostream>
#define ll long long
// 椭圆曲线点结构
class Node {
public:
    ll x, y;
    
    Node(ll x = -1, ll y = -1) : x(x), y(y) {}
    
    bool isFar() const {
        return x == -1 && y == -1;
    }
    
    // 显示点信息
    void show() const {
        if (isFar()) {
            std::cout << "O(无穷远点)";
        } else {
            std::cout << "(" << x << "," << y << ")";
        }
    }
};

// 基本函数声明
ll ksm(ll a, ll k, ll mod);                            // 快速幂
void h(ll a, ll p, ll& x, ll& y);                      // 扩展欧几里得
ll f(ll a, ll p);                                      // 求逆元
Node sum(Node n1, Node n2, ll a, ll b, ll p);          // 点加法
Node mul(ll d, Node P, ll a, ll b, ll p);              // 倍点运算

// 7个核心功能声明（符合题目要求）
bool pdqx(ll a, ll b, ll p);                           // 1. 判断是否为椭圆曲线
bool pd(Node point, ll a, ll b, ll p);                 // 2. 判断点是否在曲线上
Node pdjf(Node P, Node Q, ll a, ll b, ll p);           // 3. 计算P+Q
Node jsdb(ll m, Node P, ll a, ll b, ll p);             // 4. 计算mP（倍加-和）
ll jsdj(Node P, ll a, ll b, ll p);                     // 5. 计算点P的阶
ll jsqxj(ll a, ll b, ll p);                            // 6. 计算椭圆曲线的阶
void scqxsd(ll a, ll b, ll p);                         // 7. 计算所有点

