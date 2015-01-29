import unittest
from pylab import plot, show
import numpy as np
import fft.fft as fft

class TestFourierTransform(unittest.TestCase):

	def setUp(self):
		self.window_size = 1024
		self.sample_rate = 2048
		self.test_freq = 200
		self.sine_arr = np.sin(np.linspace(0, self.test_freq*np.pi, self.window_size))
		self.frequencies = np.fft.fftfreq(self.window_size, 1/float(self.sample_rate))
		self.fft_arr = fft.fft(self.sine_arr)
		self.numpy_fft_arr = np.fft.fft(self.sine_arr)
		self.magnitudes = np.array([abs(x) for x in self.fft_arr])
		self.magnitudes_numpy = np.array([abs(x) for x in self.numpy_fft_arr])

	def test_fourier(self):
		self.assertTrue(np.allclose(self.fft_arr, self.numpy_fft_arr))

	def test_plot(self):
		plot(self.frequencies[:len(self.frequencies)/2:], self.magnitudes[:len(self.frequencies)/2:], self.frequencies[:len(self.frequencies)/2:], self.magnitudes_numpy[:len(self.frequencies)/2:])
		show()

if __name__ == '__main__':
	unittest.main()