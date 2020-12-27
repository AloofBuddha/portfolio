# Summary

This file solves a popular programming interview problem: given a string, return a list of all permutations of that string. I solved this in Haskell as there turns out to be a nice recursive algorithm for accomplishing this, and this can be written as a pure function in Haskell that simply takes in an input, performs some transformations on it, and returns some output, without invoking any IO or other side-effects. I find this pure style of functional programming to be a very methodical way to solve algorithms problems. Although Haskell is rarely seen in game development I wanted to illustrate the breadth of my programming knowledge, including 'higher level' languages. 

# Source

Github Gist (https://gist.github.com/kaizerroll/0ed5173e56d417d0932e#file-permutations-hs)

# File strucure

- permutations.hs - A single file that defines a main function which simply prints the output of 3 example lists to run the perms function on. It is easiewr to break this down by function

- spread - spread is a function that takes an element and a list, and 'spreads' that element into all possible places in the list, returning a list of lists. So for example:
```haskell
spread 1 [2,3] -- evaluates to [[1,2,3], [2,1,3], [2,3,1]]
```

- perms - perms can best be seen by example
```haskell
perms [1,2,3] -- evaluates to =>
concatMap (spread 1) (perms [2,3]) -- evaluates to =>
concatMap (spread 1) (concatMap (spread 2) (perms [3])) -- evaluates to =>
concatMap (spread 1) (concatMap (spread 2) (concatMap (spread 3) (perms []))) -- evaluates to =>
concatMap (spread 1) (concatMap (spread 2) (concatMap (spread 3) [[]])) -- evaluates to =>
concatMap (spread 1) (concatMap (spread 2) [3]) -- evaluates to =>
concatMap (spread 1) [[2,3], [3,2]] -- evaluates to =>
[[1,2,3], [2,1,3], [2,3,1], [1,3,2], [3,1,2], [3,2,1]]
```

- perms' and perms'' - two alternate writings of perms that utilize the fact that concatMap is the definition of `>>=` or 'bind' for the List Monad


# Output

See output in the console by running this file using a Haskell REPL, as can be found [here](https://repl.it/)

