
import numpy as np
import matplotlib.pyplot as plt

def processPoints(ps, pc, points) :
    x1 = ps[0][0]
    x2 = ps[0][1]
    x3 = ps[0][2]
    x4 = ps[0][3]
    y1 = ps[1][0]
    y2 = ps[1][1]
    y3 = ps[1][2]
    y4 = ps[1][3]
    
    xp1 = pc[0][0]
    xp2 = pc[0][1]
    xp3 = pc[0][2]
    xp4 = pc[0][3]
    yp1 = pc[1][0]
    yp2 = pc[1][1]
    yp3 = pc[1][2]
    yp4 = pc[1][3]

    a = np.array([[x1, y1,1,0,0,0,0,0,-xp1,0,0,0],
                  [0,0,0,x1,y1,1,0,0,-yp1,0,0,0],
                  [0,0,0,0,0,0,x1,y1,-1,0,0,0],
                  [x2,y2,1,0,0,0,0,0,0,-xp2,0,0],
                  [0,0,0,x2,y2,1,0,0,0,-yp2,0,0],
                  [0,0,0,0,0,0,x2,y2,0,-1,0,0],
                  [x3,y3,1,0,0,0,0,0,0,0,-xp3,0],
                  [0,0,0,x3,y3,1,0,0,0,0,-yp3,0],
                  [0,0,0,0,0,0,x3,y3,0,0,-1,0],
                  [x4,y4,1,0,0,0,0,0,0,0,0,-xp4],
                  [0,0,0,x4,y4,1,0,0,0,0,0,-yp4],
                  [0,0,0,0,0,0,x4,y4,0,0,0,-1]])
    
    b = np.array([0,0,-1,0,0,-1,0,0,-1,0,0,-1]).T
    
    s = np.linalg.solve(a,b)
    H = np.array([[s[0],s[1],s[2]],
                  [s[3],s[4],s[5]],
                  [s[6],s[7], 1]])
    
    m = np.full((1,len(points)),1)
    np.append(points,m)
    
    w = np.matmul(H,points)
    print(w)
    projected = np.divide(w,w[2,:])
    projected = projected[0:2,:]

    
    return H, projected
    
     



def plotPoints(projected, test_points) :
    #
    #  DO NOT MODIFY THIS SECTION
    #
    
    plt.plot(test_points[0, :], test_points[1, :], '-o')
    plt.title('skewed points')
    # from https://stackoverflow.com/questions/16183462/saving-images-in-python-at-a-very-high-quality
    #plt.savefig('homographySkewed.eps', format='eps', dpi=1000)

    plt.figure(2)
    plt.plot(projected[0, :], projected[1, :], 'r-o')
    plt.title('corrected points')
    #plt.savefig('homographyCorrected.eps', format='eps', dpi=1000)

    plt.show()
    
###################  main  ###################
if __name__ == "__main__" :
    #
    #  DO NOT MODIFY THIS SECTION
    #
    
    
    # points in skewed picture to use for mapping
    # each column is a vector representing the x/y coordinates of a point
    #   in the skewed picture
    # row 1 is the x-values
    # row 2 is the y-values
    points_skewed = np.array([[0,   0, 50, 50],
                              [0, 100, 75, 25]])
    
    # points in corrected picture to use for mapping
    # each column is a vector representing the x/y coordinates of a point
    #   in the corrected picture
    # row 1 is the x-values
    # row 2 is the y-values
    points_corrected = np.array([[0,   0, 200, 200], 
                                 [0, 100, 100,   0 ]])
    
    # each column is the set of x/y coordinates of a point that should be corrected
    test_points = np.array([[42.8571, 38.4615, 33.3333, 27.2727, 20, 11.1111, 20, \
                             27.2727, 33.3333, 38.4615, 42.8571, 46.6667, 42.8571],
                            [50,      65.3846, 66.6667, 68.1818, 50, 27.7778, 30, \
                             31.8182, 33.3333, 34.6154, 35.7143, 36.6667, 50],
                            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]])
      
    H, projected = processPoints(points_skewed, points_corrected, test_points)
    print('part a: H matrix\n')
    print(H)
    print('\npart b: projected test points (not as homogeneous coordinates)\n')
    print(projected)
    
    plotPoints(projected, test_points) 
