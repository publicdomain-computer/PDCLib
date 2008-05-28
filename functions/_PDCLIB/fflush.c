/* $Id$ */

/* _PDCLIB_fflush( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

int _PDCLIB_fflush( struct _PDCLIB_file_t * stream )
{
    if ( fwrite( stream->buffer, stream->bufidx, 1, stream ) == stream->bufidx )
    {
        stream->bufidx = 0;
        return 0;
    }
    else
    {
        stream->status |= _PDCLIB_ERRORFLAG;
        return EOF;
    }
}
                
#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
