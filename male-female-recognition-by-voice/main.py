import sys
# from matplotlib import pyplot as plt
import numpy as np
import scipy.io.wavfile as wav
import warnings

warnings.filterwarnings("ignore")
human = [85, 280]
woman = [172.5, 280]
men = [85, 172.5]
border = [165, 180]


def read_signal():
    file_path = sys.argv[1]
    F, signal = wav.read(file_path)
    if signal.ndim > 1:
        signal = signal.mean(axis=1)
    return F, signal


def window_signal(signal):
    return signal.copy() * np.kaiser(len(signal), 50)


def get_spectrum(signal):
    spectrum = np.fft.fft(signal)[: len(signal) // 2]
    spectrum = np.abs(spectrum)
    return spectrum


def get_freqs(F, n):
    TW = 1 / F
    freqs = np.fft.fftfreq(n, TW)[: n // 2]
    return freqs


def resample_signal(F, signal, new_F):
    new_signal = signal.copy()[:: int(F / new_F)]
    return new_signal


def cut_non_human(freqs, spectrum):
    spectrum_copy = spectrum.copy()
    for i in range(len(freqs)):
        if freqs[i] < human[0] or freqs[i] > human[1]:
            spectrum_copy[i] = 0
    return spectrum_copy


# fig, axs = plt.subplots(5, 1, figsize=(10, 10))
# current_plt_index = 0


# def draw_spectrum(freqs, spectrum):
#     global current_plt_index
#     axs[current_plt_index].plot(freqs, spectrum)
#     axs[current_plt_index].set_xlabel("Częstotliwość [Hz]")
#     axs[current_plt_index].set_xlim([0.01, 23000])
#     axs[current_plt_index].set_xscale("log")
#     current_plt_index += 1


def hps(spectrum, freqs, iterations):
    final_spectrum = spectrum.copy()
    for i in range(2, iterations):
        new_F = F / i
        resample = resample_signal(F, spectrum, new_F)
        final_spectrum[: len(resample)] *= resample
    final_spectrum = cut_non_human(freqs, final_spectrum)
    return freqs[np.argmax(final_spectrum)]


F, signal = read_signal()
signal = window_signal(signal)
spectrum = get_spectrum(signal)
freqs = get_freqs(F, len(signal))
tone = hps(spectrum, freqs, 5)
if tone > men[0] and tone < men[1]:
    print("M")
else:
    print("K")
