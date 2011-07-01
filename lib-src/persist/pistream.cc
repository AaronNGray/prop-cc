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
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <strstream>
#include <AD/persist/pstream.h>      // persistent stream base class
#include <AD/persist/pconvert.h>     // conversions
#include <AD/persist/ptype.h>        // object types
#include <AD/persist/pfactory.h>     // object factories
#include <AD/persist/pi_impl.h>      // Pistream implementation
#include <AD/contain/vararray.h>     // variable sized array
#include <AD/strings/quark.h>


PMarkerLog::PMarkerLog(int n)
    : objects(P_FIRST_MARKER-n, P_FIRST_MARKER, 0),
    object_types(0,255)
{ /* clean(); */
}

PMarkerLog::~PMarkerLog()
{ }

void PMarkerLog::clean()
{
  PObject ** array = objects;
  memset(array + objects.lo(), 0,
         (objects.hi() - objects.lo() + 1) * sizeof(PObject*));
}

//////////////////////////////////////////////////////////////////////////////
//  Class Pistream
//////////////////////////////////////////////////////////////////////////////

Pistream::Pistream( std::istream& in)
    : _in          (in),
    _marker_log  (new PMarkerLog(256)),
    _next_marker (P_FIRST_MARKER),
    _mem         (0)
{}

Pistream::Pistream( std::istream& in, Mem& m)
    : _in          (in),
    _marker_log  (new PMarkerLog(256)),
    _next_marker (P_FIRST_MARKER),
    _mem         (&m)
{}

Pistream::~Pistream()
{
  delete _marker_log;
}

//////////////////////////////////////////////////////////////////////////////
//  Stream input into an object.
//////////////////////////////////////////////////////////////////////////////

Pistream& operator >> (Pistream& s, PObject& obj)
{
  const PObjectType& expected_id = obj.persist_type_id();
  PObjectType actual_id;
  actual_id.read(s);
  if (expected_id != actual_id)
  {
    char buf [1024];
    std::ostrstream ERR(buf,sizeof(buf));
    ERR << "expecting type id " << expected_id
    << " but found " << actual_id << std::ends;
    s.error(ERR.str());
    return s;
  }
  obj.persist_read(s);
  return s;
}

//////////////////////////////////////////////////////////////////////////////
//  Stream input into an object pointer
//////////////////////////////////////////////////////////////////////////////

PObject * read_object( Pistream& s)
{
  P_OBJECT_MARKER marker;
  s >> marker;
  if (P_IS_NEW_OBJECT(marker))
  {
    PObjectType id;
    id.read(s);
    PObject * new_object = PBaseFactory::create_object(id);
    P_OBJECT_MARKER new_marker = s._next_marker--;
    s._marker_log->objects[new_marker] = new_object;
    new_object->persist_read(s);
    return new_object;
  }
  else if (P_IS_MARKER(marker))
  {
    if (marker > s._next_marker)
    {
      return s._marker_log->objects[marker];
    }
    else
    {
      char buf [1024];
      std::ostrstream ERR(buf,sizeof(buf));
      ERR << "object marker " << marker << " is undefined" << std::ends;
      s.error(ERR.str());
      return 0;
    }
  }
  else
  {
    return (PObject*)-marker;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  Stream input for common types
//////////////////////////////////////////////////////////////////////////////

Pistream& operator >> (Pistream& s, P_char& c)
{
  s._in >> c;
  return s;
}

Pistream& operator >> (Pistream& s, P_uchar& c)
{
  s._in >> c;
  return s;
}

#ifdef PROP_BOOL_IS_DEFINED
Pistream& operator >> (Pistream& s, bool& b)
{
  char x;
  s._in.read(&x,sizeof(x));
  b = x != 0;
  return s;
}
#endif

Pistream& operator >> (Pistream& s, P_int16& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, P_uint16& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, int& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, unsigned int& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, P_int32& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, P_uint32& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, P_real32& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, P_real64& n)
{
  s._in.read((char*)&n,sizeof(n));
  P_canonic_to_local(n);
  return s;
}

Pistream& operator >> (Pistream& s, const P_char *& str)
{
  P_int32 length = -1;
  s >> length;
  if (length < 0)
  {
    str = 0;
  }
  else
  {
    char * buf = s._mem ? (char*)s._mem->m_alloc(length + 1)
                 : new char [length + 1];
    s._in.read(buf,length);
    buf[length] = '\0';
    str = buf;
  }
  return s;
}

Pistream& operator >> (Pistream& s, const P_uchar *& str)
{
  return s >> *(const P_char **)(&str);
}

Pistream& operator >> (Pistream& s, Quark& q)
{
  char buf[4096];
  s.read(buf, sizeof(buf));
  q = Quark(buf);
  return s;
}

int Pistream::read( char buf[], int max)
{
  P_int32 length = -1;
  *this >> length;
  if (length < 0)
    length = 0;
  _in.read(buf,max < length ? max : length);
  if (max > length)
    buf[length] = '\0';
  else
    _in.seekg(streamoff(length - max), ios::cur);
  return length;
}

int Pistream::read( unsigned char buf[], int max)
{
  return read((char *)buf, max);
}


//////////////////////////////////////////////////////////////////////////////
//
//  Read a persistent type from a persistent stream.
//
//////////////////////////////////////////////////////////////////////////////

void PObjectType::read( Pistream& f)
{
  P_OBJECT_TYPEID id = -1;
  f >> id;             // read type id
  P_STREAM_TAG tag = 0;
  f >> tag;            // read stream tag
  if (tag == P_OBJECT_NAME_TAG)
  {  // must be followed by string
    char name[1024];
    int len = f.read(name,sizeof(name)-1);
    if (len >= 0)
      name[len] = '\0';
    if ((entry = PObjectType::lookup_entry(name)))
    {
      f._marker_log->object_types[id] = entry;
      // std::cerr << "Name " << name << ", id " << id << " = " << *this << '\n';
    }
    else
    {
      char buf[1024];
      std::ostrstream ERR(buf,sizeof(buf));
      ERR << "unknown persistent type name " << name << std::ends;
      f.error(ERR.str());
    }
  }
  else if (tag == P_OBJECT_ID_TAG)
  {  // check id
    if (f._marker_log->object_types.hasKey(id))
    {
      entry = f._marker_log->object_types[id];
      // std::cerr << "Id " << id << " = " << *this << '\n';
      if (entry == 0)
      {
        char buf[1024];
        std::ostrstream ERR(buf,sizeof(buf));
        ERR << "undefined persistent id " << id << std::ends;
        f.error(ERR.str());
      }
    }
    else
    {
      char buf[1024];
      std::ostrstream ERR(buf,sizeof(buf));
      ERR << "bad persistent id " << id << std::ends;
      f.error(ERR.str());
    }
  }
  else
  {  // bad tag error here
    char buf[1024];
    std::ostrstream ERR(buf,sizeof(buf));
    ERR << "bad persistent stream tag " << tag
    << "(id = " << id << ')' << std::ends;
    f.error(ERR.str());
    entry = 0;
  }
}
