import numpy as np
import matplotlib.pyplot as plt

class LinearRegression(object):
    def __init__(self, n=20):
        self.n = n
        self.x = np.random.random(n) * 2 - 1
        self.p = np.array([
            np.random.uniform(low=-2.0, high=2.0),
            np.random.uniform(low=-1.0, high=1.0),
            np.random.uniform(low=-1.0, high=1.0)
        ])
        self.X = np.column_stack((self.x*self.x, self.x, np.ones(self.x.shape)))
        self.y = self.X.dot(self.p)
        self.y += np.random.normal(0, 0.1, self.y.shape)

    def compute(self):
        print "Actual parameter: ", self.p
        XTXinv = np.linalg.inv(self.X.T.dot(self.X))
        self.w = np.linalg.multi_dot((XTXinv, self.X.T, self.y))
        print "Estimated parameter: ", self.w

    def show(self):
        plt.plot(self.x, self.y, 'ro')
        x = np.linspace(-1,1,1000)
        X = np.column_stack((x*x, x, np.ones(x.shape)))
        y = np.dot(X, self.p)
        yw = np.dot(X, self.w)
        plt.plot(x, y, 'b-')
        plt.plot(x, yw, 'g--')
        plt.show()

lr = LinearRegression()
lr.compute()
lr.show()
