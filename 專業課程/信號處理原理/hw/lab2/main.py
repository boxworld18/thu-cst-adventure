import librosa
import numpy as np
import argparse

def key_tone_recognition(audio_array):
    audio, sr = audio_array
    size = sr // 64
    S = np.abs(librosa.stft(y = audio, n_fft = size, hop_length = size, center = False))
    rms = librosa.feature.rms(y = audio, frame_length = size, hop_length = size, center = False)

    result = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"]
    for i, r in np.ndenumerate(rms[0]):
        x = np.argmax(np.array([S[11, i], S[12, i], S[13, i], S[15, i]]))
        y = np.argmax(np.array([S[19, i], S[21, i], S[23, i]]))
        print(result[x * 3 + y] if r > 0.5 else "-1", end=' ')

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--audio_file', type = str, help = 'test file name', required = True)
    args = parser.parse_args()
    input_audio_array = librosa.load(args.audio_file, sr = 48000, dtype = np.float32) # audio file is numpy float array
    key_tone_recognition(input_audio_array)