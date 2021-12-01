$$\Huge\text{反演}$$

- 莫比乌斯反演
	- 莫比乌斯函数
	- 莫比乌斯反演定理
	- 杜教筛
- 快速莫比乌斯变换（反演）与子集卷积
	- 莫比乌斯变换（反演）
	- 子集卷积
- 二项式反演
- 斯特林反演
	- 第一类斯特林数
	- 第二类斯特林数
	- 反演公式
- 最值反演（$\text{min-max}$ 容斥）
- 单位根反演

## 莫比乌斯反演

### 莫比乌斯函数

莫比乌斯函数，是一个积性函数，记作 $\mu$ ，它的定义如下：
1. 若 $d = 1$ ，那么 $\mu(d)=1$；
2. 若 $d=p_1p_2\cdots p_k$ ， $p_i$ 均为互异素数，那么 $\mu(d)=(-1)^k$；
3. 其他情况下 $\mu(d)=0$

性质：对于 $\forall n \in \mathbb{N}_+$  
$$\sum_{d\mid n} \mu(d)=\begin{cases} 1 &n=1\\0 &n>1\end{cases}$$

> 证明：1. $n=1$ 时显然成立；  
> 　　　2. $n>1$ 时，将 $n$ 分解为 $p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$ ， $\mu(d)\neq 0$ 的只有次数均为 $1$ 的因子，其中质因数个数为 $i$ 的因子个数有 $C_k^i$ 个。  
> 　　　　那么就有 $$\begin{aligned}\sum_{d\mid n} \mu(d)&=C_k^0-C_k^1+\cdots+(-1)^kC_k^k\\&=(1-1)^k=0 \end{aligned}$$

线性筛莫比乌斯函数

```cpp
void get_mu() {
    memset(isprime, 1, sizeof(isprime)); isprime[1] = 0, mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i*prime[j] <= N; j++) {
            isprime[i*prime[j]] = 0;
            if (!(i%prime[j])) {mu[i*prime[j]] = 0; break; }
            else mu[i*prime[j]] = -mu[i];
        }
    }
}
```

### 莫比乌斯反演定理

若 $F(n)$ 和 $f(n)$ 是定义在非负整数集合上的两个函数，并且满足条件 $F(n)=\sum_{d\mid n} f(d)$。那么我们得到结论：$$f(n)=\sum_{d\mid n} \mu(d)F(\frac{n}{d})$$

> 证明： $$\sum_{d|n}\mu(d)F(\frac{n}{d})=\sum_{d|n}\mu(d)\sum_{k|\frac{n}{d}}f(k)=\sum_{k|n}f(k)\sum_{d|\frac{n}{k}}\mu(d)=f(n)$$

由这个定理我们可以得到莫比乌斯函数的另外一个性质： 对于 $\forall n \in \mathbb{N}_+$

$$\sum_{d\mid n} \frac{\mu(d)}{d}=\frac{\varphi(n)}{n}$$

> 证明：
> 
> 　　　引理： $n=\sum_{d\mid n} \varphi(d)$
> 
> 　　　证明：
> 
> 对于 $n$ 的每个因数 $d$ ，我们取出 $[1,d]$ 内的 $\varphi(d)$ 个与 $n$ 互素的数记做集合 $A=\{a_1,a_2,\cdots,a_{\varphi(d)}\}$ ，将集合 $A$ 内的元素对应到集合 $B=\{a_1\frac{n}{d},a_2\frac{n}{d},\cdots,a_{\varphi(d)}\frac{n}{d}\}$ 。显然 $gcd(a_i\frac{n}{d},n)=\frac{n}{d}$ 。由于 $d$ 枚举了所有 $n$ 的因数，所以 $\frac{n}{d}$ 也是。则集合 $B$ 内是 $[1,n]$ 内所有的数。故原命题成立。
> 
> 　　　有了这个引理，我们将莫比乌斯反演定理中的 $F(n) = n,f(n) = \varphi(n)$ 。 $$\begin{aligned}\varphi(n)&=\sum_{d\mid n} \frac{n}{d}\mu(d)\\ \frac{\varphi(n)}{n}&=\sum_{d\mid n} \frac{\mu(d)}{d} \end{aligned}$$

