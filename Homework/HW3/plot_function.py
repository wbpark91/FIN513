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

    def h(x, dx = 0.01):
        return (g(x + dx) - g(x)) / dx

    x = np.arange(-1, 2.01, 0.01)

    # plot_function(x, f)
    # plot_function(x, g)
    # plot_function(x, h)

    fig = plt.figure(figsize = (16, 4))
    ax1 = fig.add_subplot(131)
    ax2 = fig.add_subplot(132)
    ax3 = fig.add_subplot(133)
    ax1.set_xlim(x[0], x[-1])
    ax1.set_title("$f(x)$")
    ax2.set_xlim(x[0], x[-1])
    ax2.set_title("$g(x)$")
    ax3.set_xlim(x[0], x[-1])
    ax3.set_title("$h(x)$")
    ax1.plot(x, f(x))
    ax2.plot(x, g(x))
    ax3.plot(x, h(x))
    plt.show()
