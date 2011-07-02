//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are free to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome any suggestions
// and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string>
#include <AD/automata/scanner.h>

/////////////////////////////////////////////////////////////////////////////
// Initialize the scanner
/////////////////////////////////////////////////////////////////////////////

void LexScanner::open()
{
  close();
  buffer          = limit = read_limit = cursor = tok = 0;
  len             = 0;
  anchored        = true;
  current_context = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Clean up after scanning
/////////////////////////////////////////////////////////////////////////////

void LexScanner::close()
{
  delete [] buffer;
  buffer = limit = read_limit = cursor = tok = 0;
  len = 0;
  save_char = -1;
}

/////////////////////////////////////////////////////////////////////////////
// Method to add new input to the buffer
//
// Precondition:
//   buffer < tok < cursor == read_limit < limit
//
/////////////////////////////////////////////////////////////////////////////

int LexScanner::fill_buffer( std::istream& stream, int read_size, LexScanner::Option option)
{
  int space_to_right = limit - read_limit;
  int space_to_left  = tok - buffer;

  if (read_size > space_to_right + space_to_left)
  {
    //
    //  Expand buffer if necessary
    //
    int chars_left    = read_limit - tok;
    int new_capacity  = chars_left + read_size;
    if (buffer == 0)
      new_capacity += new_capacity / 2;
    char * new_buffer = new char [new_capacity];
    if (buffer)
      memcpy(new_buffer,buffer,chars_left);
    delete [] buffer;
    buffer     = new_buffer;
    limit      = buffer + new_capacity;
    tok        = buffer;
    read_limit = cursor = buffer + chars_left;
  }
  else if (read_size > space_to_right)
  {
    //
    // Shift buffer if necessary
    //
    int chars_left = read_limit - tok;
    register char * p, * q, * r;
    for (p = buffer, q = tok, r = read_limit; q < r; )
      *p++ = *q++;
    tok = buffer;
    cursor = read_limit = buffer + chars_left;
  }

  //
  //  Read more stuff from stream
  //
  int bytes_read;
  if (option & Block_buffering)
  { // block buffering mode
    stream.read(read_limit,read_size - 1);
    bytes_read = stream.gcount();
    read_limit += bytes_read;
  }
  else
  { // line buffering mode
    stream.get(read_limit,read_size - 1);
    bytes_read = stream.gcount();
    read_limit += bytes_read;
    if (stream.peek() == '\n')
    {
      *read_limit++ = stream.get();
      bytes_read++;
    }
  }
  return bytes_read;
}

/////////////////////////////////////////////////////////////////////////////
//  Method for reporting errors
/////////////////////////////////////////////////////////////////////////////

void LexScanner::error( const char file_name[], int line_number)
{
  std::cerr << "Scanner error in file \"" << file_name << "\" at line " << line_number;
  if (cursor == read_limit)
  {
    std::cerr << "\nEnd of file encountered\n";
  }
  else
  {
    *read_limit = '\0';
    std::cerr << "\nJammed: remaining input: \"" << cursor << "\"\n";
  }
  exit(1);
}
