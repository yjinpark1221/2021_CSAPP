/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */
//bit and, getbyte,bitcount add

#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  int result = ~(~x | ~y);
  return result;
}
// De Morgan's laws
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    int result = ~(x & y) & ~(~x & ~y);
  return result;
}
// De Morgan's laws + xor
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
// tmin() == 0b10000000000000000000000000000000 == 0x80000000
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return ((x ^ (x + 1)) >> 31) & 1 & !(x >> 31);
}
// x가 tmax인 경우에는 x + 1에서 overflow가 일어나 부호(msb)가 반대가 된다.
// -> ((x ^ (x + 1)) >> 31)
// x가 -1인 경우에도 x + 1과 msb가 반대가 되므로 이 경우를 제외하기 위해
// x의 msb가 0임을 확인하기 위해 !(x >> 31)을 & 해주었다. 
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int cmp = (0x55 << 24) | (0x55 << 16) | (0x55 << 8) | 0x55; 
    // cmp == 0b01010101010101010101010101010101 == 0x55555555
    int result = !~(~cmp | x);
    // (odd bits) cmp의 bit가 1인 경우는 x의 bit가 1이어야 하고 
    // (even bits)cmp의 bit가 0인 경우는 x의 bit가 상관 없다. 
    // ~cmp | x 의 결과가 
    // 0xffffffff일 때 return 1, 아닐 때는 return 0을 하기 위해
    // !~을 취해주었다.
  return result;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    int result = ~x + 1;
  return result;
}
// two's complement
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
     int result = (x >> (n << 3)) & 0xFF;
  return result;
}
// 8 * n bit만큼 right shift하면 마지막 8 bit에 return 할 값이 나온다.
// 앞에 24bit를 지워야하므로 & 0xFF를 통해 마지막 8 bit를 구해준다.
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  return 2;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int result = ((~!!x + 1) & y) | ((~!x + 1) & z);
  return result;
}
// x != 0인 경우 (0xffffffff & y) | (0x00000000 & z) 를 통해 y를 return 
// x == 0인 경우 (0x00000000 & y) | (0xffffffff & z) 를 통해 z를 return
// 0x00000000는 0xffffffff에서 +1을 하면 오버플로우를 통해 얻을 수 있다. 
// x != 0을 0과 1로 바꾸기 위해 !!x를 해주었고 x == 0을 0과 1로 바꾸기 위해 !x를 해주었다.
//
// x == 0인 경우
// ~!!x == 0xffffffff 이므로 ~!!x + 1 == 0x00000000이다.
// ~!x == 0xfffffffe이므로 ~!x + 1 == 0xffffffff이다.
// x != 0인 경우
// ~!!x == 0xfffffffe 이므로 ~!!x + 1 == 0xffffffff이다.
// ~!x == 0xffffffff이므로 ~!x + 1 == 0x00000000이다.
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  return 2;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;
  // x 에 1이 있으면 x의 lsb가 1이 되므로 x에 ~을 취한 후 마지막 bit만 리턴해주면 된다.
  return ~x & 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 2;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int r = 0x11 | (0x11 << 8) | (0x11 << 16) | (0x11 << 24);
  // r == 0x11111111
  int cnt = (r & x) + (r & (x >> 1)) + (r & (x >> 2)) + (r & (x >> 3));
  // 각 16진수 별로 1의 개수를 저장한다.
  cnt = (cnt >> 16) + (cnt & 0xffff);
  cnt = (cnt & 0xf) + ((cnt >> 4) & 0xf) + ((cnt >> 8) & 0xf) + ((cnt >> 12) & 0xf);
  // 8개의 16진수를 합치는 과정이다.
  return cnt;
}
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}

// int bitCount(int x) {
//   int cnt = x & 1;
//   cnt += (x >> 1) & 1;
//   cnt += (x >> 2) & 1;
//   cnt += (x >> 3) & 1;
//   cnt += (x >> 4) & 1;
//   cnt += (x >> 5) & 1;
//   cnt += (x >> 6) & 1;
//   cnt += (x >> 7) & 1;
//   cnt += (x >> 8) & 1;
//   cnt += (x >> 9) & 1;
//   cnt += (x >> 10) & 1;
//   cnt += (x >> 11) & 1;
//   cnt += (x >> 12) & 1;
//   cnt += (x >> 13) & 1;
//   cnt += (x >> 14) & 1;
//   cnt += (x >> 15) & 1;
//   cnt += (x >> 16) & 1;
//   cnt += (x >> 17) & 1;
//   cnt += (x >> 18) & 1;
//   cnt += (x >> 19) & 1;
//   cnt += (x >> 20) & 1;
//   cnt += (x >> 21) & 1;
//   cnt += (x >> 22) & 1;
//   cnt += (x >> 23) & 1;
//   cnt += (x >> 24) & 1;
//   cnt += (x >> 25) & 1;
//   cnt += (x >> 26) & 1;
//   cnt += (x >> 27) & 1;
//   cnt += (x >> 28) & 1;
//   cnt += (x >> 29) & 1;
//   cnt += (x >> 30) & 1;
//   cnt += (x >> 31) & 1;
//   return cnt;
// }