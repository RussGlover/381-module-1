from functools import partial
import time
import timeit
import numpy as np

DFT_TIME = 0.0
FFT_TIME = 0.0


def DFT(arr):
	arr = np.asarray(arr, dtype=float)
	length = arr.shape[0]
	n = np.arange(length)
	k = n.reshape(length, 1)
	M = np.exp(-2j * np.pi * k * n / length)
	return np.dot(M, arr)

def test():
	global DFT_TIME 
	DFT_TIME += 5

def FFT(sampled_arr):
	arr = np.asarray(sampled_arr, dtype=float)
	length = arr.shape[0]

	if length % 2 > 0:
		raise ValueError('Length of array must be a power of 2.')
	elif length <= 16:
		global DFT_TIME
		before = time.clock()
		z = DFT(arr)
		DFT_TIME += time.clock() - before
		return DFT(arr)
	else:
		arr_even = FFT(arr[::2])
		arr_odd = FFT(arr[1::2])
		constant_factor = np.exp(-2j * np.pi * np.arange(length)/length)
		return np.concatenate([arr_even + constant_factor[:length / 2] * arr_odd, arr_even + constant_factor[length / 2:] * arr_odd])



test_arr = np.random.random(1024)
before = time.clock()
FFT(test_arr)
FFT_TIME = time.clock() - before - DFT_TIME
print FFT_TIME, DFT_TIME
#DFT(test_arr)
np.fft.fft(test_arr)

def function_timer(test_func, test_data):
	return min(timeit.Timer(partial(test_func, test_arr)).repeat(repeat=3, number=5))

#print function_timer(FFT, test_arr)
#print function_timer(np.fft.fft, test_arr)