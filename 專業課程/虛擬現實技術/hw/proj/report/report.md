# **全景图像融合实验报告**

<center><div style='height:2mm;'></div><div style="font-family:宋体;font-size:10pt;">于沛楠　蒋政　容逸朗</div></center>



## 简介

#### 实验目标

* 将多幅图像拼接成一张大尺度的图片

#### 分工

* 于沛楠：实验框架搭建、多图拼接及效果调整
* 蒋政：图像融合、多图拼接
* 容逸朗：单应性矩阵计算、柱面投影

#### 代码下载

* 链接：https://cloud.tsinghua.edu.cn/d/7bf029b5f6684d3e8c14/



## 实验内容

### 内容简述

#### 基础部分

* 利用 SIFT 方法为两张图片做特征匹配；
* 计算匹配点的特征变换矩阵；
* 使用特征变换矩阵，将某张图片变形为适合拼接的另一张图片；
* 使用线性插值、泊松融合或金字塔融合等方式实现两张图片拼接。

#### 提高部分

* 在两张图片拼接的基础上实现多图拼接。



### 实现方案

#### SIFT 特征匹配

* 首先利用 SIFT 寻找特征点和描述子；
* 然后利用 knnMatch 方法匹配特征点；
* 本次实验主要使用 OpenCV 的 SIFT 方法实现，无须特別改进。

#### 单应性矩阵计算

* 基础版本：任意选取四组特征点计算矩阵；
* 难点：由于匹配存在误差，因此随机算法可能选到错误的点导致拼接效果不佳。

##### 解决方案

* 使用 RANSAC 算法提高精度：
  * 每次随机选取四组特征点；
  * 多次迭代后找到包含最多内点的模型；
* 然后利用最小二乘法为 RANSAC 算法计算所得的内点拟合矩阵。

#### 图像融合算法

* 基础版本：算出单应性矩阵后直接变换其中一张图片，然后把两张图片拼接在一块；
* 难点：相邻图片之间的光线颜色有所不同，直接拼接可以看到明显的接缝。

##### 解决方案

* 本次实验共实现了三种不同的融合方法作对比：
* 加权融合
  * 针对重叠部分按照离边界的距离加权融合两张图片的颜色，实现渐变效果。
* 泊松融合
  * 完成图像拼接后，只针对重叠部分采用泊松融合；
  * 以此改变拼接交界处图像的颜色以及梯度，达到无缝融合效果。
* 金字塔融合
  * 首先生成高斯金字塔；
  * 然后生成拉普拉斯金字塔；
  * 最后生成融合金字塔并进行重建。

#### 多图拼接

* 基础版本：图片按左至右的顺序分別调用拼接函数；
* 难点：图像变形严重，由于只有固定一侧的图片会变形导致图片有一边被严重拉伸。

##### 解决方案 1

* 图片按照左右交替的方式从中间开始拼接：
  * 例如：三张图片 A, B, C；
  * 先拼接 A 和 B，然后对 A 作矩阵变换；
  * 然后把合并好的图片和 C 拼接，对 C 作矩阵变换；
  * 这样可以使中间的图片处于视角中央，形成透视效果；
* 难点：即便运用了上面的方法，当要拼接的图像数量变多时仍然会导致最终图像左右两侧的图片出现严重的变形；

##### 解决方案 2

* 除了方案 1 外，同时通过裁剪和压扩的方式减少每次拼接所带来的极端拉伸。



## 实验演示

更多例子可以在代码仓库下的 `code/pics/{example_name}/` 中查看。

### 融合方法对比

输入：

<center class="half"><img src="img/elden1/3.png" alt="3" style="zoom:10%;" /><img src="img/elden1/4.png" alt="4" style="zoom:10%;" /><img src="img/elden1/5.png" alt="5" style="zoom:10%;" /></center>

#### 金字塔融合

生成结果：`out_multiband_345.png`

<img src="img/elden1/out_multiband_345.png" alt="out_multi" style="zoom:25%;" />

#### 加权融合

生成结果：`out_weight_345.png`

<img src="img/elden1/out_weight_345.png" alt="out_weight" style="zoom:25%;" />

#### 泊松融合

生成结果：`out_poisson_345.png`

<img src="img/elden1/out_poisson_345.png" alt="out_poisson" style="zoom:25%;" />

