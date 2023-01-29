# **傅里叶级数的可视化．实验报告**

<center><div style='height:2mm;'></div><div style="font-family:华文楷体;font-size:10pt;">计01　容逸朗　2020010869</div></center>



## 复现方法

请确保您是在**文件根目录**下开启命令行，然后在命令行输入下面的指令即可运行代码。

```bash
bash ./gen.sh
```

也可以通过调整下面的指令单独运行程序：

```bash
python exp1.py -nf 128 -sh 'semicircle'
```

我们还提供了两个不同的参数可供调整：

| 参数 | 意义                                    |
| ---- | --------------------------------------- |
| nf   | 傅里叶采样点数量                        |
| sh   | 信号类型，包括 'square' 和 'semicircle' |

## 实验结果

实验的图片结果放在 `square` 和 `semicircle` 对应的文件夹当中，视频则放在 `video` 文件夹下，以 `{signal_name}_{N_Fourier}.mp4` 的方式命名。

## 实验过程

### 方波信号可视化

目标方波：$f(t)=0.5\mathrm{sgn}(\sin(t))+0.5$

首先，可以取常数 $\omega_1=1$，此时周期 $T=\frac{2\pi}{\omega_1}=2\pi$，对应的傅里叶系数为：
$$
\begin{align}
a_0&=\frac{1}{2\pi}\int_0^{2\pi}f(t)\mathrm{d} t\\
&=\frac{1}{2\pi}\int_0^{2\pi}\left[\frac{1}{2}\mathrm{sgn}(\sin(t))+\frac{1}{2}\right]\mathrm{d} t\\
&=\frac{1}{2\pi}\int_0^{\pi}dt\\
&=\frac{1}{2}
\end{align}
$$


当 $n\in \mathbb{Z}^+$ 时， 对应的傅里叶系数为：
$$
\begin{align}
a_n&=\frac{2}{2\pi}\int_0^{2\pi}f(t)\cos(nt)\mathrm{d} t\\
&=\frac{1}{\pi}\int_0^{2\pi}\left[\frac{1}{2}\mathrm{sgn}(\sin(t))+\frac{1}{2}\right]\cos(nt)\mathrm{d} t\\
&=\frac{1}{\pi}\int_0^{\pi}\cos(nt)dt\\
&=\frac{1}{n\pi}\sin(nt)\bigg|_0^\pi\\
&=\frac{\sin(n\pi)}{n\pi}
\end{align}
$$

$$
\begin{align}
b_n&=\frac{2}{2\pi}\int_0^{2\pi}f(t)\sin(nt)\mathrm{d} t\\
&=\frac{1}{\pi}\int_0^{2\pi}\left[\frac{1}{2}\mathrm{sgn}(\sin(t))+\frac{1}{2}\right]\sin(nt)\mathrm{d} t\\
&=\frac{1}{\pi}\int_0^{\pi}\sin(nt)dt\\
&=\frac{-1}{n\pi}\cos(nt)\bigg|_0^\pi\\
&=\frac{1-\cos(n\pi)}{n\pi}
\end{align}
$$

然后我们可以将对应的公式写入 `fourier_coefficient(n)` 函数。

### 半圆信号可视化

目标波形：$f(t)=
\begin{cases}
\sqrt{\pi^2-(t-\pi)^2},&0\leq t<2\pi\\
f(t-2\pi),&t\geq2\pi
\end{cases}$

同样可以取常数 $\omega_1=1$，此时周期 $T=\frac{2\pi}{\omega_1}=2\pi$。

首先求傅里叶系数 $a_0=\frac{1}{2\pi}\int_0^{2\pi}f(t)\mathrm{d} t$ 由简单观察可知此式相当于求半圆的面积除以 $2\pi$ 的值，因此求得 $a_0=\frac{\pi^2}{4}$。

对于其他 $n\in \mathbb{Z}^+$，我们可以采用分段近似的方法求积分值，即
$$
\int_0^{2\pi}f(x)\mathrm{d}x=\sum_{k=0}^{N-1}f\left(k\cdot \frac{2\pi}{N}\right)\cdot\frac{2\pi}{N}
$$
然后将对应公式写入 `fourier_coefficient(n)` 函数即可。

