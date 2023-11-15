import matplotlib.pyplot as plt

if __name__ == "__main__":
    f = open('data.txt', 'r')
    lines = f.readlines()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    fig2d = plt.figure()
    ax2d = fig2d.add_subplot(111)
    
    
    naive = [], [], []
    share = [], [], []
    
    naive2d = [], [], []
    share2d = [], [], []
    
    naive2d2 = [], [], []
    share2d2 = [], [], []
    
    best_time = 20
    best_config = []
    
    for idx, line in enumerate(lines):
        data = line.split(' ')
        method, x, y, _, time, _ = data
        
        if method == 'naive':
            naive[0].append(int(x))
            naive[1].append(int(y))
            naive[2].append(float(time))
            if int(y) == 1:
                naive2d[0].append(int(x))
                naive2d[1].append(float(time))
            elif int(y) == 2:
                naive2d2[0].append(int(x)) 
                naive2d2[1].append(float(time))
        else:
            share[0].append(int(x))
            share[1].append(int(y))
            share[2].append(float(time))
            if int(y) == 1:
                share2d[0].append(int(x))
                share2d[1].append(float(time))
            elif int(y) == 2:
                share2d2[0].append(int(x))
                share2d2[1].append(float(time))
        
        if best_time > float(time):
            best_time = float(time)
            best_config = [method, x, y, time]
        
    print('| x | y | naive | shared memory |')
    print('| ---- | ---- | ---- | ---- |')
    for idx in range(len(naive[0])):
        print('| {} | {} | {} | {} |'.format(naive[0][idx], naive[1][idx], naive[2][idx], share[2][idx]))
        
    ax.scatter(naive[0], naive[1], naive[2], label = 'naive')
    ax.scatter(share[0], share[1], share[2], label = 'shared memory', c = 'r', marker = '^')

    ax.set_xlabel('x-label')
    ax.set_ylabel('y-label')
    ax.set_zlabel('time(ms)')
    
    ax.legend(loc = 'upper right')
    
    # plot a 2D graph using the best configuration
    ax2d.plot(naive2d[0], naive2d[1], label = 'naive, x=1')
    ax2d.plot(naive2d2[0], naive2d2[1], label = 'naive, y=2', linestyle = 'dashed')
    ax2d.plot(share2d[0], share2d[1], label = 'shared memory, y=1', c = 'r')
    ax2d.plot(share2d2[0], share2d2[1], label = 'shared memory, y=2', linestyle = 'dashed')
    ax2d.set_xlabel('x-label')
    ax2d.set_ylabel('time(ms)') 
    ax2d.legend(loc = 'upper right')
    
    plt.show()
    
    