第二形式： $$F(n)=\sum_{n\mid d} f(d)\Rightarrow f(n)=\sum_{n\mid d} \mu(\frac{d}{n})F(d)$$

> 证明：令 $k=\frac{d}{n}$ ，那么 $$\sum^{+\infty}_{k=1}\mu(k)F(nk)=\sum^{+\infty}_{k=1}\mu(k)\sum_{nk|t}f(t)=\sum_{n|t}f(t)\sum_{k|\frac{t}{n}}\mu(k)=f(n)$$

### 杜教筛（普适）

若 $f(n)$ 是一个积性函数，求 $f(n)$ 的前缀 $S(n)$ 。即 $S(n)=\sum\limits_{i=1}^nf(n)$ 。

> 狄利克雷卷积
> 
> 对于数论函数 $g(n),f(n)$ ，其狄利克雷卷积 $h(n)$ 也是一个数论函数 $$h(n)=\sum_{d\mid n}g(d)f\left(\frac{n}{d}\right)$$

我们找到另一个积性函数 $g(n)$ ，让 $f(n)$ 和 $g(n)$ 做一个卷积 $$(g*f)(n)=\sum_{d\mid n}g(d)f\left(\frac{n}{d}\right)$$

求卷积的前缀 $$\sum_{i=1}^n(g*f)(i)=\sum_{i=1}^n\sum_{d|i}g(d)f\left(\frac{i}{d}\right)$$

提出右式的 $d$ $$\begin{aligned}\Rightarrow\sum_{i=1}^n(g*f)(i)&=\sum_{d=1}^{n}g(d)\sum_{d|i}f\left(\frac{i}{d}\right)\\&=\sum_{d=1}^{n}g(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}f(i)\\&=\sum_{d=1}^{n}g(d)S\left(\left\lfloor\frac{n}{d}\right\rfloor\right)\end{aligned}$$

容易得到这个式子 $$g(1)S(n)=\sum_{i=1}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)-\sum_{i=2}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$

其实就是 $$g(1)S(n)=\sum_{i=1}^n(g*f)(i)-\sum_{i=2}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$

我们发现如果狄利克雷卷积前缀很好算的话，积性函数的前缀也可以分块递归来算了。

举几个例子：  

**1.**  求 $S(n)=\sum\limits_{i=1}^n\mu(n)$  

上述式子 $$g(1)S(n)=\sum_{i=1}^n(g*\mu)(i)-\sum_{i=2}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$  

考虑到 $\sum\limits_{d\mid n}\mu(d)=[n=1]$ ，又由于 $(g*\mu)(n)=\sum\limits_{d\mid n}g(d)\mu\left(\frac{n}{d}\right)$ 。我们考虑让 $g(n)=1(n)$ ，那么 $(1*\mu)(n)=\sum\limits_{d\mid n}1\cdot\mu(d)=[n=1]$ 。显然这个卷积的前缀为 $\sum\limits_{i=1}^n(g*\mu)(i)=1(n)$ 。  

故对于 $\mu$ $$S(n)=1-\sum_{i=2}^nS\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$

**2.**  求 $S(n)=\sum\limits_{i=1}^n\varphi(n)$  

上述式子 $$g(1)S(n)=\sum_{i=1}^n(g*\varphi)(i)-\sum_{i=2}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$  

