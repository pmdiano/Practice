import numpy as np

class LinearRegression(object):
    def __init__(self, n=20):
        self.n = n
        self.x = np.random.random(n) * 100
        self.params = np.array([
            np.random.uniform(low=-1.0, high=1.0),
            np.random.uniform(low=-10.0, high=10.0),
            np.random.uniform(low=-100.0, high=100.0)
        ])

    def show(self):
        print self.x, self.x.shape
        print self.params, self.params.shape

lr = LinearRegression()
lr.show()
