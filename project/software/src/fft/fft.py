from functools import partial
import time
import timeit
import numpy as np


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