#### 总结

泊松融合在复杂的场景下可以减少重影的出现。

### 多图拼接

#### 简单现实场景：荷塘 (snow)

输入：

<center class="half"><img src="img/snow/1.jpg" alt="1" style="zoom:15%;" /><img src="img/snow/2.jpg" alt="2" style="zoom:15%;" /></center>

生成结果：

<img src="img/snow/result.png" alt="1" style="zoom:40%;" />

#### 泊松融合：简单现实场景 (road)

输入：

<center class="half"><img src="img/road/1.png" alt="1" style="zoom:50%;" /><img src="img/road/2.png" alt="2" style="zoom:50%;" /><img src="img/road/3.png" alt="3" style="zoom:50%;" /></center>

生成结果：

<img src="img/road/out_poisson_3.png" alt="1" style="zoom:60%;" />

#### 泊松融合：现实光影 (bridge)

输入：

<center class="half"><img src="img/bridge/1.png" alt="2" style="zoom:10.12%;" /><img src="img/bridge/2.png" alt="3" style="zoom:10.08%;" /><img src="img/bridge/3.png" alt="4" style="zoom:10%;" /></center>

生成结果：`out_poisson_3.png`

<img src="img/bridge/out_poisson_3.png" alt="out_3" style="zoom:18%;" />

#### 加权融合：复杂光影 (elden1)

输入：

<center class="half"><img src="img/elden1/1.png" alt="1" style="zoom:10%;" /><img src="img/elden1/2.png" alt="2" style="zoom:10%;" /><img src="img/elden1/3.png" alt="3" style="zoom:10%;" /><img src="img/elden1/4.png" alt="4" style="zoom:10%;" /><img src="img/elden1/5.png" alt="5" style="zoom:10%;" /><img src="img/elden1/6.png" alt="6" style="zoom:10%;" /></center>

生成结果：`out_weight_6.png`

<img src="img/elden1/out_weight_6.png" alt="out_weight_6" style="zoom:25%;" />

#### 泊松融合：复杂光影 (elden2)

输入：

<center class="half"><img src="img/elden2/2.png" alt="2" style="zoom:10%;" /><img src="img/elden2/3.png" alt="3" style="zoom:10%;" /><img src="img/elden2/4.png" alt="4" style="zoom:10%;" /></center>

生成结果：`out_poisson_345.png`

<img src="img/elden2/out_poisson_345.png" alt="out_poisson_345" style="zoom:25%;" />

#### 金字塔融合：复杂光影 (elden3)

输入：

<center class="half"><img src="img/elden3/1.png" alt="1" style="zoom:10%;" /><img src="img/elden3/2.png" alt="2" style="zoom:10%;" /><img src="img/elden3/3.png" alt="3" style="zoom:10%;" /><img src="img/elden3/4.png" alt="4" style="zoom:10%;" /><img src="img/elden3/5.png" alt="5" style="zoom:10%;" /><img src="img/elden3/6.png" alt="6" style="zoom:10%;" /></center>

生成结果：`out_multiband_6.png`

<img src="img/elden3/out_multiband_6.png" alt="out_multiband_6" style="zoom:25%;" />



## 实验总结

### 实验不足

#### 柱面投影

本次实验尝试了使用柱面投影减少图片变形的问题，然而引入柱面投影后由于拼接的图像变界出现了新的黑色区域，这使得图像融合时出现不自然的色差，同时又因为合并后图像已经受到变形影响，当图像匹配特征点时成功匹配的点数会大幅减少，这使得图像合并效果不佳。

#### 重影

在图片重叠的位置有机会因为矩阵计算偏差的原因，导致重叠部分的特征点出现了两次，又因为融合算法 (如加权融合) 的原因使得重复出现的内容同时出现在图像上，也就产生了重影的问题。

### 未来改进方案

* 尝试更多特征点匹配算法：
  * 实验虽然采用了 OpenCV 的匹配算法，然而色调偏暗的重点物品却不能很好的被 SIFT 算法所匹配，这导致合并后的图片出现较大程度的失真；
* 对柱面投影的图片特殊处理，减少变形黑框对图像融合结果的影响；
* 支持更多图片的拼接。(本项目最大可以支持 6 张图的拼接)
