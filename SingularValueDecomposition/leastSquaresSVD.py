
import numpy as np

def lsSVD(data, tol) :
    #uses Singular Value Decomposition to estimate water usage with a specified error tolerance
    A = np.array(data[:,:len(data.T)-1])
    b = np.array(data[:,-1]).T
    
    U, S, VT = np.linalg.svd(A)

    r = sum(num >= tol for num in S)
    
    Sinv = np.zeros(A.shape).T
    Sinv[:r,:r] = np.diag(1/S[:r])
    print(Sinv)
 
    x = VT.T.dot(Sinv).dot(U.T).dot(b)
    
    Ax = np.matmul(A,x)
    norm = np.linalg.norm(b - Ax)
    
    return x, S, r, norm
        


#############################  main  #############################

if __name__ == "__main__" :
    data = np.genfromtxt("waterUsage.csv", dtype=None, delimiter=',', skip_header=5)
    
    # function lsSVD
    #      parameters:  2D numpy array, int
    #   return values:  1D numpy array, 1D numpy array, float
    #
    
    tolerance = 2.5
    x, S, r, norm = lsSVD(data, tolerance)
    
    print("singular values")
    print(S)
    
    print("\neffective rank = %d when tolerance is %.1f" % (r, tolerance))
    
    print("\nEstimates")
    print("    laundry = %5.1f gallons" % x[0])
    print(" dishwasher = %5.1f gallons" % x[1])
    print("     shower = %5.1f gallons" % x[2])
    print(" sprinklers = %5.1f gallons" % x[3])
    
    print("\nthe norm of the residual is %.1f" % norm)

