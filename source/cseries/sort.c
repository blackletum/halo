/*
SORT.C

symbols in this file:
00080360 0060:
	_code_00080360 (0000)
000803C0 0050:
	_code_000803c0 (0000)
00080410 0150:
	_qsort_2byte (0000)
00080560 0140:
	_qsort_4byte (0000)
*/

/* ---------- headers */

#include "cseries.h"

/* ---------- constants */

enum
{
	CUTOFF = 8, /* from the CRT qsort.c */
};

/* ---------- macros */

/* ---------- structures */

typedef boolean (*compare_function_2byte)(short, short);
typedef boolean (*compare_function_4byte)(long, long);

/* ---------- prototypes */

static void shortsort_2byte(char *lo, char *hi, compare_function_2byte compare);
static void shortsort_4byte(char *lo, char *hi, compare_function_4byte compare);

/* ---------- globals */

/* ---------- public code */

void qsort_2byte(
	void *base,
	unsigned long num,
	compare_function_2byte compare)
{
	char *lo, *hi;
	char *mid;
	char *loguy, *higuy;
	unsigned long size;
	char *lostk[30], *histk[30];
	long stkptr;
	short swap_space;

	if (num < 2)
	{
		return;
	}

	stkptr = 0;

	lo = base;
	hi = (char *)base + sizeof(short) * (num - 1);

recurse:

	size = ((short *)hi - (short *)lo) + 1;

	if (size <= CUTOFF)
	{
		shortsort_2byte(lo, hi, compare);
	}
	else
	{
		mid = lo + (size / 2) * sizeof(short);
		swap_space = *(short *)mid; *(short *)mid = *(short *)lo; *(short *)lo = swap_space;

		loguy = lo;
		higuy = hi + sizeof(short);

		for (;;)
		{
			do
			{
				loguy += sizeof(short);
			} while (loguy <= hi && !compare(*(short *)loguy, *(short *)lo));

			do
			{
				higuy -= sizeof(short);
			} while (higuy > lo && compare(*(short *)higuy, *(short *)lo));

			if (higuy < loguy)
			{
				break;
			}

			swap_space = *(short *)loguy; *(short *)loguy = *(short *)higuy; *(short *)higuy = swap_space;
		}

		swap_space = *(short *)lo; *(short *)lo = *(short *)higuy; *(short *)higuy = swap_space;

		if (higuy - 1 - lo >= hi - loguy)
		{
			if (lo + sizeof(short) < higuy)
			{
				lostk[stkptr] = lo;
				histk[stkptr] = higuy - sizeof(short);
				++stkptr;
			}

			if (loguy < hi)
			{
				lo = loguy;
				goto recurse;
			}
		}
		else
		{
			if (loguy < hi)
			{
				lostk[stkptr] = loguy;
				histk[stkptr] = hi;
				++stkptr;
			}

			if (lo + sizeof(short) < higuy)
			{
				hi = higuy - sizeof(short);
				goto recurse;
			}
		}
	}

	--stkptr;

	if (stkptr >= 0)
	{
		lo = lostk[stkptr];
		hi = histk[stkptr];
		goto recurse;
	}

	return;
}

void qsort_4byte(
	void *base,
	unsigned long num,
	compare_function_4byte compare)
{
	char *lo, *hi;
	char *mid;
	char *loguy, *higuy;
	unsigned long size;
	char *lostk[30], *histk[30];
	long stkptr;
	long swap_space;

	if (num < 2)
	{
		return;
	}

	stkptr = 0;

	lo = base;
	hi = (char *)base + sizeof(long) * (num - 1);

recurse:

	size = ((long *)hi - (long *)lo) + 1;

	if (size <= CUTOFF)
	{
		shortsort_4byte(lo, hi, compare);
	}
	else
	{
		mid = lo + (size / 2) * sizeof(long);
		swap_space = *(long *)mid; *(long *)mid = *(long *)lo; *(long *)lo = swap_space;

		loguy = lo;
		higuy = hi + sizeof(long);

		for (;;)
		{
			do
			{
				loguy += sizeof(long);
			} while (loguy <= hi && !compare(*(long *)loguy, *(long *)lo));

			do
			{
				higuy -= sizeof(long);
			} while (higuy > lo && compare(*(long *)higuy, *(long *)lo));

			if (higuy < loguy)
			{
				break;
			}

			swap_space = *(long *)loguy; *(long *)loguy = *(long *)higuy; *(long *)higuy = swap_space;
		}

		swap_space = *(long *)lo; *(long *)lo = *(long *)higuy; *(long *)higuy = swap_space;

		if (higuy - 1 - lo >= hi - loguy)
		{
			if (lo + sizeof(long) < higuy)
			{
				lostk[stkptr] = lo;
				histk[stkptr] = higuy - sizeof(long);
				++stkptr;
			}

			if (loguy < hi)
			{
				lo = loguy;
				goto recurse;
			}
		}
		else
		{
			if (loguy < hi)
			{
				lostk[stkptr] = loguy;
				histk[stkptr] = hi;
				++stkptr;
			}

			if (lo + sizeof(long) < higuy)
			{
				hi = higuy - sizeof(long);
				goto recurse;
			}
		}
	}

	--stkptr;

	if (stkptr >= 0)
	{
		lo = lostk[stkptr];
		hi = histk[stkptr];
		goto recurse;
	}

	return;
}

/* ---------- private code */

static void shortsort_2byte(
	char *lo,
	char *hi,
	compare_function_2byte compare)
{
	char *p, *max;
	short swap_space;

	while (hi > lo)
	{
		max = lo;

		for (p = lo + sizeof(short); p <= hi; p += sizeof(short))
		{
			if (compare(*(short *)p, *(short *)max))
			{
				max = p;
			}
		}

		swap_space = *(short *)max; *(short *)max = *(short *)hi; *(short *)hi = swap_space;
		hi -= sizeof(short);
	}

	return;
}

static void shortsort_4byte(
	char *lo,
	char *hi,
	compare_function_4byte compare)
{
	char *p, *max;
	long swap_space;

	while (hi > lo)
	{
		max = lo;

		for (p = lo + sizeof(long); p <= hi; p += sizeof(long))
		{
			if (compare(*(long *)p, *(long *)max))
			{
				max = p;
			}
		}

		swap_space = *(long *)max; *(long *)max = *(long *)hi; *(long *)hi = swap_space;
		hi -= sizeof(long);
	}

	return;
}
