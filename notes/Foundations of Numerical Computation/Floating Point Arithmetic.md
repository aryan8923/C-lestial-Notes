Backlink: [notes](../notes.md)

Before we can work out the theory and algorithms for a problem, I feel that we should have some idea on how computers, the very tool of our trade, even process and work with numbers. A better understanding of your tool can go a long way in designing and choosing better algorithms for your problems (as we will learn later, choice of a method can influence the results of a numerical computation.)  So this chapter focuses on the machine side of numerical computation while from the next chapter we will focus on the mathematical and algorithmic side.  

**Note:** Even though we also have integer type of variables in computers, for numerical computations of quantities, you would mainly be working with floating types. 

**Tip**: I highly recommend at least skimming through the classic article on floating point arithmetic: *[What every computer scientist should know about floating-point arithmetic by Goldberg](https://dl.acm.org/doi/abs/10.1145/103162.103163)* . This chapter is basically notes of this article plus my own additions in explanations here and there. 

# Rounding Error

Here we will discuss what floating-point format is, what are the implications of using different rounding strategies for the basic operations $(+,-,\times, \div)$ and background on the 2 methods of measuring error, namely ulps and relative error. 


## Floating Point Formats

Floating point format is just a representation of real numbers. A computer has only a finite number of bits, but the real numbers contain infinitely many values. Therefore, a computer cannot represent every real number exactly and the result of a floating-point calculation often has to be rounded so that it fits into the finite representation available to the computer. This leads to rounding errors which is thus a characteristic feature of floating-point computation.

This section introduces the representation of real numbers in floating-point arithmetic. The subsequent sections study how errors arising from this representation are measured and controlled.

A floating-point representation is characterized by:

- a base, denoted by $\beta$, which is assumed to be even;
- a precision, denoted by $p$;
- a smallest allowable exponent, $e_{\min}$;
- a largest allowable exponent, $e_{\max}$.

Thus, the important parameters are $\boxed{\beta,\quad p,\quad e_{\min},\quad e_{\max}}$ with $\beta=10$ for decimal representation and $\beta=2$ for binary. 

**General form of a floating-point number**: $\boxed{\pm d_0.d_1d_2\cdots d_{p-1}\times\beta^e}$ where $0\leq d_i<\beta.$

Equivalently,
$$\boxed{
\pm
\left(
d_0+d_1\beta^{-1}+d_2\beta^{-2}
+\cdots+d_{p-1}\beta^{-(p-1)}
\right)\beta^e
}$$

with $0\leq d_i<\beta.$ The quantity $d_0.d_1d_2\cdots d_{p-1}$ is called the **significand** (older terms: fraction/mantissa). Precision $p$ specifies the number of digits in the significand.


**Example**: Say for a representation, $\beta=10,p=3$ then the real number $0.1$ is written as $1.00\times10^{-1}$ with base $=10$, precision $p=3$, significand $=1.00$, exponent $=-1$. But if base 2, then 0.1 has infinite binary representation and cannot be represented exactly using a finite number of binary digits. $0.1_{{10}} = 0.0001100110011001100110011\ldots_2$. Thus, a finite-precision binary floating-point system must approximate $0.1$. (Conversion to binary is discussed in the next subsection.)

**Normalisation**: Floating point representation of a real number is not unique so we normalise by keeping the leading digit $d_{0}$ to be non-zero.  $0.1$ can be represented as $0.01\times 10^1$ and $1.00 \times 10^{-1}$, but the latter form is the normalised form. Due to the leading 1 digit, a normalized representation cannot represent zero. So 0 is treated specially as $fl(0) = 1.0 \times \beta^{e_{\min}-1}$

**Note**: Many hardware floating point units use the IEEE-754 standard and in it the number of explicitly stored fraction bits is not the same as the effective precision because normalized binary numbers have an implicit leading $1$.

I will use the following example to illustrate how to convert a real number to binary format, but I will use the IEEE 754 standard to also show how the computer will store it. When 32 bits are used to store a float, it is called a single-precision float and when 64 bits are used to store a float, it is called a double-precision float. Out of the 32 bits, 1 is used for sign (0 for + and 1 for -), 8 for exponent and 23 for mantissa/fraction. Out of the 64 bits, 1 for sign, 11 for exponent and 52 bits for mantissa/fraction. 

**Note related to library:** C-lestial library module `defs.h` sets whether you wish to work with single or double precision floats by setting the line `#define PRECISION double` to set double precision and `#define PRECISION float` to set single precision. 

### Real Number to IEEE-754 Single Precision Conversion

So let's **convert 85.125 to IEEE-754 single precision**.

A decimal number can be separated into integer part + fractional part.  For the integer part, ordinary decimal-to-binary conversion can be used. So $(85)\_{10} = (1010101)\_{2}$ . For the fractional part, repeatedly multiply by 2 , take the bit appearing before the decimal point and continue with the remaining fractional part: 0.125 × 2 = 0.25 → 0 0.25 × 2 = 0.5 → 0 0.5 × 2 = 1.0 → 1 So $(0.125)\_{10} = (001)\_{2}$ .

Now combine the two parts: $1010101.001$ and note that the decimal needs to move 6 places left for it to be in normalised form. So, in normalised form: $(1.010101001)_{2} \times 2^6$ and hence the exponent is 6.

Since the leading 1 in normalised form becomes implicit, storing it becomes redundant and so the computer stores only the bits after the decimal. Note that since fraction 23 bits in single precision, we need to add the rest of the 0s. So finally, mantissa is stored as $010101001000\dots$ 

Now, the exponent is 6 but since 8 bits assigned to the exponent also needs to take into account negative exponents, the stored bits represent from -126 to 127. So 6 is represented by $127+6 = 133 = (10000101)_{2}$. This is how the exponent is stored in the computer. 

85.125 is a positive real number so the sign bit is 0.

**Final representation:** $0 \quad 10000101 \quad  010101001000\dots$

Without spaces: $010000101010101001000\dots$ or in hexadecimal: 0x42AA4000

### Real Numbers to Exactly Representable

There are two fundamental reasons behind why a real number might not be exactly representable.

1. The number requires infinitely many digits. For example 0.1 in binary requires infinite bits to store exactly. Fundamentally a precision/rounding issue.

2. The number is outside the representable range. Number is either too large ($|x|>\beta^{e_{\max}}$) or too small ($|x|<1.0\times\beta^{e_{\min}}.$).  A range issue and is treated later in the article.

The allowed exponents range from $e_{\min} \ \ \text{to} \ \  e_{\max}$. Therefore, there are $e_{\max}-e_{\min}+1$ possible exponent values. For each exponent, there are $\beta^p$ possible significands.

The number of bits needed to encode a floating-point number as

$$
\boxed{
\left\lceil
\log_2(e_{\max}-e_{\min}+1)
\right\rceil
+
\left\lceil
\log_2(\beta^p)
\right\rceil
+1
}
$$

where the final $+1$ represents the sign bit.

The exact encoding details are not important at this stage.