考虑到 $\sum\limits_{d\mid n}\varphi(d)=n$ ，又由于 $(g*\varphi)(n)=\sum\limits_{d\mid n}g(d)\varphi\left(\frac{n}{d}\right)$ 。我们考虑让 $g(n)=1(n)$ ，那么 $(1*\varphi)(n)=\sum\limits_{d\mid n}1\cdot\varphi(d)=n$ 。显然这个卷积的前缀为 $\sum\limits_{i=1}^n(g*\varphi)(i)=\frac{n(n+1)}{2}$ 。  

故对于 $\varphi$ $$S(n)=\frac{n(n+1)}{2}-\sum_{i=2}^nS\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$$

## 快速莫比乌斯变换（反演）与子集卷积

### 莫比乌斯变换（反演）

#### 问题提出

若 $h,f,g$ 为下标为集合的函数，我们定义

$$h=f*g$$

表示

$$h(S) = \sum_{L \subseteq S}^{} \sum_{R \subseteq S}^{} [L \cup R = S] f(L) \times g(R)$$

容易发现，对于这个问题，我们可以用 $O\left((2^n)^2\right)$ 的枚举 $L,R$ 来计算。

然而这样复杂度较高，我们考虑类比多项式卷积的过程，可以求出 $f,g$ 的点值，直接相乘得到 $h$ 的点值然后再插回去。

值得注意的是为了便于表述以及规范表达，快速莫比乌斯变换就相当于点值，快速莫比乌斯反演就相当于插值。

#### 算法原理

 - 我们定义 $f$ 的莫比乌斯变换为 $F$ ，其中 $F(S)=\sum_{X\subseteq S}f(X)$ ；由这个定义，我们可以推出 $F$ 莫比乌斯反演 $f$ 为 $f(S) = \sum_{X \subseteq S} (-1)^{|S| - |X|}F(X)$ 。对于莫比乌斯反演的证明，可以带入莫比乌斯变换的式子或容斥来证。
 - 我们对于一个函数 $f,g,h$ ，记它的点值式为 $F,G,H$ 。我们将**问题提出**中的卷积式两边同时做莫比乌斯变换，得到 $$\begin{aligned}H(S) &= \sum_{L \subseteq S} \sum_{R \subseteq S} [L \cup R \subseteq S] f(L) \times g(R)\\&=\sum_{L \subseteq S} \sum_{R \subseteq S}f(L) \times g(R)\\&=\left(\sum_{L \subseteq S}f(L)\right)\times\left(\sum_{R \subseteq S}g(R)\right)\\&=F(S)\times G(S)\end{aligned}$$

至此算法原理及过程已经完全结束。似乎我们可以用 $O(3^n)$ 枚举子集来变换和反演，实际上我们可以让复杂度更优。

#### 算法实现

 - 设 $\hat{f_{S}}^{(i)}$ 表示 $\sum_{T \subseteq S} [(S - T) \subseteq \{1, 2, ..., i\}] f_{T}$
 - 易得初始状态：$\hat{f_{S}}^{(0)} = f_{S}$
 - 对于每一个不包含 $\{i\}$ 的集合 $S$，可知 $\hat{f_{S}}^{(i)} = \hat{f_{S}}^{(i - 1)}$（因为 $S$ 并没有 $i$ 这位），$\hat{f}_{S \cup \{i\}}^{(i)} = \hat{f}_{S}^{(i - 1)} + \hat{f}_{S \cup \{i\}}^{(i - 1)}$（前者的 $T$ 没有包含 $\{i\}$，而后者的 $T$ 必须包含了 $\{i\}$）。
 - 显然，递推了 $n$ 轮之后，$\hat{f}_{S}^n$ 就是所求的变换了。

用高维前缀和可以做到 $O(n\times 2^n)$ 的递推，求出点值和插值。

```cpp
void FMT(int *A, int o) {// o 为识别因子
	for (int i = 1; i < ST; i <<= 1)//ST-1 表示全集
		for (int j = 0; j < ST; j++)
			if (i&j) (A[j] += A[j^i]*o) %= mod;
}
```

### 子集卷积

