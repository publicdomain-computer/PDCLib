// ----------------------------------------------------------------------------
// $Id$
// ----------------------------------------------------------------------------
// Public Domain C Library - http://pdclib.sourceforge.net
// This code is Public Domain. Use, modify, and redistribute at will.
// ----------------------------------------------------------------------------
// Personality #define's (see personality.txt)
// ----------------------------------------------------------------------------

#ifndef __PDCLIB_PERSONALITY_H
#define __PDCLIB_PERSONALITY_H __PDCLIB_PERSONALITY_H

// This structure is required by time.h and wchar.h.
struct tm;

// This type is required by wchar.h and wctype.h.
typedef wint_t;

// #undef this if environment does not support _Imaginary.
#define __PERSONALITY_SUPPORTS_IMAGINARY

#endif // __PDCLIB_PERSONALITY_H
