import unittest
import numpy as np

class TestFourierTransform(unittest.TestCase):

	def setUp(self):
		self.sine_arr = np.sin(np.linspace(-np.pi, np.pi, 200))

	def test_fourier(self):
		print np.fft.fft(self.sine_arr)
		print 

if __name__ == '__main__':
	unittest.main()