$\text{FWT}$ ：“你刚才说的那个玩意我也能做啊，要你何用？”

$\text{FMT}$ ：“……”

#### 问题提出

若 $h,f,g$ 为下标为集合的函数，我们定义

$$h=f*g$$

表示

$$h(S) = \sum_{X \subseteq S} f(X) \times g(S-X)$$

#### 算法实现

回顾刚刚的集合并卷积，子集卷积的条件比集合并卷积更苛刻，即 $L$ 和 $R$ 的集合应该不相交。

我们可以在卷积时多加一维，维护集合的大小，如 $f_{i,S}$ 表示集合中有 $i$ 个元素，集合表示为 $S$ 。显然，当 $i$ 和 $S$ 的真实元素个数符合时才是对的。记数组 ```cnt[S]``` 表示集合 $S$ 的模。初始时，我们只把 $f_{cnt[S],S}$ 的值赋成原来的 $f(S)$ （ $g$ 同理），然后每一维做一遍 $\text{FMT}$ ，点值相乘时这么写：$h_{i, S} = \sum_{j = 0}^{i} f_{j,S} \times g_{i - j, S}$ 。最后扫一遍把不符合实际情况的状态赋成 $0$ 即可。


```cpp
for (int i = 0; i <= n; i++) FMT(g[i], 1);
for (int i = 0; i <= n; i++) FMT(f[i], 1);
for (int i = 1; i <= n; i++) {
	for (int j = 0; j <= i; j++)
		for (int k = 0; k < ST; k++)
			(h[i][k] += 1ll*f[j][k]*g[i-j][k]%mod) %= mod;
	FMT(h[i], -1);
	for (int k = 0; k < ST; k++) if (cnt[k] != i) h[i][k] = 0;
	if (i != n) FMT(h[i], 1);
}
```

## 二项式反演

### 内容

对于函数 $f,g$ ， $\forall p\in\mathbb{N}$ 若 $\forall n\geq p$ ，满足

$$f(n)=\sum_{k=p}^{n}\binom{n}{k}g(k)$$

那么 $\forall n\geq p$

$$g(n)=\sum_{k=p}^{n}(-1)^{n-k}\binom{n}{k}f(k)$$

### 证明

为了方便表达，我们取 $p=0$ ，实质和取 $p\in\mathbb{N}$ 的证明方法是一样的。

$$\begin{aligned}g(n)&=\sum_{k=0}^{n}(-1)^{n-k}\binom{n}{k}f(k)\\&=\sum_{k=0}^{n}(-1)^{n-k}\binom{n}{k}\sum_{i=0}^k{k\choose i}g(i)\\&=\sum_{k=0}^n\sum_{i=0}^k(-1)^{n-k}{n\choose k}{k\choose i}g(i)\\&=\sum_{i=0}^n\left(\sum_{k=i}^n(-1)^{n-k}{n\choose k}{k\choose i}\right)g(i)\\&=\sum_{i=0}^n\left(\sum_{k=i}^n(-1)^{n-k}{n\choose i}{n-i\choose k-i}\right)g(i)\\&=\sum_{i=0}^n\left({n\choose i}\sum_{k=i}^n(-1)^{n-k}{n-i\choose n-k}\right)g(i)\\&=\sum_{i=0}^n\left({n\choose i}(1-1)^{n-i}\right)g(i)\\&=g(n)\end{aligned}$$

故成立。

### 应用举例

#### 推导错排公式

我们记 $f(n)$ 为 $n$ 个数字任意放的方案数， $g(n)$ 为 $n$ 个数没有一个放在自己位置上的方案数。

枚举不在自己位置上的个数，容易得到

$$f(n)=\sum_{i=0}^n{n\choose i}g(i)$$

那么

$$\begin{aligned}g(n)&=\sum_{i=0}^n(-1)^{n-i}{n\choose i}f(i)\\&=\sum_{i=0}^n(-1)^i{n\choose i}f(n-i)\end{aligned}$$

