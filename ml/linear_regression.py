import sys
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class LinearRegression(object):
    def __init__(self, n=20):
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

class LinearRegression2D(object):
    def __init__(self, n=100):
        self.x1 = np.random.random(n) * 2 - 1
        self.x2 = np.random.random(n) * 2 - 1
        self.p = np.random.random(6) * 2 - 1
        self.p[0:2] *= 2
        self.y = self.quadratic(self.x1, self.x2, self.p)
        self.y += np.random.normal(0, 0.1, self.y.shape)

    def stack(self, x1, x2):
        return np.column_stack((
            x1*x1,
            x2*x2,
            x1*x2,
            x1,
            x2,
            np.ones(x1.shape),
        ))

    def quadratic(self, x1, x2, p):
        return self.stack(x1, x2).dot(p)

    def quadratic_meshgrid(self, x1, x2, p):
        X1, X2 = np.meshgrid(x1, x2)
        X1_ = X1.reshape(X1.size)
        X2_ = X2.reshape(X2.size)
        return self.stack(X1_, X2_).dot(p).reshape(X1.shape)

    def compute(self):
        print "Actual parameter: ", self.p
        X = self.stack(self.x1, self.x2)
        XTXinv = np.linalg.inv(X.T.dot(X))
        self.w = np.linalg.multi_dot((XTXinv, X.T, self.y))
        print "Estimated parameter: ", self.w

    def show(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.scatter(self.x1, self.x2, self.y, c='r', marker='o')

        x1 = np.linspace(-1,1,200)
        x2 = np.linspace(-1,1,200)
        X1, X2 = np.meshgrid(x1, x2)
        Y = self.quadratic_meshgrid(x1, x2, self.p)
        ax.plot_wireframe(X1, X2, Y, rstride=5, cstride=5)

        plt.show()

if len(sys.argv) == 2 and sys.argv[1] == '2':
    lr = LinearRegression2D()
else:
    lr = LinearRegression()
lr.compute()
lr.show()
