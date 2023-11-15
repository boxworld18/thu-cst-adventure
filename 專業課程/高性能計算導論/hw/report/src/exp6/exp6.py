import matplotlib.pyplot as plt

# 数据
bitwidths = [2, 4, 8]
strides = [1, 2, 4, 8, 16, 32]
bandwidths = [
    [4236.73, 8149.93, 8648.63],
    [4303, 4309.13, 4339.57],
    [2161.88, 2028.73, 2173.54],
    [829.905, 1012.96, 1087.65],
    [427.725, 504.418, 544.071],
    [214.939, 250.814, 544.07]
]
bandwidth_gm = [530.02, 182.489, 91.9961, 46.2886]
# 绘图
for i in range(len(bitwidths)):
    plt.semilogy(range(0, 6), [bandwidths[j][i] for j in range(len(strides))], label=f'Bitwidth={bitwidths[i]}')
# plt.semilogy(strides[:4], bandwidth_gm, label='global mem')
plt.legend()
plt.xlabel('Stride')
plt.ylabel('Bandwidth (log scale)')

# 增加 y 轴刻度
yticks = [200, 600, 2000, 8000]
plt.yticks(yticks, [str(y) for y in yticks])

xticks = [1, 2, 4, 8, 16, 32]
plt.xticks(range(0, 6), [str(x) for x in xticks])

plt.show()