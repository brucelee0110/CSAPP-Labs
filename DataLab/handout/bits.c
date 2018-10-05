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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int shift_bits = n << 3;
  int shifted = x >> shift_bits;
  int result = (shifted & 255);
 /* printf("%i   %x\n",n,x);
  printf("%i   %x\n",shift_bits,shifted);
  printf("final result:  %x \n",result);
  */
  return result;

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  // shift bits except the sign bit
  int musking = ~(1<<31); // get 0x01111111
  int shifted = (musking & x) >> n;
  // shift the sign bit
  int sign_bit = (x >> 31) & 1;
  int sign_shift = 32 + (~n);
  int shifted_sign = sign_bit << sign_shift; 
  /*printf("%x    %i\n",x,n);
  printf("shifted: %x\n",shifted);
  printf("shifted_sign: %x\n",shifted_sign);
  printf("sign_shift: %i  sign_bit: %x\n",sign_shift,sign_bit);
  */
  return shifted + shifted_sign;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    // musk with 0101 to sum 1 bit number
    int musk_pattern1 = (85 << 8) + 85;
    int musk_2bits = (musk_pattern1 << 16) +musk_pattern1;
    int x_2bits0 = x & musk_2bits;
    int x_2bits1 = (x >> 1) & musk_2bits;
    int x_2bits = x_2bits0 + x_2bits1;
    // musk with 0011 to sum 2 bit number
    int musk_pattern2 = (51 << 8) + 51;
    int musk_4bits =( musk_pattern2 << 16) + musk_pattern2;
    int x_4bits0 = x_2bits & musk_4bits;
    int x_4bits1 = (x_2bits >> 2) & musk_4bits;
    int x_4bits = x_4bits0 + x_4bits1;
    // musk with 00001111 to sum 4 bit number
    int musk_pattern3 = (15 << 8) + 15;
    int musk_8bits = (musk_pattern3 << 16) + musk_pattern3;
    int x_8bits0 = x_4bits & musk_8bits;
    int x_8bits1 = (x_4bits >> 4) & musk_8bits;
    int x_8bits = x_8bits0 + x_8bits1;
    // musk with 000000011111111 to sum 8 bit number
    int musk_pattern4 = (0<<8) + 255;
    int musk_16bits = (musk_pattern4 << 16) + musk_pattern4;
    int x_16bits0 = x_8bits & musk_16bits;
    int x_16bits1 = (x_8bits >> 8) & musk_16bits;
    int x_16bits = x_16bits0 + x_16bits1;
    // sum it up
    int result =((x_16bits << 16) >> 16) + (x_16bits >> 16);
    /*
    printf("x: %x\n",x);
    printf("musk bit 1 : %x\n",musk_2bits);
    printf("%x\n%x\n%x\n%x\n%i\n",x_2bits,x_4bits,x_8bits,x_16bits,result);
    */
    return result;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    // if there is 1, least significant bit will be 1
    int x1 = (x >> 1) | x; //find 1 every 2 bits
    int x2 = (x1>>2) | x1;
    int x3 = (x2>>4) | x2;
    int x4 = (x3>>8) | x3;
    int x5 = (x4>>16)| x4;
    int result = (x5^1) & 1; 
    return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    // all the bits except the last n bit matters
    int shift_bits = 33 + (~n);
    int x_nbit = (x << shift_bits) >> shift_bits;
    // compare after extend and truncate one with x
    int equal = x ^ x_nbit;
    int result = !equal;
    return result;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int sign = !(!(x>>31));
    int bias = (1 << n) + (~0);
    int x_modified = x + (bias<<sign) + 1 + (~bias);
    int result = x_modified >> n;
    /*
    printf("x: %i\n",x);
    printf("sign: %i\n",sign);
    */
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
  return 1+(~x);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    int zero = !x;
    int z = x + 1 + (~zero); //except 0 case
    return !(z>>31);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // x>=0 y<0 always 0, no matter overflow
    int x_bzero = !(x>>31); 
    int y_szero = !((y>>31)+1); 
    int case_false =x_bzero & y_szero;
    // x<0 y>=0 always 1, no matter overflow
    int case_true = (!x_bzero) & (!y_szero);
    int z = y+1+(~x);
    int raw_num  = z>>31;
    int compare_zero = raw_num + case_true +1 +(~case_false);
    //add case true to raw and minus case false to raw, then >=0 result in 1, <0 result in 0
    int result = !(compare_zero >> 31);
    /*
    printf("X: %i,Y: %i\n",x,y);
    printf("case_false: %i  case_true: %i \n",case_false,case_true);
    printf("compare zero: %x\n",compare_zero);
    */
    return result;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    /*
    Count the first n bits.
    if it has one, add n to result and >> n.
    In this case, start with 16 8 4 2 1.
    */
    // Check first 16 bits
    int musk0 = ((255<<8)+255)<<16; //0xFFFF0000
    int num0 = musk0 & x;
    int b0 =!(!num0);
    int x_16bits = x & (~musk0); // remaining 16 bits
    // Add Up:
    // If larger than 16 bits, discard rest
    // Else add rest for further process
    int x0 = (num0>>16) + (x_16bits << (!num0)) + 1 +(~x_16bits);
    // Check first 8 bits
    int musk1 = 255 << 8; //FF00
    int num1 = musk1 & x0;
    int b1 =!(!num1);
    int x_8bits = x0 & (~musk1); //remaining 8 bits
    int x1 = ((num1>>8)&255) + (x_8bits << (!num1)) +1 +(~x_8bits);
    // Check first 4 bits
    int musk2 = 240; //F0
    int num2 = musk2 & x1;
    int b2 =!(!num2);
    int x_4bits = x1 & (~musk2);
    int x2 =((num2>>4)&15) +(x_4bits<<(!num2)) +1 +(~x_4bits);
    // Check first 2 bits
    int musk3 = 12; //1100
    int num3 = musk3 & x2;
    int b3 = !(!num3);
    int x_2bits = x2 & (~musk3);
    int x3 = ((num3>>2)&3) +(x_2bits<<(!num3)) +1 +(~x_2bits);
    // Check first 1 bits
    int musk4 =2;// 10
    int num4 = musk4 & x3;
    int b4 = !(!num4);
    int result= (b0<<4) +(b1<<3) +(b2<<2) +(b3<<1)+b4;
    /*
    printf("x: %x\n",x);
    printf("musk0: %x\n",musk0);
    printf("num0: %x   x0: %x\n",b0<<4,x0);
    printf("num1: %x   x1: %x\n",!(!num1)<<3,x1);
    printf("num2: %x   x2: %x\n",!(!num2)<<2,x2);
    printf("num3: %x   x3: %x\n",!(!num3)<<1,x3);
    printf("num4: %x   \n",num4);
    printf("x_2bits:  %x\n",x_2bits);
    */
    return result;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned frac = uf << 9;
    unsigned exp =  uf >> 23;
    unsigned nan = (~exp & 0x000000FF) | (!frac);
    //printf("Frac: %x  Exp: %x \n",frac,exp);
    if (!nan) {
        return uf;
    }else{
        return uf + (1<<31);
    }
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = !(x & 0x80000000);
    int number;
    int exp_num;
    unsigned exp;
    unsigned dropped;
    unsigned frac;
    unsigned result;
    int shift_bits;
    int i;
    // positive or negative number
    if (sign){// positive number
        number = x;
        if (!number){// number = 0 
            return 0x0;     
        }
    }else{// negative number
        number = 1+(~x);
        if (!(number<<1)){ // Tmin 
            return 0xCF000000;    
        }
    }
    // get shift bits
        for(i=0;!(0x80000000&number);i++){
        number = number<<1;
        shift_bits = i;
    }
    // Get frac and exp field
    exp_num = 158 +(~shift_bits);
    exp = exp_num << 23;
    // do the rounding for Frac Field
    dropped = (number>>8 & 0x007FFFFF); // drop the first 1
    // match only one bit a time
    if ( number & 0x80){// .X = .1
        if (number& 0x7f){// .XY = .1xxx1
            frac = dropped+1;
        }else{ // .XY = .10
            if (number&0x100){// Z.XY = 1.10
                frac = dropped +1;
            }else{ // Z.XY = 0.10
                frac = dropped;
            }
        }
    } else{// .X = .0
        frac = dropped;
    }
    result = ((!sign)<<31) + exp + frac;
    /*printf("dropped: %x\n",dropped);
    printf("exp: %x  frac: %x \n",exp,frac);
    */
    return result;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned frac_old = uf & 0x7FFFFF;
    unsigned exp_old = uf & 0x7F800000;
    unsigned exp_ones = !(~exp_old & 0x7F800000);
    unsigned nan = exp_ones && frac_old;
    unsigned infinity = exp_ones && (!frac_old);
    unsigned frac;
    unsigned exp;
    if ( nan || infinity ){ // NaN or Infinity case
        return uf;    
    }
    // denormalize case
    if (!exp_old){
        // check wether overflow
        if ( frac_old & 0x400000 ){ // rep in normalize
            exp = 0x800000;
            frac = (frac_old << 1) & 0x7FFFFF;
        }else{ // denorm shift
            exp = exp_old;
            frac = frac_old <<1;
        }
    }else{ // normalize case
        exp =exp_old + 0x800000;
        frac = frac_old;
    }
    return sign+exp+frac;
}
/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 */
