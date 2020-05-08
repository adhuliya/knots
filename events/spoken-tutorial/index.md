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
## Parsing data [(Link)](https://spoken-tutorial.org/watch/Python+3.4.3/Parsing+data/English/)

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



<a id="references"></a>
## References
1. [Spoken Tutorial Page][1]
2. [Help for matplotlib][2]
3. [Example plots][3]

[1]: https://spoken-tutorial.org/tutorial-search/?search_foss=Python%203.4.3&search_language=English&page=1
[2]: matplotlib.sourceforge.net/contents.html
[3]: matplotlib.sourceforge.net/users/screenshots.html


