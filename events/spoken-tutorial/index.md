The Spoken Tutorial
=========================

## Index
1. [Requirements](#requirements)
1. [Getting started with iPython](#ipython)
1. [Using plot command interactively](#plotcommand)
1. [Embellishing a plot](#embellishplot)
1. [Saving plots](#savingplots)
1. [Multiple plots](#multipleplots)
1. [Subplots](#subplots)
1. [Additional features of iPython](#ipython_more)
1. [Loading data from files](#loadingdata)
1. [Plotting Data](#plottingdata)
1. [Other types of plots](#otherplots)
1. [Plotting Charts](#plottingcharts)
1. [Getting started with lists](#lists)
1. [Getting started with for](#for_loop)
1. [Getting started with strings](#string)
1. [Getting started with files](#files)
1. [Parsing data](#parsingdata)
1. [Getting started with arrays](#arrays)
1. [Accessing parts of arrays](#partsofarrays)
1. [Image manipulation using arrays](#imagemanipulation)
1. [Basic Matrix Operations](#basicmatrixops)
1. [Advanced Matrix Operations](#advancedmatrixops)
1. [Least square fit](#leastsquarefit)
1. [Testing and Debugging](#testingdebugging)
1. [Handling Errors and Exceptions](#errosandexceptions)
1. [References](#references)


<a id="requirements"></a>
## Requirements

* Ubuntu 14.04
* Python 3.4.3
* iPython 5.1.0
* pip3 install matplotlib


<a id="ipython"></a>
## 1. Getting started with iPython [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Getting+started+with+IPython/English/)

    $ pip3 install matplotlib
    ...

Now start `ipython3` and load `pylab` before doing anything else.

    $ ipython3
    In [1]: %pylab


<a id="plotcommand"></a>
## 2. Using plot command interactively [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Using+plot+command+interactively/English/)

    $ ipython3
    # now in ipython3 interpreter

    %pylab
    t = linspace(-pi, pi, 100)
    len(t)
    plot(t, cos(t))

    sinValues = sin(t)
    plot(t, sinValues)

    clf()    # clear the figure


<a id="embellishplot"></a>
## 3. Embellishing a plot [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Embellishing+a+plot/English/)

Objectives,
1. Modify plot attributes: color, line style, line width
1. Add title to the plot with embedded latex.
1. Label x and y axes
1. Add annotations to the plot
1. Set and get the limits of the axes


    $ ipython3

    %pylab
    
    x = linspace(-2, 4, 20)
    plot(x, sin(x))
    clf()

    plot(x, sin(x), 'r')                # red color
    plot(x, cos(x), linewidth=2)        #overlays the cos graph
    clf()

    plot(x, sin(x), 'b', linewidth=3)   # blue color
    clf()

    plot(x, sin(x), '.')                # dotted graph
    plot(x, cos(x), 'r--', linewidth=3) # a red dashed graph
    clf()

    plot(x, -x**2 + 4*x - 5, linewidth=2)
    title("Prabolic function $-x^2+4x-5$")
    xlabel("$x$")
    ylabel("$y$")
    annotate("local maxima", xy=(2, -1))# annotates a point in graph

    xlim()        # get x axis limits
    ylim()        # get y axis limits
    xlim(-4,5)    # set x axis limits
    ylim(-15,2)   # set y axis limits



<a id="savingplots"></a>
## 4. Saving plots [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Saving+plots/English/)

Objectives,
1. Save the plot in different formats


    $ ipython3

    %pylab

    x = linspace(-3*pi, 3*pi, 100)
    savefig("sine.png")             # saves the figure in png format
    savefig("sine.pdf")             # saves the figure in pdf format
    savefig("sine.ps")              # saves the figure in ps  format
    savefig("sine.eps")             # saves the figure in eps format
    savefig("sine.svg")             # saves the figure in svg format



<a id="multipleplots"></a>
## 5. Multiple plots [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Multiple+plots/English/)

Objectives,
1. Draw multiple plots which are overlaid
1. Use the figure command
1. Use the legend command
1. Switch between the plots and do operation on them


    $ ipython3

    %pylab
    x = linspace(0, 50, 10)
    plot(x, sin(x))
    y = linspace(0, 50, 500)
    plot(y, sin(y))               # plot is overlaid
    legend(['sin(x)', 'sin(y)'])  # list of string each associated with the plots created in order
    clf()

    x = linspace(0, 50, 500)
    figure(1)                     # names the plot as 1
    plot(x, sin(x), 'b')

    figure(2)                     # creates a new figure and names the plot as 2
    plot(x, cos(x), 'g')
    title('cos(x)')
    savefig('cosine.png')

    figure(1)                     # go back to plot 1
    title('sin(x)')
    savefig('sin.png')
 
  

<a id="subplots"></a>
## 6. Subplots [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Subplots/English/)

Objectives,
1. Create and switch between subplots


    $ ipython3

    %pylab
    
    x = linspace(0, 50, 500)
    plot(x, cos(x))
    y = linspace(0, 5, 100)
    plot(y, y**2)
    # the overly of plots doesn't look good, so we use subplots,
    # to draw them separately.

    subplot(2,1,1)    # no. of rows, no. of columns, subplot serial num.

    subplot(2,1,2)    # selects the lower subplot
    subplot(2,1,1)
    plot(x, cos(x))
    subplot(2,1,2)
    plot(y, y**2)
    clf()



<a id="ipython_more"></a>
## 7. Additional features of iPython [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Additional+features+of+IPython/English/)

Objectives,
1. Retrieve ipython history
1. View a part of the history
1. Save a part of the history to a file
1. Run a script from within ipython


    $ ipython3

    %pylab

    x = linspace(-2*pi, 2*pi, 100)
    plot(x, xsin(x))                  # error

    plot(x, x * sin(x))
    xlabel("$x$")
    ylabel("$y$")
    title("$x and x sin(x)$")

    %history -n                       # prints the history and numbers commands
    %history 5                        # prints 5th command
    %history -n 4-6 9                 # prints commands 4,5,6 and 9
    %save plot_script.py 2 4-7        # save command 2,4,5,6,7

    %run -i plot_script.py            # runs the script
    show()



<a id="loadingdata"></a>
## 8. Loading data from files [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Loading+Data+From+Files/English/)

Objectives,
1. Load data from files


    $ ipython3

    %pylab

    cat primes.txt            # display the file

    primes = loadtxt("primes.txt")
    print(primes)

    cat pendulum.txt          # this file has two columns
    pend = loadtxt("pendulum.txt")
    print(pend)

    L, T = loadtxt("pendulum.txt", unpack=True)
    print(L, T)

    cat pendulum_semicolon.txt
    L, T = loadtxt("pendulum_semicolon.txt", unpack=True, delimiter=";")
    print(L, T)



<a id="plottingdata"></a>
## 9. Plotting Data [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Plotting+Data/English/)

Objectives,
1. Define a list of numbers
1. Perform element wise squaring of the list
1. Plot data points
1. Plot error bars


    $ ipython3

    %pylab

    l = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
    t = [0.69, 0.90, 1.19, 1.30, 1.47, 1.58, 1.77, 1.83, 1.94]
    tsquare = square(t)
    plot(l, tsquare, '.')         # small dot 
    clf()

    plot(l, tsquare, 'o')         # large dot

    # with delta_t is the error list
    errorbar(t, tsquare, xerr=delta_t, yerr=delta_t, fmt="bo")

    plot(l, tsquare, 'r+')         # red color with '+' symbol plot


<a id="otherplots"></a>
## 10. Other types of plots [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Other+Types+Of+Plots/English/)

Objectives,
1. Create scatter plots
1. Create log-log plots


    $ ipython3

    %pylab

    cat company-a-data.txt            # the file has two columns
    year, profit = loadtxt("company-a-data.txt", unpack=True)

    scatter(year, profit)
    clf()

    scatter(year, profit, color='r', marker='d')
    clf()

    x = linspace(1, 20, 100)
    y = 5 * x**3
    loglog(x, y)              # plots a log-log graph


<a id="plottingcharts"></a>
## 11. Plotting Charts [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Plotting+Charts/English/)

[company-a-data.txt](files/company-a-data.txt)

Objectives:
1. Create pie charts
1. Create bar charts
1. Find more information on matplotlib


    ipython3
    # now inside ipython3 shell

    %pylab

    # create a pie chart
    # function: pie(values, labels = labels)   -- labels for each wedge

    # load the data file which has two columns
    year, profit = loadtxt("company-a-data.txt", unpack=True)
    clf()
    pie(profit, labels=year)

    # adjust colors
    pie?
    clf()
    pie(profit, lables=year, colors=('w', 'r', 'k', 'm', 'y', 'b', 'g', 'c', 'y', 'm', 'b'))

    # bar chart
    # function: bar(x, y) -- x and y are sequence of data of same length

    clf()
    bar(year, profit)
    clf()
    bar(year, profit, fill=False, hatch="/")  # a slanted hatched bar chart

    clf()
    bar(year, profit, fill=False, hatch="|")  # a vertical hatched bar chart



<a id="lists"></a>
## 12. Getting started with lists [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Getting+started+with+Lists/English/)

Objectives,
1. Create lists
2. Access list elements
3. Append elements to lists
4. Delete elements from lists


    $ ipython3
    # now inside ipython3 interpreter

    mylist = ['span', 'eggs', 100, 1.234]
    type(mylist)

    # mylist is a variable

    del mylist[1]
    mylist.append('span')
    mylist.remove('span')


<a id="for_loop"></a>
## 13. Getting started with for [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Getting+started+with+for/English/)

Objectives,
1. Use the for loop
1. Use range function


    $ ipython3
    # inside ipython3 interpreter

    # for <loop variable> in sequence:
    #     <loop body>

    print(range(1,50))
    print(range(1,50,2))


<a id="string"></a>
## 14. Getting started with strings [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Getting+started+with+strings/English/)

Objectives,
1. Define strings in different ways
1. Concatenate strings
1. Print a string repeatedly
1. Access individual elements of the string


    $ ipython3
    # now inside ipython3 interpreter

    # strings are immutable
    print("*" * 20)
    s = "Hello World! Is this day?"
    ss = s.split()
    ".".join(ss)


<a id="files"></a>
## 15. Getting started with files [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Getting+started+with+files/English/)

Objectives,
1. Open a file
1. Read the contents fo the file line by line
1. Read the entire content of file at once
1. Append the lines of a file to a list
1. Close the file


    $ ipython3
    # now inside ipython3 interpreter

    %pylab

    # file_obj = open(filename, mode)
    # mode can be: 'r' - Read mode
    #              'w' - Write mode
    #              'a' - Appending mode
    #              'r+'- Read and Write mode
    f = open("pendulum.txt")

    # read the whole file
    pend = f.read()
    print(pend)

    # break the string into lines
    pend_list = pend.splitlines() 

    # close the file
    f.close()

    f = open("pendulum.txt")
    for line in f:
        print(line)



<a id="parsingdata"></a>
## 16. Parsing data [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Parsing+data/English/)

[student_record.txt](files/student_record.txt)

Objectives,
1. Split a string using a delimiter
1. Remove the leading, trailing and all whitespaces in a string
1. Convert between diffrent built-in data types


    $ ipython3

    %pylab

    str1 = "Welcome to    Python tutorials"
    str1.split()

    x = "a;bc;d"
    x.split(";")                  # splits the string at semicolons

    unstripped = " Hello world "
    unstripped.strip()            # removes the beginning and trailing spaces

    mark_str = "1.25"
    mark     = float(mark_str)
    type(mark_str)
    type(mark)

    int("1.25")                   # error: invalid literral for int()
    flt = float("1.25")
    int(flt)                      # now its OK

    math_marks_A = []
    for line in open("student_record.txt"):
        fields = line.split(";")
        region_code = fields[0]
        region_code_stripped = region_code.strip()
        math_mark_str = fields[5]
        math_mark = float(math_mark_str)
        if region_code == "A":
            math_marks_A.append(math_mark)
 
    math_marks_mean = sum(math_marks_A)/len(math_marks_A)
    print(math_marks_mean)


<a id="statistics"></a>
## 17. Statistics [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Statistics/English/)

[student_record.txt](files/student_record.txt)
[football.txt](files/football.txt)

Objectives,
1. Do statistical operations in Python
1. Sum a set of numbers
1. Find their mean, mediean an standard deviation


Install Numpy separately.

    sudo apt-get install python3-pip
    # pip3 install numpy==1.13.3
    pip3 install numpy          # Successfully installed numpy-1.18.4


    $ ipython3
    
    import numpy as np
    L = np.loadtxt("student_record.txt", usecols=(3,4,5,6,7), delimiter=";")
    L

    L.shape         # prints (185667, 5)

    L[0]
    totalmarks = sum(L[0])
    totalmarks

    totalmarks/len(L[0])
    #or
    np.mean(L[0])

    # mean of the marks for each subjects
    np.mean?
    # get average marks of all students for each subject
    np.mean(L, 0)         # 0 means rows, 1 columns

    L[:,0]   # displays the first column in the array

    np.median(L[:,0])     # median marks of the first subject

    np.median(L, 0)       # median of each subject

    np.std(L[:,0])        # standard deviation of the first subject

    np.std(L, 0)          # standard deviation of each subject

    # Exercise
    # football.txt: contains player name, goals at home, goals away
    L = np.loadtxt('football.txt', usecols=(1,2), delimiter=",")

    # find total goals for each player
    np.sum(L, 1)

    # find mean of home and goals away
    np.mean(L, 0)

    # Find standard deviation of home and goals away
    np.std(L, 0)


    # Execise
    L = [[3,4,8,2,1],[4,3,6,2,1]]
    
    # get mean of each row
    np.mean(L, 1)   
    
    marks = [74,78,56,87,91,82]
    
    # get median of marks
    np.median(marks)


<a id="arrays"></a>
## 18. Getting started with arrays[(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Getting+started+with+arrays/English/)

1. Create arrays using data
1. Create arrays from list
1. Perform basic array operations
1. Create an *identity* matrix
1. Use the method *zeros*


    $ ipython3

    import numpy as np

    # array is a homogenious data structure (same data flow value)
    a1 = np.array([1,2,3,4])
    a1

    a2 = np.array([[1,2,3,4], [5,6,7,8]])
    a2                          
    
    # arange the  elements
    ar = np.arange(1,9)         # creates one dimensional elements from 1 to 9-1
    print(ar)                   # prints: [1,2,3,4,5,6,7,8]

    # change shape of the array
    ar.reshape(2,4)             # args: rows, columns. prints array([[1,2,3,4], [5,6,7,8]])
    ar                          # remains unchanged

    ar.shape = (2,4)
    ar                          # shape changed: array([[1,2,3,4], [5,6,7,8]])

    ar.shape                    # prints the shape: (2,4)
    a1.shape                    # prints the shape: (4,)

    a3 = np.array([1,2,3,'a string'])    # converts each element to string

    # create identity matrix
    np.identity(2)              # 2x2 identity matrix

    # zero matrix
    np.zeros(4,5)               # 4x5 zero matrix

    a1                          # prints: array([1,2,3,4])
    a1 * 2                      # prints: array([2,4,6,8])
    a1                          # prints: array([1,2,3,4])

    a1 = np.array([1,2,3,4])
    a2 = np.array([5,6,7,8])

    # element by element additon
    a1 + a2                     # prints: array([6,8,10,12])
    
    # element by element multiplication
    a1 * a2                     # prints: array([5,12,21,32])

    np.zeros_like?              # creates a zero matrix of the shape of the given matrix
    np.ones?                    # creates a ones matrix of the given shape
    np.ones_like?               # creates a ones matrix of the shape of the given matrix


<a id="partsofarrays"></a>
## 19. Accessing parts of arrays [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Accessing+parts+of+arrays/English/)

Objectives,
1. Access and change
    1. individual elements of single dimensional and multi-dimensional arrays
    1. Rows and columns of arrays
    1. Elements of an array, using slicing and striding


    # ipython3

    import numpy as np

    A = np.arange(1,6)           # creates array ([1,2,3,4,5])

    C = np.arange(1,26).reshape(5,5)      # a 5x5 matrix
    
    A[2]                          # access third element
    C[2,3]                        # access fouth element in third row

    A[2]   = -2
    C[2,3] = -14

    # Negative indexing: C[4] is same as C[-1]

    # changing more than one element at a time
    C[-1] = [0,0,0,0,0]           # changes last row

    C[-1] = 2                     # changes last row to [2,2,2,2,2]

    # slicing, striding [start:stop:step]
    C[0:3,2]
    C[2,0:3]
    C[1:3, 2:4]                   # slices a 2x2 matrix array([8,9],[13,14])

    # add steps
    C[::2, ::2]                   # array([[1,3,5],[11,13,15],[21,23,25]])




<a id="imagemanipulation"></a>
## 20. Image manipulation using arrays [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Image+manipulation+using+Arrays/English/)

[Python.png](files/Python.png)
[Squares.png](files/Squares.png)

Objectives,
1. Read images into arrays
1. Perform processing on them using simple array manipulations


    $ ipython3

    import matplotlib.pyplot as plt

    img = plt.imread("Squares.png")
    plt.imshow(img)
    plt.show()

    plt.imshow(img, cmap='gray')
    plt.show()

    img               # displays an array
    img.shape         # prints (300,300)

    img[:150,:150]    # get the top left quadrant

    plt.imshow(img[:150,:150])
    plt.show()

    plt.imshow(img[::2,::2])
    plt.show()

    plt.imshow(img[::4,::4])
    plt.show()


    img = plt.imread('files/Python.png')
    plt.imshow(img)
    plt.show()

    img.shape             # (600,600,4) -- has 4 channels

    plt.imshow(img[:,:,0])   # get the red channel
    plt.show()



<a id="basicmatrixops"></a>
## 21. Basic Matrix Operations

Objectives,
1. Create matrices from list
1. Preform basic matrix operations like,
    1. Addition
    1. Subtraction
    1. Multiplication
1. Perform operation to find out
    1. Determinant of a matrix
    1. Inverse of a matrix
    1. Eigen values and Eigher vectors of a matrix


    In [1]: from numpy import matrix
    
    In [2]: m1 = matrix([1,2,3,4])
    
    In [3]: m1
    Out[3]: matrix([[1, 2, 3, 4]])
    
    In [4]: m1.shape
    Out[4]: (1, 4)
    
    In [5]: l1 = [[1,2,3,4],[5,6,7,8]]
    
    In [6]: m2 = matrix(l1)
    
    In [7]: print(m2)
    [[1 2 3 4]
     [5 6 7 8]]
    
    In [8]: # convert array to matrix
    
    In [9]: from numpy import asmatrix, arange
       ...: m2_array = asmatrix(arange(1,9).reshape(2,4))
       ...: m2_array
       ...: 
    Out[9]: 
    matrix([[1, 2, 3, 4],
            [5, 6, 7, 8]])
    
    In [10]: m3 = asmatrix(arange(5,13).rehsape(2,4))
    ---------------------------------------------------------------------------
    AttributeError                            Traceback (most recent call last)
    <ipython-input-10-4de22be2b1c7> in <module>()
    ----> 1 m3 = asmatrix(arange(5,13).rehsape(2,4))
    
    AttributeError: 'numpy.ndarray' object has no attribute 'rehsape'
    
    In [11]: m3 = asmatrix(arange(5,13).reshape(2,4))
    
    In [12]: m3
    Out[12]: 
    matrix([[ 5,  6,  7,  8],
            [ 9, 10, 11, 12]])
    
    In [13]: m3 + m2
    Out[13]: 
    matrix([[ 6,  8, 10, 12],
            [14, 16, 18, 20]])
    
    In [14]: m3 - m2          # element by element subtraction
    Out[14]: 
    matrix([[4, 4, 4, 4],
            [4, 4, 4, 4]])
    
    In [15]: m3.shape == m2.shape
    Out[15]: True
    
    In [16]: m2.shape
    Out[16]: (2, 4)
    
    In [17]: m4 = asmatrix(arange(1,9).reshape(4,2))
    
    In [18]: m4.shape
    Out[18]: (4, 2)
    
    In [19]: m2 * m4
    Out[19]: 
    matrix([[ 50,  60],
            [114, 140]])
    
    In [20]: print(m4)
    [[1 2]
     [3 4]
     [5 6]
     [7 8]]
    
    In [21]: print(m4.T)    # transpose of a matrix
    [[1 3 5 7]
     [2 4 6 8]]
    
    In [22]: # determinant of a matrix
    
    In [25]: from numpy.linalg import det
        ...: m5 = matrix([[2,-3,1],[2,0,-1],[1,4,5]])
        ...: 
        ...: 
    
    In [26]: det(m5)     # determinant of m5
    Out[26]: 49.000000000000014
    
    In [27]: from numpy.linalg import inv
        ...: im5 = inv(m5)                   # inverse of a matrix
        ...: 
    
    In [28]: im5
    Out[28]: 
    matrix([[ 0.08163265,  0.3877551 ,  0.06122449],
            [-0.2244898 ,  0.18367347,  0.08163265],
            [ 0.16326531, -0.2244898 ,  0.12244898]])
    
    In [29]: from numpy import eye, allclose
    
    In [30]: allclose(im5 * m5, asmatrix(eye(3)))
    Out[30]: True
    
    In [31]: # eye(3) creates an identity matrix of shape 3x3
        ...: # allclose() returns True if both the given matrices are equal
        ...: 
    
    In [32]: # Eigen values and Eigen vectors
        ...: # Given a square matrix A
        ...: #   * eig(A)[0] gives its eigen values
        ...: #   * eig(A)[1] gives its eigen vector
        ...: #   * eigvals(A) gives its eigen values
        ...: # eig and eigvals functions are present in numpy.linalg module
        ...: 
    
    In [33]: from numpy import diag
        ...: from numpy.linalg import eig
        ...: m6 = asmatrix(diag((1,2,3)))
        ...: 
    
    In [34]: eig(m6)
    Out[34]: 
    (array([1., 2., 3.]), matrix([[1., 0., 0.],
             [0., 1., 0.],
             [0., 0., 1.]]))
    
    In [35]: eig_value = eig(m6)[0]
    
    In [36]: eig_value
    Out[36]: array([1., 2., 3.])
    
    In [37]: eig_vector = eig(m6)[1]
    
    In [38]: eig_vector
    Out[38]: 
    matrix([[1., 0., 0.],
            [0., 1., 0.],
            [0., 0., 1.]])
    
    In [39]: # another way to get eigen values
        ...: from numpy.linalg import eigvals
        ...: eig_value1 = eigvals(m6)
        ...: 
    
    In [40]: eig_value1
    Out[40]: array([1., 2., 3.])




<a id="advancedmatrixops"></a>
## 22. Advanced Matrix Operations [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Advanced+Matrix+Operations/English/)

Objectives,
1. find forbenious and infinity norm of a matrix
1. find singular value decomposition of a matrix


    In [1]: from numpy import asmatrix, arange
    
    In [2]: a = asmatrix(arange(1,10).reshape(3,3))
    
    In [3]: a
    Out[3]: 
    matrix([[1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]])
    
    In [4]: a.flatten()
    Out[4]: matrix([[1, 2, 3, 4, 5, 6, 7, 8, 9]])
    
    In [5]: # Forbenius norm
    
    In [6]: m = asmatrix(arange(1,17).reshape(4,4))
    
    In [7]: m[0,1]=0
    
    In [8]: m[1,3] = 0
    
    In [9]: m
    Out[9]: 
    matrix([[ 1,  0,  3,  4],
            [ 5,  6,  7,  0],
            [ 9, 10, 11, 12],
            [13, 14, 15, 16]])
    
    In [10]: from numpy.linalg import inv, norm
    
    In [11]: im = inv(m)
    
    In [12]: norm(im)
    Out[12]: 3.7059917700933944
    
    In [13]: # Infinity norm of a matrix -- max value of the sum of the abs value in each row
    
    In [14]: from numpy import inf
    
    In [15]: norm(im, ord=inf)
    Out[15]: 4.624999999999995
    
    In [16]: # norm?
    
    In [17]: # singular value decomposition (svd) - factorization of matrix
    
    In [18]: from numpy import matrix
    
    In [19]: from numpy.linalg import svd
    
    In [20]: m1 = matrix([[3,2,2],[2,3,-2]])
    
    In [21]: U, sigma, V_conjugate = svd(m1)
    
    In [22]: U
    Out[22]: 
    matrix([[-0.70710678, -0.70710678],
            [-0.70710678,  0.70710678]])
    
    In [23]: sigma
    Out[23]: array([5., 3.])
    
    In [24]: V_conjugate
    Out[24]: 
    matrix([[-7.07106781e-01, -7.07106781e-01, -6.47932334e-17],
            [-2.35702260e-01,  2.35702260e-01, -9.42809042e-01],
            [-6.66666667e-01,  6.66666667e-01,  3.33333333e-01]])
    
    In [25]: from numpy import diag, allclose
    
    In [26]: from numpy.matlib import zeros
    
    In [27]: smat = zeros((2,3))
    
    In [28]: smat
    Out[28]: 
    matrix([[0., 0., 0.],
            [0., 0., 0.]])
    
    In [29]: smat[:2, :2] = diag(sigma)
    
    In [30]: smat
    Out[30]: 
    matrix([[5., 0., 0.],
            [0., 3., 0.]])
    
    In [31]: diag(sigma)
    Out[31]: 
    array([[5., 0.],
           [0., 3.]])
    
    In [32]: allclose(m1, U * smat * V_conjugate)
    Out[32]: True
    
    In [33]: # True means both the matrices given to allclose() are the same
    
    In [34]: # Note: norm(A, ord='fro') == norm(A)  # fro stands for frobenious norm    
    
    In [35]: 



<a id="leastsquarefit"></a>
## Least square fit

[pendulum.txt](files/pendulum.txt)

Objectives,
1. Generate the least square fit line for the given set of points


    In [1]: # generate least square fit line for L v/s t^2 using pendulum.txt
    
    In [2]: # pendulum.txt: has two columns: first is length, second is the time
    
    In [3]: # squre of the time priod is directly proportional to the lenght
    
    In [4]: from numpy import loadtxt
    
    In [7]: L, t = loadtxt("files/pendulum.txt", unpack=True)
    
    In [8]: L
    Out[8]: 
    array([0.1 , 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2 ,
           0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3 , 0.31,
           0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.4 , 0.41, 0.42,
           0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.5 , 0.51, 0.52, 0.53,
           0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.6 , 0.61, 0.62, 0.63, 0.64,
           0.65, 0.66, 0.67, 0.68, 0.69, 0.7 , 0.71, 0.72, 0.73, 0.74, 0.75,
           0.76, 0.77, 0.78, 0.79, 0.8 , 0.81, 0.82, 0.83, 0.84, 0.85, 0.86,
           0.87, 0.88, 0.89, 0.9 , 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97,
           0.98, 0.99])
    
    In [9]: t
    Out[9]: 
    array([0.69004, 0.69497, 0.74252, 0.7536 , 0.83568, 0.86789, 0.84182,
           0.85379, 0.85762, 0.8839 , 0.89985, 0.98436, 1.0244 , 1.0572 ,
           0.99077, 1.0058 , 1.0727 , 1.0943 , 1.1432 , 1.1045 , 1.1867 ,
           1.1385 , 1.2245 , 1.2406 , 1.2071 , 1.2658 , 1.2995 , 1.3142 ,
           1.2663 , 1.2578 , 1.2991 , 1.3058 , 1.3478 , 1.3506 , 1.4044 ,
           1.3948 , 1.38   , 1.448  , 1.4168 , 1.4719 , 1.4656 , 1.4399 ,
           1.5174 , 1.4988 , 1.4751 , 1.5326 , 1.5297 , 1.5372 , 1.6094 ,
           1.6352 , 1.5843 , 1.6643 , 1.5987 , 1.6585 , 1.6317 , 1.7074 ,
           1.6654 , 1.6551 , 1.6964 , 1.7143 , 1.7706 , 1.7622 , 1.726  ,
           1.8089 , 1.7905 , 1.7428 , 1.8381 , 1.8182 , 1.7865 , 1.7995 ,
           1.8296 , 1.8625 , 1.8623 , 1.8383 , 1.8593 , 1.8944 , 1.9598 ,
           1.9    , 1.9244 , 1.9397 , 1.944  , 1.9718 , 1.9383 , 1.9555 ,
           2.0006 , 1.9841 , 2.0066 , 2.0493 , 2.0503 , 2.0214 ])
    
    In [10]: # loadtxt?
    
    In [11]: import matplotlib.pyplot as plt
    
    In [12]: 
    (python3:17510): dbind-WARNING **: 07:38:03.489: Error retrieving accessibility bus address: org.freedesktop.DBus.Error.ServiceUnknown: The name org.a11y.Bus was not provided by any .service files
    QApplication: invalid style override passed, ignoring it.
    In [12]: 
    
    In [12]: tsq = t * t
    
    In [13]: plt.plot(L, tsq, 'bo')
    Out[13]: [<matplotlib.lines.Line2D at 0x7ff6be2fb588>]
    
    In [14]: plt.show()
    
    In [15]: # fit a line through: t^2 = m * L + c, where m is the slope and c is the constant
    
    In [16]: # we need to find m and c
    
    In [17]: from numpy import array, ones_like
    
    In [18]: inter_mat = array((L, ones_like(L)))
    
    In [19]: inter_mat
    Out[19]: 
    array([[0.1 , 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2 ,
            0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3 , 0.31,
            0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.4 , 0.41, 0.42,
            0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.5 , 0.51, 0.52, 0.53,
            0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.6 , 0.61, 0.62, 0.63, 0.64,
            0.65, 0.66, 0.67, 0.68, 0.69, 0.7 , 0.71, 0.72, 0.73, 0.74, 0.75,
            0.76, 0.77, 0.78, 0.79, 0.8 , 0.81, 0.82, 0.83, 0.84, 0.85, 0.86,
            0.87, 0.88, 0.89, 0.9 , 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97,
            0.98, 0.99],
           [1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  , 1.  ,
            1.  , 1.  ]])
    
    In [20]: A = inter_mat.T     # take transpose
    
    In [21]: A
    Out[21]: 
    array([[0.1 , 1.  ],
           [0.11, 1.  ],
           [0.12, 1.  ],
           [0.13, 1.  ],
           [0.14, 1.  ],
           [0.15, 1.  ],
           [0.16, 1.  ],
           [0.17, 1.  ],
           [0.18, 1.  ],
           [0.19, 1.  ],
           [0.2 , 1.  ],
           [0.21, 1.  ],
           [0.22, 1.  ],
           [0.23, 1.  ],
           [0.24, 1.  ],
           [0.25, 1.  ],
           [0.26, 1.  ],
           [0.27, 1.  ],
           [0.28, 1.  ],
           [0.29, 1.  ],
           [0.3 , 1.  ],
           [0.31, 1.  ],
           [0.32, 1.  ],
           [0.33, 1.  ],
           [0.34, 1.  ],
           [0.35, 1.  ],
           [0.36, 1.  ],
           [0.37, 1.  ],
           [0.38, 1.  ],
           [0.39, 1.  ],
           [0.4 , 1.  ],
           [0.41, 1.  ],
           [0.42, 1.  ],
           [0.43, 1.  ],
           [0.44, 1.  ],
           [0.45, 1.  ],
           [0.46, 1.  ],
           [0.47, 1.  ],
           [0.48, 1.  ],
           [0.49, 1.  ],
           [0.5 , 1.  ],
           [0.51, 1.  ],
           [0.52, 1.  ],
           [0.53, 1.  ],
           [0.54, 1.  ],
           [0.55, 1.  ],
           [0.56, 1.  ],
           [0.57, 1.  ],
           [0.58, 1.  ],
           [0.59, 1.  ],
           [0.6 , 1.  ],
           [0.61, 1.  ],
           [0.62, 1.  ],
           [0.63, 1.  ],
           [0.64, 1.  ],
           [0.65, 1.  ],
           [0.66, 1.  ],
           [0.67, 1.  ],
           [0.68, 1.  ],
           [0.69, 1.  ],
           [0.7 , 1.  ],
           [0.71, 1.  ],
           [0.72, 1.  ],
           [0.73, 1.  ],
           [0.74, 1.  ],
           [0.75, 1.  ],
           [0.76, 1.  ],
           [0.77, 1.  ],
           [0.78, 1.  ],
           [0.79, 1.  ],
           [0.8 , 1.  ],
           [0.81, 1.  ],
           [0.82, 1.  ],
           [0.83, 1.  ],
           [0.84, 1.  ],
           [0.85, 1.  ],
           [0.86, 1.  ],
           [0.87, 1.  ],
           [0.88, 1.  ],
           [0.89, 1.  ],
           [0.9 , 1.  ],
           [0.91, 1.  ],
           [0.92, 1.  ],
           [0.93, 1.  ],
           [0.94, 1.  ],
           [0.95, 1.  ],
           [0.96, 1.  ],
           [0.97, 1.  ],
           [0.98, 1.  ],
           [0.99, 1.  ]])
    
    In [22]: from numpy.linalg import lstsq
        ...: result = lstsq(A, tsq, rcond=None)
        ...: 
    
    In [23]: result
    Out[23]: 
    (array([4.14148447, 0.07358041]),
     array([0.63609563]),
     2,
     array([10.8710938 ,  2.15077185]))
    
    In [24]: p = result[0]
    
    In [25]: m, c = p
    
    In [26]: m
    Out[26]: 4.1414844663694295
    
    In [27]: c
    Out[27]: 0.07358041497643943
    
    In [28]: tsq_fit = m * L + c
        ...: plt.plot(L, tsq, 'bo')
        ...: plt.plot(L, tsq_fit, 'r')
        ...: 
    Out[28]: [<matplotlib.lines.Line2D at 0x7ff6adde6ac8>]
    
    In [29]: plt.show()
    
    In [30]: # we learned to generate the least square fit line
    
    In [31]: ones_like([1,2,3])
    Out[31]: array([1, 1, 1])
    


<a id="testingdebugging"></a>
## Testing and Debugging

Creating manual test cases with inputs from files.


<a id="errosandexceptions"></a>
## Handling Errors and Exceptions

[mymodule.py](files/mymodule.py)

    In [1]: from files import mymodule
    
    In [2]: cat files/mymodule.py
    def test():
        prod = 1
        for i in range(0, 10):
            prod *= i / (i - 5)
        print(prod)
    
    In [3]: mymodule.test()
    ---------------------------------------------------------------------------
    ZeroDivisionError                         Traceback (most recent call last)
    <ipython-input-3-d0b28c8765cd> in <module>()
    ----> 1 mymodule.test()
    
    /home/codeman/.itsoflife/knots-git/events/spoken-tutorial/files/mymodule.py in test()
          2     prod = 1
          3     for i in range(0, 10):
    ----> 4         prod *= i / (i - 5)
          5     print(prod)
          6 
    
    ZeroDivisionError: division by zero
    
    In [4]: %debug
    > /home/codeman/.itsoflife/knots-git/events/spoken-tutorial/files/mymodule.py(4)test()
          2     prod = 1
          3     for i in range(0, 10):
    ----> 4         prod *= i / (i - 5)
          5     print(prod)
          6 
    
    ipdb> i
    5
    ipdb> q
    


<a id="references"></a>
## References
1. [Spoken Tutorial Page][1]
2. [Help for matplotlib][2]
3. [Example plots][3]

[1]: https://spoken-tutorial.org/tutorial-search/?search_foss=Python%203.4.3&search_language=English&page=1
[2]: matplotlib.sourceforge.net/contents.html
[3]: matplotlib.sourceforge.net/users/screenshots.html


