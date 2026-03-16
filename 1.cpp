#include <iostream>
#include <windows.h>
#include "mymath.h"
using namespace std;

int main()
{
    // 设置控制台编码为UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    printf("========== 椭圆曲线运算系统 ==========\n\n");
    
    ll p, a, b;
    printf("请输入椭圆曲线的参数 p, a, b：\n");
    printf("p = ");
    cin >> p;
    printf("a = ");
    cin >> a;
    printf("b = ");
    cin >> b;
    printf("\n");
    
    // 1. 判断是否为椭圆曲线
    printf("1. 判断 E_%lld(%lld,%lld) 是否为椭圆曲线：\n", p, a, b);
    if(pdqx(a, b, p))
    {
        printf("   是椭圆曲线\n");
        
        // 计算判别式
        ll delta = (4 * ksm(a, 3, p) + 27 * ksm(b, 2, p)) % p;
        delta = (delta % p + p) % p;
        printf("   判别式 Δ = 4a³ + 27b² = %lld (mod %lld)\n", delta, p);
    }
    else
    {
        printf("   不是椭圆曲线\n");
        printf("   警告：后续运算可能不正确！\n");
    }
    printf("\n");
    
    // 主菜单
    while(1)
    {
        printf("========== 功能菜单 ==========\n");
        printf("1. 判断点是否在椭圆曲线上\n");
        printf("2. 计算点加法 P + Q\n");
        printf("3. 使用倍加-和算法计算 mP\n");
        printf("4. 计算点P的阶\n");
        printf("5. 计算椭圆曲线的阶\n");
        printf("6. 输出椭圆曲线上所有点\n");
        printf("7. 重新输入椭圆曲线参数\n");
        printf("0. 退出程序\n");
        printf("请选择功能编号：");
        
        int xz;
        cin >> xz;
        printf("\n");
        
        if(xz == 0)
        {
            break;
        }
        else if(xz == 1)  // 判断点是否在曲线上
        {
            ll x, y;
            printf("请输入点的坐标 (x,y)：");
            cin >> x >> y;
            Node d(x, y);
            if(d.isFar())
            {
                printf("点d(无穷远点)在椭圆曲线上\n");
            }
            else
            {
                if(pd(d, a, b, p))
                {
                    printf("点(%lld,%lld)在椭圆曲线上\n", x, y);
                    // 显示验证计算
                    printf("验证：左边 y² = %lld² mod %lld = %lld\n", 
                        y, p, (y*y)%p);
                    printf("右边 x³ + ax + b = %lld³ + %lld*%lld + %lld mod %lld = %lld\n",
                        x, a, x, b, p, (ksm(x,3,p)+a*x+b)%p);
                }
                else
                {
                    printf("点(%lld,%lld)不在椭圆曲线上\n", x, y);
                }
                printf("\n");
            }
        }
        else if(xz == 2)  // 点加法
        {
            ll x1, y1, x2, y2;
            printf("请输入点P的坐标 (x1,y1)：");
            cin >> x1 >> y1;
            printf("请输入点Q的坐标 (x2,y2)：");
            cin >> x2 >> y2;
            
            Node P(x1, y1);
            Node Q(x2, y2);
            Node result = pdjf(P, Q, a, b, p);
            
            if(!result.isFar())
            {
                printf("P(%lld,%lld) + Q(%lld,%lld) = (%lld,%lld)\n", 
                       x1, y1, x2, y2, result.x, result.y);
            }
            else if(result.x == -1 && result.y == -1)
            {
                // 这是错误情况，已经在pdjf函数中处理了
            }
            else
            {
                printf("P(%lld,%lld) + Q(%lld,%lld) = O\n", x1, y1, x2, y2);
            }
            printf("\n");
        }
        else if(xz == 3)  // 倍点运算
        {
            ll m, x, y;
            printf("请输入正整数 m：");
            cin >> m;
            printf("请输入点P的坐标 (x,y)：");
            cin >> x >> y;
            
            Node P(x, y);
            Node result = jsdb(m, P, a, b, p);
            
            if(!result.isFar())
            {
                printf("%lldP = (%lld,%lld)\n", m, result.x, result.y);
            }
            else if(result.x == -1 && result.y == -1)
            {
                printf("%dP = (%d,%d)\n", m, -1, -1);
            }
            else
            {
                printf("%lldP = O\n", m);
            }
            printf("\n");
        }
        else if(xz == 4)  // 点的阶
        {
            ll x, y;
            printf("请输入点P的坐标 (x,y)：");
            cin >> x >> y;
            
            Node P(x, y);
            ll order = jsdj(P, a, b, p);
            
            if(order > 0)
            {
                printf("点P(%lld,%lld)的阶为：%lld\n", x, y, order);
                
                // 验证：order * P 应该等于无穷远点
                Node check = mul(order, P, a, b, p);
                if(check.isFar())
                {
                    printf("验证：%lldP = O\n", order);
                }
            }
            printf("\n");
        }
        else if(xz == 5)  // 椭圆曲线的阶
        {
            ll order = jsqxj(a, b, p);
            if(order > 0)
            {
                printf("椭圆曲线 E_%lld(%lld,%lld) 的阶为：%lld\n", p, a, b, order);
            }
            printf("\n");
        }
        else if(xz == 6)  // 输出所有点
        {
            scqxsd(a, b, p);
            printf("\n");
        }
        else if(xz == 7)  // 重新输入参数
        {
            printf("重新输入椭圆曲线的参数 p, a, b：\n");
            printf("p = ");
            cin >> p;
            printf("a = ");
            cin >> a;
            printf("b = ");
            cin >> b;
            
            printf("\n1. 判断 E_%lld(%lld,%lld) 是否为椭圆曲线：\n", p, a, b);
            if(pdqx(a, b, p))
            {
                printf("   是椭圆曲线\n");
            }
            else
            {
                printf("   不是椭圆曲线\n");
                printf("   警告：后续运算可能不正确！\n");
            }
            printf("\n");
        }
        else
        {
            printf("输入错误，请重新选择！\n\n");
        }
    }
    
    return 0;
}