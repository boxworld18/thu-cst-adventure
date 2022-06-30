# CGAN_jittor

## 简介

本项目使用了 Jittor 机器学习框架，在数字图片数据集 MNIST 上训练一个将随机噪声和类别标签映射为数字图片的 Conditional GAN 模型，生成指定数字序列对应的图片。

## 如何使用

请确保你使用的 python 环境中已有 jittor 包，否则请到[此处](https://cg.cs.tsinghua.edu.cn/jittor/download/)下载。

环境准备好后，只需要拷贝本项目到本地，然后利用下面的代码运行即可：

```
python3 CGAN.py
```

## 注意事项

1. 因为图像的尺度较小，故化码直接使用了全连接层而不是通常的卷积层。

2. 默认状态下代码会自动下载 MNIST 数据集，且 epoch 次数达 100 次。倘若阁下的计算性能不足，建议适当减少这一数值，或直接使用本项目[已经训练好的模型](https://cloud.tsinghua.edu.cn/d/0cc13f962b7b4c7b83c3/)。

