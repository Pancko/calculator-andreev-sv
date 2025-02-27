
# calculator-andreev-sv

  

## Description

  

This project is a simple calculator program written in C. It reads an arithmetic expression from standard input, parses it, and prints the result. Program features and restrictions:

- Input passed through ```stdin```

- Output passed through ```stdout```

- Less than 1KiB of input data (else `UB` )

- End of input determined after reading `EOF`

- Only allowed charset [0-9()*+\\/\s-] (else return code not equal to `0` )

	- 0-9 matches a single character in the range between 0 (index 48) and 9 (index 57) (case sensitive)
	- ()\*+ matches a single character in the list ()*+ (case sensitive)

	- \\/ matches the character / with index 47<sub>10</sub> (2F<sub>16</sub> or 57<sub>8</sub>) literally (case sensitive)

	- \s matches any whitespace character (equivalent to [\r\n\t\f\v ] )

	-  \\- matches the character - with index 45<sub>10</sub> (2D<sub>16</sub> or 55<sub>8</sub>)  literally (case sensitive)

- Only correct arithmetic expression are allowed (else return code not equal to 0 )

- All numbers in a given expression are integers from a range [0...2*10<sup>9</sup>] (else `UB` )

- All intermediate results (for any allowed order of evaluation) are fit into range [-2\*10<sup>9</sup>...2*10<sup>9</sup>] (else `UB` )

- Supports flag `--float` that switch app calculations into real numbers mode

- In integer mode:

	- / return an integer part of an division (rounds towards 0)

	- Answer is given on a single line as an integer number (with - sign if negative)

- In real numbers mode

	- / return a fraction number

	- Answer is given on a single line as a real number (decimal notation) with an absolute accuracy +- 10 <sup>-4</sup>

- In any mode division on a number less than 10 <sup>-4</sup> are forbidden (else UB)

  

## Using the Program

  
To run the program in integer mode use
```bash 
make run-int
```
  
To run the program in real mode use
```bash 
make run-float
```

The program will prompt you to enter an arithmetic expression. After entering the expression, press `Enter` and then `Ctrl+D` to see the result.

  

## Into the code-verse (how does it work)
The program uses the concept of Reverse Polish Notation, including two stacks - `values` for numbers and `symbols` for arithmetic operations and round brackets. 

- The program(`main.c`) consists of 5 functions:

	1. `checkNumSize` - checking input integers and intermediate results for following the restrictions (described in `Description` part).
	2. `division` - handles the `/` operation for both real and integer modes, also checking for the second argument to be > |10<sup>-4</sup>|.
	3. `parser` - parses the string and filling the `values` and `symbols` stacks.
	4. `zzz` - main calculus function. It takes two numbers from `values` stack and uses next operation from `symbols`. It checks for brackets, operation order and applies different actions depending on it.
    5. `evaluate_brackets` - evaluates anything in the next brackets `()`

- `main()` covers everything else: 
	- reading from `stdin` and calling `parser`,
	-  checking for `--float` flag,
	- calling the `zzz` until `values` and `symbols` stacks are exhausted, resulting in an answer. 
