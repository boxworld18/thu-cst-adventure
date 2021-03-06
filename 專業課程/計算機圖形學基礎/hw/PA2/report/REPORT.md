# **PA2．参数曲线和曲面实验报告**

<center><div style='height:2mm;'></div><div style="font-family:华文楷体;font-size:10pt;">计01　容逸朗　2020010869</div></center>



1. **Bezier 曲线和 B 样条曲线有什么异同?**

   相同点：

   * Bezier 曲线是 B 样条曲线的特例；
   * 几何不变性：两种曲线的几何特性不随坐标变换而变化，形状仅与控制多边形各顶点的相对位置有关，而与坐标系的选择无关；
   * 变差缩减性：当特征多边形为平面图形时，平面内任意直线与曲线的交点个数不多于此直线与其特征多边形的交点个数；
   * 凸包性：两种曲线始终会在包含了所有控制点的最小凸多边形内；

   相异点：

   * Bezier 曲线不接受单点修改（全局性），而 B 样条曲线可以（局部性）。
   * Bezier 曲线一定经过两个端点的控制点（起点和终点），而 B 样条曲线不一定经过两个端点；
   * B 样条曲线可以使用较低阶曲线并仍然保持大量控制点，因此 B 样条曲线的控制和灵活性较 Bezier 曲线为优。

   

2. **怎样绘制一个首尾相接且接点处也有连续性质的 B 样条?**

   对于有 $n+1$ 个控制点的 $p$ 次 B 样条曲线，只需让 $P_0$ 和 $P_{n-p+1}$ ，$P_1$ 和 $P_{n-p+2}$ ，…，$P_{p-1}$ 和 $P_n$ 这 $p$ 组点相互重合即可。（显然地，这条曲线在接点 $P_0$ 处会有 $C^{p-1}$ 的连续性，这保证了闭合曲线的连续性）

   

3. **阅读 revsurface.hpp 中绘制旋转曲面的代码，简述其主要绘制逻辑。**

   * 首先要利用 `discretize` 方法得到曲线的顶点和该处的切向量；
   * 然后以每次 $2\pi/step=\pi/20$ （这里代码中 $step=40$）的步长旋转（可以找到对应的旋转向量）；
   * 每次旋转时，将上述的旋转向量与原来的顶点和切向量做点乘，得到新的顶点和对应切向量；
   * 然后对于新顶点的相邻点，找到对应的旋转前的点，然后将这四个点分为两组：
     - $(ci + 1) * steps + i, ci * steps + i1, ci * steps + i$
     - $(ci + 1) * steps + i, (ci + 1) * steps + i1, ci * steps + i1$
   * 上面两组点组成了两个三角形面片，将这两个面片加入旋转曲面对应的三角面片集中；
   * 最后依次画出三角面片即可。

   

4. **你在完成作业的时候和哪些同学进行了怎样的讨论?是否借鉴了网上/别的同学的代码?**

   完成此次作业并没有和任何同学进行讨论，代码主要是参考了作业包内提供的 python 脚本。

   

2. **你对本次作业有什么建议? 文档或代码中有哪些需要我们改进的地方?**

   我认为本次作业的框架和指引都十分清晰，而且任务量恰到好处，暂时没有需要改进的地方。

