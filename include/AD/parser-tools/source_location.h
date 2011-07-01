///////////////////////////////////////////////////////////////////////////////
//
//  Source code location
//
///////////////////////////////////////////////////////////////////////////////

#ifndef parser_tools_source_location_h
#define parser_tools_source_location_h
#include <iostream.h>
#include <AD/strings/quark.h>

class SourceLocation
{
public:
  typedef unsigned long LineNumber;
  typedef Quark         FileName;
private:
  FileName   this_file;
  LineNumber this_line;
public:
  inline SourceLocation()
  {}
  inline SourceLocation(const SourceLocation& l)
      : this_file(l.this_file), this_line(l.this_file)
  {}
  inline SourceLocation(const char * f, LineNumber l)
      : this_file(f), this_line(l)
  {}
  inline SourceLocation(const FileName& f, LineNumber l)
      : this_file(f), this_line(l)
  {}

  inline void operator = (const SourceLocation& l)
  {
    this_file = l.this_file;
    this_line = l.this_line;
  }
  inline void operator = (const FileName& f)
  {
    this_file = f;
  }
  inline void operator = (LineNumber l)
  {
    this_line = l;
  }
  inline void operator ++ ()
  {
    this_line++;
  }
  inline void operator ++ (int)
  {
    this_line++;
  }
  inline void operator += (int l)
  {
    this_line += l;
  }

  inline const FileName& file () const
  {
    return this_file;
  }
  inline LineNumber      line () const
  {
    return this_line;
  }

  inline std::ostream& operator << (std::ostream& f) const
  {
    return f << ':' << l;
  }
};

#endif
