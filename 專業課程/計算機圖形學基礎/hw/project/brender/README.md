# 基于 NeRF 和 Instant-NGP 的可微渲染新视角生成模型
<p align="left">
<img src="docs/coffee.png" width="240" \>
<img src="docs/scarf.png" width="240" style="padding-left: 5px;" \>
<img src="docs/scar.png" width="240" style="padding-left: 5px;" \>
</p>

## 简介

本项目包含了第二届计图挑战赛计图 - 可微渲染新视角生成比赛的代码实现。项目是以 baseline ([jrender](https://github.com/Jittor/jrender) 和 [JNeRF](https://github.com/Jittor/jnerf)) 为基础改进而成的，因此本项目继承了上述项目的特点，即：

* 支持对 .obj 文件的加载和保存，支持对三角网格模型的渲染；
* 支持 Volume Rendering；
* 内置 2 个主流三角网格可微渲染器 SoftRas 和 N3MR，支持快速切换可微渲染器；
* 支持金属度、粗糙度材质渲染；
* 内置多种 loss 函数、投影函数；
* 使用 CUDA 进行渲染加速，渲染速度优于 PyTorch；
* 支持 Instant-NGP 模型，在训练 NeRF 模型时有更好的效率和更优质的结果。

### 效果

本模型在比赛提供的数据集上的渲染成绩如下：

| 数据集   | 模型        | 实现方式 |   PSNR   |
| -------- | :---------- | -------- | :------: |
| Car      | NeRF        | jrender  | 24.5174  |
| Coffee   | Instant-NGP | JNeRF    | 34.3579  |
| Easyship | NeRF        | jrender  | 25.2233  |
| Scar     | Instant-NGP | JNeRF    | 40.5888  |
| Scarf    | Instant-NGP | JNeRF    | 32.1524  |
| **总计** | -           | -        | 156.8397 |



## 安装

### 运行环境

* 系统：**Linux**(e.g. Ubuntu/CentOS/Arch), **macOS**, or **Windows Subsystem of Linux (WSL)**
* 显卡
  * sm arch >= sm_61 (GTX 10x0 / TITAN Xp 或更高)
  * 使用 fp16: sm arch >= sm_70 (TITAN V / V100 或更高，brender 会自动检测环境是否满足需求)
  * 使用 FullyFusedMLP: sm arch >= sm_75 (RTX 20x0 或更高，brender 会自动检测环境是否满足需求)
* CPU 编译器 (至少满足其中一个条件)
  * g++ (>=5.4.0)
  * clang (>=8.0)
* GPU 编译器 (可选)
  * nvcc (>=10.0 for g++ or >=10.2 for clang)
* GPU 库: cudnn-dev (建议使用 tar 文件安装，[下载地址](https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html#installlinux-tar))

### 训练速度

我们使用单张 NVIDIA A100 显卡及如下配置：

- cuda: 11.4
- driver: 470.57.02
- jittor: 1.3.4.14

注：

* 利用 jrender 测试 `configs/jrender/nerf_sample.txt` 时，训练速度为 13.5 iter/s，训练显存为 7.1G，测试显存为 4.2G。

* 利用 JNeRF 测试 `configs/jnerf/ngp_sample.txt`时，训练速度为 122.1 iter/s，训练显存为 8.6G，测试显存为 9.0G。

### 安装方法

#### 步骤一：安装 Jittor

使用 BNerf 前需要安装好 Jittor，Jittor 的安装方法在[此处](https://github.com/Jittor/jittor)。

#### 步骤二：安装依赖

执行以下命令安装 python 依赖
```
bash setup.sh
```

#### 步骤三：安装 JNeRF (可选)

您可以在 ```~/.bashrc``` 中加入 ```export PYTHONPATH=$PYTHONPATH:{your_path_to_brender}/brender/python``` ，然后运行

```shell
source ~/.bashrc
```



## 训练

### 数据集

#### 训练/验证数据集下载

首先根据 **安装** 部分介绍的方法，安装好 jittor 和上述其他依赖包后，运行以下指令：

```shell
git clone git@github.com:boxworld18/jittor-boxworld-brender.git
cd brender
bash download_data.sh
```

### 开始训练

#### jrender

jrender 的训练与测试已经集成在一条命令之中。一个简单的例子如下：

```
python ./tools/run_jrender.py --config ./configs/jrender/nerf_sample.txt
```

#### JNeRF

JNeRF 的训练与测试已经集成在一条命令之中。请注意 jittor 是一个即时编译框架，因此首次编译代码可能需要较长的时间。

```shell
python ./tools/run_jnerf.py --config-file ./configs/jnerf/ngp_sample.py
```

注：JNeRF 训练结束后，ckpt 文件 params.pkl 会自动保存在 `./logs/{exp_name}/` 中，也可以在配置文件中设置 ckpt_path 来修改 ckpt 文件路径。



## 测试

### 使用预训练模型

执行以下命令下载预训练模型：

```shell
bash download_sample.sh
```

对于此次竞赛中的五个赛题，我们已经训练好不同的模型。执行以下命令即可下载相关预训练模型：

```shell
bash download_pretrained_models.sh
```

### 生成测试图片

将命令的 `--task` 设置为 `test` 以使用预训练模型进行测试：

```shell
python ./tools/run_jnerf.py --config-file ./configs/jnerf/render_sample.py --task test
```

### 渲染视频

把指令中的 `--task` 设置为 `render` 以根据预训练模型以指定的相机路径渲染演示视频 demo.mp4

```shell
python ./tools/run_jnerf.py --config-file ./configs/jnerf/render_sample.py --task render
```



## 致谢

此项目基于下述论文实现，部分代码参考了 [jrender](https://github.com/Jittor/jrender) 和 [JNerf](https://github.com/Jittor/jnerf)。

```
@article{liu2019softras,
    title={Soft Rasterizer: A Differentiable Renderer for Image-based 3D Reasoning},
    author={Liu, Shichen and Li, Tianye and Chen, Weikai and Li, Hao},
    journal={The IEEE International Conference on Computer Vision (ICCV)},
    month = {Oct},
    year={2019}
}

@article{hu2020jittor,
    title={Jittor: a novel deep learning framework with meta-operators and unified graph execution},
    author={Hu, Shi-Min and Liang, Dun and Yang, Guo-Ye and Yang, Guo-Wei and Zhou, Wen-Yang},
    journal={Science China Information Sciences},
    volume={63},
    number={222103},
    pages={1--21},
    year={2020}
}

@article{mueller2022instant,
    author = {Thomas M\"uller and Alex Evans and Christoph Schied and Alexander Keller},
    title = {Instant Neural Graphics Primitives with a Multiresolution Hash Encoding},
    journal = {ACM Trans. Graph.},
    issue_date = {July 2022},
    volume = {41},
    number = {4},
    month = jul,
    year = {2022},
    pages = {102:1--102:15},
    articleno = {102},
    numpages = {15},
    url = {https://doi.org/10.1145/3528223.3530127},
    doi = {10.1145/3528223.3530127},
    publisher = {ACM},
    address = {New York, NY, USA},
}

@inProceedings{kato2018renderer
    title={Neural 3D Mesh Renderer},
    author={Kato, Hiroharu and Ushiku, Yoshitaka and Harada, Tatsuya},
    booktitle={The IEEE Conference on Computer Vision and Pattern Recognition (CVPR)},
    year={2018}
}

@inproceedings{mildenhall2020nerf,
    title={NeRF: Representing Scenes as Neural Radiance Fields for View Synthesis},
    author={Ben Mildenhall and Pratul P. Srinivasan and Matthew Tancik and Jonathan T. Barron and Ravi Ramamoorthi and Ren Ng},
    year={2020},
    booktitle={ECCV},
}
```