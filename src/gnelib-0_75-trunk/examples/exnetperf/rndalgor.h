/*
** Last Modified: Mar-8-2000
** This was taken mostly unmodified from the SNIPPETS collection at the
** address:
** http://www.strangecreations.com/library/snippets/index.htm
** minus the main() function provided to test the RNG, for use in
** Jason Winnebeck's jrnd library, provided at
** http://www.rit.edu/~jpw9607/
** Added things for compatabilty with the include
*/

/* +++Date last modified: 02-Nov-1995 */

/*
**  longrand() -- generate 2**31-2 random numbers
**
**  public domain by Ray Gardner
** 
**  based on "Random Number Generators: Good Ones Are Hard to Find",
**  S.K. Park and K.W. Miller, Communications of the ACM 31:10 (Oct 1988),
**  and "Two Fast Implementations of the 'Minimal Standard' Random
**  Number Generator", David G. Carta, Comm. ACM 33, 1 (Jan 1990), p. 87-88
**
**  linear congruential generator f(z) = 16807 z mod (2 ** 31 - 1)
**
**  uses L. Schrage's method to avoid overflow problems
*/

#define a 16807         /* multiplier */
#define m 2147483647L   /* 2**31 - 1 */
#define q 127773L       /* m div a */
#define r 2836          /* m mod a */

long nextlongrand(long seed)
{
      unsigned long lo, hi;

      lo = a * (long)(seed & 0xFFFF);
      hi = a * (long)((unsigned long)seed >> 16);
      lo += (hi & 0x7FFF) << 16;
      if (lo > m)
      {
            lo &= m;
            ++lo;
      }
      lo += hi >> 15;
      if (lo > m)
      {
            lo &= m;
            ++lo;
      }
      return (long)lo;
}

static long randomnum = 1;

long longrand(void)                     /* return next random long */
{
      randomnum = nextlongrand(randomnum);
      return randomnum;
}

void slongrand(unsigned long seed)      /* to seed it */
{
      randomnum = seed ? (seed & m) : 1;  /* nonzero seed */
}

/*Following lines added by Jason Winnebeck to stop conflicts*/
#undef a
#undef m
#undef q
#undef r
