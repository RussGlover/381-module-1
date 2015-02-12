from functools import partial
import time
import timeit
import numpy as np
from math import sqrt, sin
import librosa
from os import listdir, getcwd
from os.path import isfile, join, dirname, abspath


def dft(arr):
	arr = np.asarray(arr, dtype=float)
	length = arr.shape[0]
	n = np.arange(length)
	k = n.reshape(length, 1)
	M = np.exp(-2j * np.pi * k * n / length)
	return np.dot(M, arr)

def fft(sampled_arr):
	arr = np.asarray(sampled_arr, dtype=float)
	length = arr.shape[0]

	if length % 2 > 0:
		raise ValueError('Length of array must be a power of 2.')
	elif length <= 16:
		return dft(arr)
	else:
		arr_even = fft(arr[::2])
		arr_odd = fft(arr[1::2])
		constant_factor = np.exp(-2j * np.pi * np.arange(length)/length)
		return np.concatenate([arr_even + constant_factor[:length / 2] * arr_odd, arr_even + constant_factor[length / 2:] * arr_odd])

def function_timer(test_func, test_data):
	return min(timeit.Timer(partial(test_func, test_arr)).repeat(repeat=3, number=5))

def euclidean_distance(arr1, arr2):
	distance_squared = 0
	for index, x in enumerate(arr1):
		distance_squared += (x - arr2[index])**2
	return sqrt(distance_squared)


cache = {}

def extract_magnitudes(number, path):

	def memoize(number, path):
		if (number, path) in cache:
			return cache[(number, path)]
		else:
			cache[(number, path)] = extract_mags(number, path)
			return cache[(number, path)]

	def extract_samples(filepath):
		return librosa.load(filepath, sr=32000, offset=60.0, duration=60.0)

	def extract_mags(number, path):
		arr, sample_rate = extract_samples(path + '/' + str(number) + '.mp3')
		scale = max((abs(min(arr)), abs(max(arr))))
		arr = 2*arr/scale
		arr = arr.reshape(-1, 1024)
		ffts = [np.fft.fft(x) for x in arr]
		return [abs(x)[:512:] for x in ffts]

	return memoize(number, path)

def get_medians(number_songs, genre):
	magnitudes = []
	medians = []
	for x in xrange(1, number_songs):
		magnitudes += extract_magnitudes(x, genre)
	for i in xrange(512):
		medians.append(np.median([magnitude[i] for magnitude in magnitudes]))
	return medians

def get_medians_for_song(song, genre):
	magnitudes = []
	medians = []
	magnitudes += extract_magnitudes(song, genre)
	for i in xrange(512):
		medians.append(np.median([magnitude[i] for magnitude in magnitudes]))
	return medians


def rescale_medians(medians):
	rescaled = []
	i = 0
	while len(rescaled) < 8:
		rescaled.append(sum(medians[i:i+64]))
		i += 64
	scale_factor = 10000/max(rescaled)
	rescaled = [int(scale_factor*x) for x in rescaled]
	# rescaled = medians
	return rescaled


classical = getcwd() + '/classicalmusic'
pop = getcwd() + '/popmusic'

def classify(number, genre):
	test_genre = extract_magnitudes(number, genre)
	pop_distance = []
	classical_distance = []
	print("getting medians")
	pop_medians = get_medians(30, pop)
	classical_medians = get_medians(30, classical)
	print("Done getting medians")

	print("euclidean_distance")
	for test_magnitude in test_genre:
		pop_distance.append(euclidean_distance(test_magnitude, pop_medians))
		classical_distance.append(euclidean_distance(test_magnitude, classical_medians))
	print("Done distance")
	if np.median(pop_distance) > np.median(classical_distance):
		return "Classical"
	else:
		return "Pop"
# z = rescale_medians(get_medians(4, classical))
def test_acc(number, genre):
	classical_factors = [10000, 1866, 585, 345, 242, 189, 159, 145]
	pop_factors = [10000, 2973, 1782, 1386, 1135, 931, 614, 394]
	misclassified = 0
	for x in xrange(40, 40 + number):
		if genre == classical:
			if euclidean_distance(classical_factors, rescale_medians(get_medians_for_song(x, genre))) > euclidean_distance(pop_factors, rescale_medians(get_medians_for_song(x, genre))):
				misclassified += 1
		else:
			if euclidean_distance(classical_factors, rescale_medians(get_medians_for_song(x, genre))) < euclidean_distance(pop_factors, rescale_medians(get_medians_for_song(x, genre))):
				misclassified += 1
	return (number - misclassified)/number, misclassified, number

print(test_acc(10, classical))

# y1 = rescale_medians(get_medians_for_song(51, classical))
# y2 = rescale_medians(get_medians_for_song(52, classical))
# y3 = rescale_medians(get_medians_for_song(53, classical))
# z1 = rescale_medians(get_medians_for_song(51, pop))
# z2 = rescale_medians(get_medians_for_song(52, pop))
# z3 = rescale_medians(get_medians_for_song(53, pop))
# c = rescale_medians(get_medians(35, classical))
# p = rescale_medians(get_medians(35, pop))
# print(euclidean_distance(y1, c), "classical1 to classical", euclidean_distance(y1, p), "classical1 to pop")
# print(euclidean_distance(y2, c), "classical2 to classical", euclidean_distance(y2, p), "classical2 to pop")
# print(euclidean_distance(y3, c), "classical3 to classical", euclidean_distance(y3, p), "classical3 to pop")
# print(euclidean_distance(z1, p), "pop1 to pop", euclidean_distance(z1, c), "pop1 to classical")
# print(euclidean_distance(z2, p), "pop2 to pop", euclidean_distance(z2, c), "pop2 to classical")
# print(euclidean_distance(z3, p), "pop3 to pop", euclidean_distance(z3, c), "pop3 to classical")
# print("Classical:", c, "Pop:", p)

# print(get_medians(5, classical))

# for x in xrange(50, 75):
# 	print(classify(x, pop))
# 	print(classify(x, classical))

# y = [int(10*sin(x)) for x in range(1024)]
# fftvals = np.fft.fft(y)
# mag_fft = abs(fftvals)
# largest = max(mag_fft)
# largest_index = -10
# for index, z in enumerate(mag_fft):
# 	if largest == z:
# 		largest_index = index
# 	print(index, z, largest_index)
