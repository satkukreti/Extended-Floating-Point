# Extended Floating Point

A text based application that creates a generalized floating point number capability. Can be considered an extension to the standard IEEE standard as my data type has a fractional and exponential portion. The goal of this project was to:

- Learn about IEEE floating point numbers
- Learn about manipulating bits ("bit twiddling") in C
- Understand number type conversions

## Introduction

Coding languages use the IEEE standard to represent floating point numbers in 32 bits worth of data. Some applications need the flexibility of floating point numbers, but may not need the full precision offered by the standard float or double implementations of floating point numbers. Or, applications may need higher precision and are willing to sacrifice the number of exponent bits to get higher precision.

This project implements a generalized floating point number capability; one which uses an arbitrary number of bits, `expBits`, to represent the exponent of a floating point number, and an arbitrary number of bits, `floatx`, to represent the fractional part of the number.

Other than changing the number of bits for the sub-fields, all the rest of the IEEE conventions for floating point numbers are followed.

For example, a floatx number with 12 total bits and 5 exponent bits would use the following bits in a long unsigned value:

<table>
<tr><td>63</td><td>...</td><td>12</td><td>11</td><td>10</td><td>9</td><td>8</td><td>7</td><td>6</td><td>5</td><td>4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr>
<tr><th colspan=3>Padding</th><th>S</th><th colspan=5>Exponent</th><th colspan=6>Fraction</th><tr>
</table>

## Makefile

Contains the following targets:

- `clean` Removes all the files Makefile can create
- `testFloatx` - creates the testFloatx executable from testFloatx.c, floatx.c.
- `gdb` - A target to run gdb on the testFloatx executable. This will automatically set a breakpoint at the first instruction in `doubleToFloatx`, and run with command line arguments 16 and 4.
- `test` - Runs testFloatx using some easy to debug formats such as 32 8 (for standard `float` format), 64 11 (for standard double format) and 16 4 which does not map to an existing floating point format. The conversion is run on all the numbers in test1.txt which contains several test cases that are useful for debugging.

## Runtime Example

Here is an example of the output:

```txt
>./testFloatx 32 8 <test1.txt
             1 = floatx(32,8) : 000000003f800000
           100 = floatx(32,8) : 0000000042c80000
     1.3333333 = floatx(32,8) : 000000003faaaaaa
   1.27563e+45 = floatx(32,8) : 000000007f800000
      6.23e+22 = floatx(32,8) : 00000000655314a2
       7.9e-39 = floatx(32,8) : 00000000005605fc
 3.4028235e+38 = floatx(32,8) : 000000007f7fffff
 3.4028236e+38 = floatx(32,8) : 000000007f7fffff
Input : q not recognized as a double...         quitting

```

## Credit

This was my favorite project in CS220. The credit for this idea goes to Professor Tom Bartenstein of Binghamton University. The implementation of the code was my own, aside from the starter code given.
