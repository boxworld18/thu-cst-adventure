import numpy as np
import matplotlib.pyplot as plt

# 时长为1秒
t = 1
# 采样率为60hz
fs = 60
t_split = np.arange(0, t * fs)


# 1hz与25hz叠加的正弦信号
x_1hz = t_split * 1 * np.pi * 2 / fs
x_25hz = t_split * 25 * np.pi * 2 / fs
signal_sin_1hz = np.sin(x_1hz)
signal_sin_25hz = np.sin(x_25hz)

signal_sin = signal_sin_1hz + 0.25 * signal_sin_25hz


# TODO: 补全这部分代码
# 通带边缘频率为10Hz，
# 阻带边缘频率为22Hz，
# 阻带衰减为44dB，窗内项数为17的汉宁窗函数
# 构建低通滤波器
# 函数需要返回滤波后的信号
def filter_fir(input):
    # init
    N = 17
    N1 = 8 - 0.0000001 # avoid zero division
    wp = 2 * np.pi * 10 / fs
    ws = 2 * np.pi * 22 / fs
    wc = (wp + ws) / 2
    
    # window function
    wn = np.array([0.5 + 0.5 * np.cos(2 * np.pi * (n - N1) / (N - 1)) for n in range(N)])
    hd = np.array([np.sin(wc * (n - N1)) / (np.pi * (n - N1)) for n in range(N)])
    hc = hd * wn
    
    # array extension
    input_ext = np.concatenate((input, np.zeros(len(hc))))
    hc_ext = np.concatenate((hc, np.zeros(len(input))))
    
    # convolution
    result = np.fft.fft(input_ext) * np.fft.fft(hc_ext)
    result = np.real(np.fft.ifft(result))
    return result[:len(input)]

# TODO: 首先正向对信号滤波(此时输出信号有一定相移)
# 将输出信号反向，再次用该滤波器进行滤波
# 再将输出信号反向
# 函数需要返回零相位滤波后的信号
def filter_zero_phase(input):
    result = np.flip(filter_fir(input))
    result = np.flip(filter_fir(result))
    return result

if __name__ == "__main__":
    delay_filtered_signal = filter_fir(signal_sin)
    zerophase_filtered_signal = filter_zero_phase(signal_sin)

    plt.plot(t_split, signal_sin, label = 'origin')
    plt.plot(t_split, delay_filtered_signal, label = 'fir')
    plt.plot(t_split, zerophase_filtered_signal, label = 'zero phase')

    plt.show()
