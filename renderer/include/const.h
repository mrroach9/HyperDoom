// Defines all constants for HyperDoom.
// Constants are not bound by namespace hd. Instead, they all start with HD_ prefixes.

#ifndef _CONST_H_
#define _CONST_H_

#pragma once

// The error bound for comparing floating point numericals, i.e. numericals within this
// error bound are considered equal.
#define HD_EPSILON 1e-6
// A finer error bound for comparing values with zeros. i.e. numericals with absolute value
// less than this constant will be considered zero.
#define HD_EPSILON_TINY 1e-9

#endif // _CONST_H_