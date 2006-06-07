/* $Id$ */

/* fclose( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

/* FIXME: Last file not removed from list. */
int fclose( struct _PDCLIB_file_t * stream )
{
    struct _PDCLIB_file_t * current = _PDCLIB_filelist;
    struct _PDCLIB_file_t * previous = NULL;
    /* Checking that the FILE handle is actually one we had opened before. */
    while ( current != NULL )
    {
        if ( stream == current )
        {
            if ( stream->status & _PDCLIB_WROTELAST ) fflush( stream );
            if ( stream->status & _PDCLIB_LIBBUFFER ) free( stream->buffer );
            _PDCLIB_close( stream->handle );
            if ( previous != NULL )
            {
                previous = current->next;
            }
            else
            {
                _PDCLIB_filelist = current->next;
            }
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* FIXME: This is basically fopen() checking. Flushing and buffer-freeing is not checked. */
    struct _PDCLIB_file_t * file1;
    struct _PDCLIB_file_t * file2;
    TESTCASE( _PDCLIB_filelist == NULL );
    TESTCASE( ( file1 = fopen( "testfile1", "w" ) ) != NULL );
    TESTCASE( _PDCLIB_filelist == file1 );
    TESTCASE( ( file2 = fopen( "testfile2", "w" ) ) != NULL );
    TESTCASE( _PDCLIB_filelist == file2 );
    TESTCASE( fclose( file2 ) == 0 );
    TESTCASE( _PDCLIB_filelist == file1 );
    TESTCASE( ( file2 = fopen( "testfile1", "w" ) ) != NULL );
    TESTCASE( _PDCLIB_filelist == file2 );
    TESTCASE( fclose( file1 ) == 0 );
    TESTCASE( _PDCLIB_filelist == file2 );
    TESTCASE( fclose( file2 ) == 0 );
    TESTCASE( _PDCLIB_filelist == NULL );
    system( "rm testfile1 testfile2" );
    return TEST_RESULTS;
}

#endif