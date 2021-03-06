# Calculator

*1 Overview

In this project I implement two calculators in C++, mainly including the knowledge of class encapsulation, inheritance, derivation, operator overload and the implementation of stack. I also use QT Creator to simulate the graphical interface of the calculator which includes the buttons of addition, subtraction, multiplication and division, parentheses, equal sign and 10 digital buttons as well a clear button to clear the contents on the display.

*2 Polynomials Math Calculator

I implement a polynomials math calculator included in the file "Poly_Cal". This calculator is able to conduct the addition, subtraction, and multiplication of any polynomials. 

Here is an example:
input an arbitrary polynomial and click "=":
![](https://github.com/Link199711/Calculator/raw/master/pic/input1.png)
we get the result:
![](https://github.com/Link199711/Calculator/raw/master/pic/output1.png)


It can also derivative any polynomial and show the result.

*3 Arithmetic expression calculator

I implement a arithmetic expression calculator in the file "Arith_Cal". This calculator allows us to calculate the value of any arithmetic expression that only contains addition, subtraction, multiplication, paretheses and arbitrary integers. The implementation mechanism behind it is Inverse Polish Algorithm, which transforms infix expressions into suffix expression through two stacks (which are realized by myself) to calculate the value in an easier way.

Here is an example:
![](https://github.com/Link199711/Calculator/raw/master/pic/result.png)
