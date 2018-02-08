import numpy as np
import matplotlib.pyplot as plt

def plot_function(x, function):
    '''
    x: numpy array
    function: only input is range
    '''
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim(x[0], x[-1])
    ax.plot(x, function(x))
    plt.show()
    plt.close()

if __name__ == "__main__":
    def f(x):
        return (x ** 3 - 2 * x ** 2 + 1) / (1 + x ** 2)

    def g(x, dx = 0.01):
        return (f(x + dx) - f(x)) / dx

    x = np.arange(-1, 2.01, 0.01)

    plot_function(x, f)
    plot_function(x, g)
