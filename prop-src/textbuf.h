///////////////////////////////////////////////////////////////////////////////
//
//  Text buffer class
//
///////////////////////////////////////////////////////////////////////////////

#ifndef text_buffer_h
#define text_buffer_h

#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
//
//  Text buffer represents a simple open-ended insertion only buffer,
//  sort of like a light weight std::ostrstream.
//
///////////////////////////////////////////////////////////////////////////////

class TextBuffer
{
protected:

  char * buffer;         // storage to buffer
  char * limit;          // limit of buffer
  char * cursor;         // cursor to next insertion point

  void grow (size_t);    // expand buffer

public:

  TextBuffer();
  TextBuffer( const TextBuffer&); // transfer to another buffer
  ~TextBuffer();

  void operator = ( const TextBuffer&); // transfer to another buffer
  void emit ( const char *, long = -1);
  void emit ( char);
  inline const char * text() const
  {
    return buffer;
  }
  inline size_t length() const
  {
    return cursor - buffer;
  }
  inline void reset()
  {
    cursor = buffer;
  }
};

#endif
