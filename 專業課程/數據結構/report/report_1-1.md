## 1-1 A+B Problem  解题报告 ##

#### 容逸朗 2020010869 ####

### 1  解法 ###

高精度乘法是十分经典的题目，要解决这一问题只需要模拟竖式计算即可。

简单来说，对于两个字串 $sa$ 和 $sb$ ，我们先将字串的每一位按低位在前的方法存入数组，再把字串内的数字一一枚举做乘法：

```c++
for (int i = 1; i <= a[0]; i++) // a[0] 为字串 sa 的长度
    for (int j = 1; j <= b[0]; j++) {// b[0] 为字串 sb 的长度
        s[i + j - 1] += a[i] * b[j];
    }
```

运算结束后需要解決进位的问题：

```c++
for (int i = 1; i < s[0]; i++) {
    x = s[i] / bigInt; // bigInt = 1e8
    s[i + 1] += x;
    s[i] -= x * bigInt; // 直接取模也可以，看个人习惯
}
```

最后倒序输出数组便可：

```c++
printf("%lld", num[num[0]]);
for (int i = num[0] - 1; i > 0; i--) {
    printf("%08lld", num[i]); // 压了八位，不足位补零。用 %08lld
}
printf("\n");    
```

时间复杂度为 $O(n^2)$ ，空间复杂度 $O(1)$。

### 2  遇到的问题

#### 2.1 何时进位

最开始的时候，我是在计算 $a[i]*b[j]$ 时计算进位的，这使得程序的效率十分低下，在规模最大的问题约需 2.7 秒（压九位），后来在所有乘法运算结束后才一併计算进位，时间间大幅减少至 0.7 秒（压八位）。

耗时较高的原因在于前者时间复杂度 $O(len_a * len_b)$ ，后者时间复杂度为 $O(len_a + len_b)$ 。

#### 2.2 压位

理论上 unsigned long long 可以支持压九位的操作，但由于我们是在运算结束后一併处理进位的，所以压九位的时候会导致数组内的数值最大可以达到 $10^9*10^9*(5000+5000) = 10^{20}$ ，这超出了 unsigned long long 的表示范围，因此只能压八位（最大值 $10^{18}$ ）。

