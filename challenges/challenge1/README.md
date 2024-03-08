# Challenge 1 : A gradient method for the minimization of a multivariate function.

This repo contains the work done by Nils Malmberg for the first challenge of the course of Advanced Programming for Scientific Compution (C++) followed at Politecnico di Milano during the academic year 2023-2024.

## Some context :
We consider a function that has a minimum that we want to find. A common method is to use the gradient method. Given an initial guess x(0) of the minimum of the function, we need to do x(k+1) = x(k) - a(k)grad(f(x(k)) where a(k) is defined by several methods (exponential decay, inverse decay, approximate line search).

## Main goals :
We need to :
- write a function that takes in input two function wrappers that define f, grad(f), initial conditions, tolerances, a(0), maximal number of iterations and all other needed parameters, and returns the computed minimum.
- Implement the Armijo rule (used for the approximate line search method).
- Use a git repo, add a README.md file, create a Makefile, comment the code and prepare a test case.

## Additional goals :
We can :
- Give the user the choice of the method use and so add other methods to the code (don't use loops that are inefficient but a function template with an enumerator as template parameter and use if constepr).
- Write a function that computes the gradient by finite differences and let the user choose between this one instead of the exact gradient.
- Try to define the function and the derivatives using muParser.
- Try to implement other scheme as momentum or heavy-ball methods...

## The work done :
