# Challenge 1 : A gradient method for the minimization of a multivariate function.

This repo contains the work done by Nils Malmberg for the first challenge of the course of Advanced Programming for Scientific Compution (C++) followed at Politecnico di Milano during the academic year 2023-2024.

## Some context :
We consider a function that has a minimum that we want to find. A common method is to use the gradient method. Given an initial guess x(0) of the minimum of the function, we need to do x(k+1) = x(k) - a(k)grad(f(x(k)) where a(k) is defined by several methods (exponential decay, inverse decay, approximate line search).

## Main goals :
We need to :
- write a function that takes in input two function wrappers that define f, grad(f), initial conditions, tolerances, a(0), maximal number of iterations and all other needed parameters, and returns the computed minimum -> done.
- Implement the Armijo rule (used for the approximate line search method) -> done.
- Use a git repo, add a README.md file, create a Makefile, comment the code and prepare a test case -> done.

## Additional goals :
We can :
- Give the user the choice of the method use and so add other methods to the code -> done.
- Write a function that computes the gradient by finite differences and let the user choose between this one instead of the exact gradient -> done.
- Try to define the function and the derivatives using muParser.
- Try to implement other scheme as momentum or heavy-ball methods...

## Structure of the project :
The starting point is a JSON file called "parameters.json", which contains the parameters used during the computation. The parameters "alpha0" and "mu" are those used in the learning rate calculation (see doc/Challenge23-24-1.pdf). "lTol" and "rTol" refer respectively to the tolerances used when controlling step length and residual. "methodLearningRate" is defined as an integer which can take the values 0, 1 or 2 and refers to the method used to calculate the learning rate (0=exponential decay, 1=inverse decay, 2=line search with Armijo's rule). "methodGradient" is used to choose a method to compute the gradient (0= the user define the gradient in the main, 1= the gradient is compute using finite differences).


## Test case :
We consider the function f(x,y) = x * y + 4 * x^4 + y^2 + 3*x , where (x,y) are real numbers.

The gradient of f is defined by grad(f)=(y + 16 * x^3 + 3 , x + 2 * y)

With alpha0=0.2 ; mu=0.2 ; maxIter=1e+5 ; lTol=1e-6 ; rTol=1e-6 ; initialConditions=[0.0 , 0.0] ; methodLearningRate=2.

We obtain, min{x y + 4 x^4 + y^2 + 3 x} ~ -1.37233 at (x, y)~(-0.590551, 0.295272)

To compare, by using wolframalpha, min{x y + 4 x^4 + y^2 + 3 x} ~ -1.37233 at (x, y)~(-0.590551, 0.295275)

(https://www.wolframalpha.com/input?i=minimize+x+*+y+%2B+4+*+x%5E4+%2B+y%5E2+%2B+3+*+x+)