注意到 $f(x)=x!$ ，那么

$$\begin{aligned}g(n)&=\sum_{i=0}^n(-1)^i\frac{n!}{i!(n-i)!}(n-i)!\\&=n!\sum_{i=0}^n(-1)^i\frac{1}{i!}\end{aligned}$$

#### 棋盘染色

有个 $1\times n$ 的格子， $m$ 种颜色（ $m\geq 2$ ），要求相邻格子的颜色不相同且每种颜色都要用到，求染色方案数。

我们记 $f(n)$ 为至多用到 $n$ 种颜色的方案数， $g(n)$ 为 $n$ 为恰用到 $n$ 种颜色的方案数。

那么

$$\begin{aligned}f(m)&=\sum_{i=2}^m{m\choose i}g(i)\\\Rightarrow g(m)&=\sum_{i=2}^m(-1)^i{m\choose i}f(n-i)\end{aligned}$$

注意到 $f(x)=x\times(x-1)^{n-1}$ 。那么就可以带入直接算了。

### 另一形式

$$a_k=\sum\limits_{i=k}^n{i\choose k}b_i\Rightarrow  b_k=\sum\limits_{i=k}^n(-1)^{i-k}{i\choose k}a_i$$

证明：

$$\begin{aligned} &\sum\limits_{i=k}^n(-1)^{i-k}{i\choose k}a_i\\=& \sum\limits_{i=k}^n(-1)^{i-k}{i\choose k}\sum\limits_{j=k}^n{j\choose i}b_i\\=& \sum\limits_{i=k}^n\sum\limits_{j=k}^n(-1)^{i-k}{i\choose k}{j\choose i}b_i\\=& \sum\limits_{i=k}^n\sum\limits_{j=k}^n(-1)^{i-k}{j\choose i}{i\choose k}b_i\\=& \sum\limits_{j=k}^n\sum\limits_{i=k}^j(-1)^{i-k}{j\choose k}{j-k\choose i-k}b_i\\=& \sum\limits_{j=k}^n{j\choose k}\sum\limits_{i=k}^j(-1)^{i-k}{j-k\choose i-k}b_i\\=&\sum\limits_{j=k}^n{j\choose k}(1-1)^{j-k}b_i\\=&b_k\end{aligned}$$

## 斯特林反演

### 第一类斯特林数

$\begin{bmatrix}n\\m\end{bmatrix}$ 表示将 $n$ 个元素排成 $m$ 个轮换的方法数。

递推公式：$\begin{bmatrix}n\\m\end{bmatrix}=\begin{bmatrix}n-1\\m-1\end{bmatrix}+(n-1)\begin{bmatrix}n-1\\m\end{bmatrix}$

含义是考虑第 $n$ 个元素的放法：要么新开一个轮换，要么就放在前 $n-1$ 个元素的左边。

### 第二类斯特林数

$\begin{Bmatrix}n\\m\end{Bmatrix}$ 表示将 $n$ 个元素划分成 $m$ 个非空子集的方法数。

递推公式：$\begin{Bmatrix}n\\m\end{Bmatrix}=\begin{Bmatrix}n-1\\m-1\end{Bmatrix}+m\begin{Bmatrix}n-1\\m\end{Bmatrix}$

含义是考虑第 $n$ 个元素的放法：要么新开一个组，要么就放在前 $m$ 组内。

通项公式（容斥式）： $\begin{Bmatrix}n\\m\end{Bmatrix}=\frac{1}{m!}\sum\limits_{k=0}^{m}(-1)^k\binom{m}{k}(m-k)^n$

