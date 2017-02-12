// Defines all constants for HyperDoom.
// Constants are not bound by namespace hd. Instead, they all start with HD_ prefixes.

#ifndef _CONST_H_
#define _CONST_H_

#pragma once

// The error bound for comparing floating point numericals, i.e. numericals within this
// error bound are considered equal.
#define HD_EPSILON (1e-6)
// A finer error bound for comparing values with zeros. i.e. numericals with absolute value
// less than this constant will be considered zero.
#define HD_EPSILON_TINY (1e-9)
// Represents invalid id. Note that ids are mostly represented as unsigned ints and longs,
// therefore this value should usually be converted to very large numbers (2^32-1 or 2^64-1),
// which is rarely reached and thus serve as an invalid id.
#define HD_INVALID_ID (-1)

#endif // _CONST_H_