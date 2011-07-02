//////////////////////////////////////////////////////////////////////////////
// NOTICE:
//
// ADLib, Prop and their related set of tools and documentation are in the
// public domain.   The author(s) of this software reserve no copyrights on
// the source code and any code generated using the tools.  You are encouraged
// to use ADLib and Prop to develop software, in both academic and commercial
// settings, and are welcomed to incorporate any part of ADLib and Prop into
// your programs.
//
// Although you are under no obligation to do so, we strongly recommend that
// you give away all software developed using our tools.
//
// We also ask that credit be given to us when ADLib and/or Prop are used in
// your programs, and that this notice be preserved intact in all the source
// code.
//
// This software is still under development and we welcome(read crave for)
// any suggestions and help from the users.
//
// Allen Leung
// 1994
//////////////////////////////////////////////////////////////////////////////

#define PSTREAM_IMPLEMENTATION
#include <stdlib.h>
#include <string>
#include <iostream>
#include <AD/persist/ptype.h>     // persistent type id
#include <AD/persist/pstream.h>   // persistent stream base class
#include <AD/persist/pconvert.h>  // conversions
#include <AD/persist/po_impl.h>   // persistent stream implementation
#include <AD/hash/lhash2.h>       // linear probing hash table
#include <AD/strings/quark.h>     // atomic strings
#include <AD/contain/variset.h>   // variable length integer set

PObjectLog::PObjectLog(int n)
    : markers(n),
    object_types(PObjectType::number_of_types())
{}

PObjectLog::~PObjectLog()
{}

typedef PObjectLog::PObjectInfo PObjectInfo;

//////////////////////////////////////////////////////////////////////////////
//  Class Postream
//////////////////////////////////////////////////////////////////////////////

Postream::Postream( std::ostream& out)
    : _out(out),
    _object_log(new PObjectLog(1025)),
    _next_marker(P_FIRST_MARKER)
{}

Postream::~Postream()
{
  _object_log->clean();
  delete _object_log;
}

void PObjectLog::clean ()
{
  foreach (i, markers)
  {
    markers.value(i).obj = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////
//  Stream output from an object.
//////////////////////////////////////////////////////////////////////////////

Postream& operator << (Postream& s, const PObject& obj)
{
  obj.persist_type_id().write(s);
  obj.persist_write(s);
  return s;
}

//////////////////////////////////////////////////////////////////////////////
//  Stream output from an object pointer
//////////////////////////////////////////////////////////////////////////////

Postream& operator << (Postream& s, const PObject * obj)
{
  if (P_IS_UNBOXED(obj))
  {
    // (a) Object is unboxed
    //     Send small integer tag
    s << -(P_OBJECT_MARKER)obj;
  }
  else
  {
    Ix m = s._object_log->markers.lookup(P_WRAP_ADDR(obj));
    if (m)
    {
      // (b) Object already serialized
      //     Send object marker
      s << s._object_log->markers.value(m).marker;
    }
    else
    {
      // (c) Object is new.
      //     Add new marker to the log
      P_OBJECT_MARKER new_marker = s._next_marker--;

      s << P_NEW_OBJECT_TAG;
      s._object_log->markers.insert(P_WRAP_ADDR(obj),
                                    PObjectInfo(obj,new_marker));

      // Write out the type of object
      obj->persist_type_id().write(s);

      // Write out the contents of object
      obj->persist_write(s);
    }
  }
  return s;
}

//////////////////////////////////////////////////////////////////////////////
//  Output operators
//////////////////////////////////////////////////////////////////////////////

Postream& operator << (Postream& s, P_char c)
{
  s._out << c;
  return s;
}

Postream& operator << (Postream& s, P_uchar c)
{
  s._out << c;
  return s;
}

#ifdef PROP_BOOL_IS_DEFINED
Postream& operator << (Postream& s, bool b)
{
  char x = b ? 1 : 0;
  s._out.write(&x, sizeof(x));
  return s;
}
#endif

Postream& operator << (Postream& s, P_int16 n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, P_uint16 n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, int n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, unsigned int n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, P_int32 n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, P_uint32 n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, P_real32 n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, P_real64 n)
{
  P_local_to_canonic(n);
  s._out.write((char*)&n,sizeof(n));
  return s;
}

Postream& operator << (Postream& s, const P_char * str)
{
  if (str == 0)
  {
    P_int32 length = -1;
    s << length;
  }
  else
  {
    P_int32 length = strlen(str);
    s << length;
    s._out.write (str, length);
  }
  return s;
}

Postream& operator << (Postream& s, const P_uchar * str)
{
  return s << (const P_char*)str;
}

Postream& operator << (Postream& s, const Quark& q)
{
  return s << q.string();
}

Postream& Postream::write( const char buf [], int len)
{
  if (buf == 0)
  {
    P_int32 length = -1;
    *this << length;
  }
  else
  {
    P_int32 length = len >= 0 ? len : strlen(buf);
    *this << length;
    _out.write (buf, length);
  }
  return *this;
}

Postream& Postream::write( const unsigned char buf [], int len)
{
  return write((const char *)buf, len);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Write a persistent type to a persistent stream
//
//////////////////////////////////////////////////////////////////////////////

void PObjectType::write( Postream& f) const
{
  P_OBJECT_TYPEID id  = entry->unique_id;
  f << id;
  Bool found = f._object_log->object_types[id];
  if (found)
  {
    f << P_OBJECT_ID_TAG;
    // std::cerr << "[Writing " << *this << "]\n";
  }
  else
  {
    f << P_OBJECT_NAME_TAG;
    f.write(entry->type_name,entry->type_name_len);
    f._object_log->object_types.setUnion(id);
    // std::cerr << "[Writing new " << *this << "]\n";
  }
}
