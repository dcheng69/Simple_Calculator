# Simple_Calculator

# Objective

The design process for creating a human computer interface will always proceed from informal requirements specifications, to implemented physical executable systems, in this project we will explore these transformation by following a classical pathway from requirements to implementation and testing.

We will focus on the key-press based user interfaces, with simple text-based output displays representing the digits corresponding to the input and output numbers.

We will be considering the design of three versions of simple calculators:

1. A **simple** 4-function calculator, which has buttons 0~9 and the function buttons {'+', '-', 'x', '/', '='}. This calculator will receive inputs from the user in normal "INFIX" mode, but without any operator precedence. 

   Given the following sequence of inputs {'5', '+', '3', 'x', '2', '='} the user will see '5', '3', '8', '2', and then the answer should be '16', not '11'.

2. A **simple** 4-function calculator, which operates in "RPN" mode. It has buttons 0~9, and the function buttons {'+', '-', 'x', '/'}, but instead of '=' it has an {'enter'} key.

   In this mode, the same calculator would be {'5', 'enter', '3', '+', '2', 'x'}, and the answer is '16'.

   

**Note:**

​	This project will serve as an introduction to the steps needed to proceed through all stages of the Requirements, Analysis, Design, Implementation and Testing phases. Thus, in order to simplify this process, no need to implement '**divide by zero**' error checking, nor any functionality for **entering negative numbers.** 