有关通项公式的证明及运用可以参考[多项式类数学相关](https://www.cnblogs.com/NaVi-Awson/p/8684389.html)这篇文章。

### 反演公式

$$f(x) = \sum_{i=0}^x \begin{Bmatrix}x\\i\end{Bmatrix} g(i) \Leftrightarrow g(x) = \sum_{i=0}^x (-1) ^ {x - i}\begin{bmatrix}x\\i\end{bmatrix} f(i)$$

$$f(x) = \sum_{i=0}^x \begin{bmatrix}x\\i\end{bmatrix}  g(i) \Leftrightarrow g(x) = \sum_{i=0}^x (-1) ^ {x - i}\begin{Bmatrix}x\\i\end{Bmatrix}  f(i)$$

> 例题
>  - 给出 $n$ 个点的一张简单图，问有多少个边的子集，满足保留子集中的边后，该图连通。
>      - 大概就是枚举连通块的个数，然后块内随便连，然后容斥就好。
>      - 考虑如何求容斥系数 $f(i)$ 。设实际上是 $x$ 个连通块的方案，它应该被计算 $[x=1]$ 次，实际上在所有更仔细的分块中被统计，所以
>      - $$[x = 1] = \sum_{i=1}^x\begin{Bmatrix}x\\i\end{Bmatrix}f(i)$$
>      - 由斯特林反演
>      - $$\begin{aligned}f(x) &= \sum_{i=1}^x(-1)^{x-i}\begin{bmatrix}x\\i\end{bmatrix}[i=1]\\&=(-1)^{x-1}\begin{bmatrix}x\\1\end{bmatrix}\\&=(-1)^{x-1}(x-1)!\end{aligned}$$

## 最值反演（ $\text{min-max}$ 容斥）

### 公式

记 $\max(S)$ 为集合 $S$ 中的最大值， $\min(S)$ 为集合 $S$ 中的最小值， $|S|$ 为集合 $S$ 的元素数量，那么以下两个等式成立

$$\max(S)=\sum_{T\subseteq S}(-1)^{|T|+1}\min(T)$$

$$\min(S)=\sum_{T\subseteq S}(-1)^{|T|+1}\max(T)$$

### 证明

这里只证明第一个等式好了，后边的可以自行推出。

其实只需要证明一件事，就是除了 $\min(T)=\max(S)$ 的那个值，其他的 $\min$ 值都被消掉了就可以了（这里说明一下，我们假定集合中的元素两两相异）

先来说明 $\max(S)$ 的系数为什么是 $1$ ，假设中 $S$ 最大的元素是 $a$ ，那么我们会发现只有 $\min(\{a\})=\max(S)$ 所以 $\max(S)$ 的系数必须是 $1$ 。

然后再说明为什么别的 $\min$ 都被消掉了，假设某个元素 $b$ 的排名是 $k$ ，那么 $\min(T)=b$ 当且仅当我们选出的集合是后 $n-k$ 个的元素构成的集合的子集然后并上 $\{b\}$ 得到的，我们会发现显然这样的集合有 $2^{n-k}$ 种，而显然这其中恰有 $2^{n-k-1}$ 中是有奇数个元素的，恰有 $2^{n-k-1}$ 种是有偶数个元素的，两两相消自然就成 $0$ 了，当然上述等式在 $k=n$ 的时候不成立，但是此时剩下的刚好是最大值，所以证明完毕。

# 拉格朗日插值法

## 简介

给定 $n + 1$ 个**横坐标不相同**的点，可以唯一确定一个 $n$ 次的多项式。最直观的求多项式的做法就是列方程求解。但是这样需要 $O(n^3)$ 的时间来计算。而拉格朗日插值法则通过构造的方法，得到了一个经过 $n + 1$ 个点的 $n$ 次多项式。 具体的过程是这样的，假设现在我们得到了 $n + 1$ 个点：

$$ (x_0, y_0), \;(x_1, y_1),\; \dots,\;(x_n, y_n) $$

设**拉格朗日基本多项式**为

$$ \ell_j(x) = \prod_{i = 0, i \neq j}^n {x - x_i \over x_j - x_i} $$

这个基本多项式构造十分巧妙，因为注意到 $\ell_j(x_j) = 1$ ，并且 $\ell_j(x_i) = 0, \;\forall i \neq j$ 。那么，接着构造出这个 $n$ 次多项式

$$ P(x) = \sum_{i = 0}^n y_i\ell_i(x) $$

根据基本多项式的性质，我们可以知道 $P(x_i) = y_i$ ，也就是经过了这 $n + 1$ 个点。 通过简单的多项式乘法和多项式除法就可以在 $O(n^2)$ 的时间求出这个多项式的系数表达。

## 求解

已知 $n$ 次多项式 $f(n)$ 上的 $n+1$ 个点 $(x_i,y_i),i\in[0,n]$ ，求 $f(xi)$

```cpp
int lagrange(int n, int *x, int *y, int xi) {
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        int s1 = 1, s2 = 1;
        for (int j = 0; j <= n; j++)
            if (i != j) {
                s1 = 1ll*s1*(xi-x[j])%mod;
                s2 = 1ll*s2*(x[i]-x[j])%mod;
            }
        ans = (1ll*ans+1ll*y[i]*s1%mod*quick_pow(s2, mod-2)%mod)%mod;
    }
    return (ans+mod)%mod;
}
```

如果 $x$ 的取值是连续一段的话，我们可以做到 $O(n)$ 求解。假设 $\forall i<j,x_i<x_j$ （具体公式推导的话，如果你有兴趣可以参看之后的内容。因为比较显然，这里不再讲解。）

```cpp
int lagrange(int n, int *x, int *y, int xi) {
	int ans = 0;
	s1[0] = (xi-x[0])%mod, s2[n+1] = 1;
	for (int i = 1; i <= n; i++) s1[i] = 1ll*s1[i-1]*(xi-x[i])%mod;
	for (int i = n; i >= 0; i--) s2[i] = 1ll*s2[i+1]*(xi-x[i])%mod;
	ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) ifac[i] = -1ll*mod/i*ifac[mod%i]%mod;
	for (int i = 2; i <= n; i++) ifac[i] = 1ll*ifac[i]*ifac[i-1]%mod;
	for (int i = 0; i <= n; i++)
		(ans += 1ll*y[i]*(i == 0 ? 1 : s1[i-1])%mod*s2[i+1]%mod
			*ifac[i]%mod*(((n-i)&1) ? -1 : 1)*ifac[n-i]%mod) %= mod;
	return (ans+mod)%mod;
}
```

## 单位根反演
具体式子是这样的
$$\forall k,[n|k]=\frac{1}{n}\sum_{i=0}^{n-1}\omega_n^{ik} $$

> 简单的证明：
首先当 $[n|k]$ 的时候，$\omega_n^{ik}=\omega^0=1$，所以原式等于 $1$。
否则是一个等比数列求和，$\displaystyle \frac{1}{n}\frac{\omega_n^{nk}-\omega_n^0}{\omega_n^k-1}=0$。

假如我们要算某个多项式的特定倍数的系数和。
也就是要求这个：$\displaystyle \sum_{i=0}^{[\frac{n}{k}]}[x^{ik}]f(x)$。

那么可以

$$\begin{aligned} \sum_{i=0}^{[\frac{n}{k}]}[x^{ik}]f(x)&=\sum_{i=0}^n[k|i][x^i]f(x)\\ &=\sum_{i=0}^n [x^i]f(x)\frac{1}{k}\sum_{j=0}^{k-1}\omega_{k}^{ji}\\ &=\frac{1}{k}\sum_{i=0}^n a_i\sum_{j=0}^{k-1}\omega_{k}^{ij}\\ &=\frac{1}{k}\sum_{j=0}^{k-1}\sum_{i=0}^n a_i(\omega_k^j)^i\\ &=\frac{1}{k}\sum_{j=0}^{k-1}f(\omega_{k}^j) \end{aligned}$$