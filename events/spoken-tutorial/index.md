The Spoken Tutorial
=========================

## Index
1. [Requirements](#requirements)
1. [Plotting Charts](#plottingcharts)
1. [References](#references)


<a id="requirements"></a>
## Requirements

* Ubuntu 14.04
* Python 3.4.3
* iPython 5.1.0
* pip3 install matplotlib

<a id="plottingcharts"></a>
## 11. Plotting Charts

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
## 12. Getting started with lists

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


<a id="for-loop"></a>
## 13. Getting started with for

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
## 14. Getting started with strings

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
## 15. Getting started with files

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




 

<a id="references"></a>
## References
1. [Spoken Tutorial Page][1]
2. [Help for matplotlib][2]
3. [Example plots][3]

[1]: https://spoken-tutorial.org/tutorial-search/?search_foss=Python%203.4.3&search_language=English&page=1
[2]: matplotlib.sourceforge.net/contents.html
[3]: matplotlib.sourceforge.net/users/screenshots.html

