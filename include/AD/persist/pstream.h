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

#ifndef persistent_object_stream_h
#define persistent_object_stream_h

#include <iostream>
#include <AD/generic/generic.h>
#include <AD/persist/pobject.h>
#include <AD/memory/mem.h>


class Quark;

//////////////////////////////////////////////////////////////////////////////
//  Implementation note: persistent streams are NOT derived by subclassing
//  from the classes ios, std::istream, std::ostream, or iostream since the
//  read/write methods operator << and operator >> (among others) are
//  non-virtual.  Because the encoding of persistent values are drastically
//  different from the usual ASCII input/output, the usual methods cannot
//  work.
//
//  Rather we allow any base classes of std::istream and std::ostream to be attached
//  to our persistent streams.  In short, the persistent streams act as an
//  extra layer of protocol conversions between the transport and the
//  application layer.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Additional documentation:
//
// Persistent objects can be written and later recovered from a stream in
// its entirety in a serial manner.
//
// The persistence protocol is implemented in class Pstream in the library.
// User defined persistent types should be derived from the base class PObject.
// Each object should each redefine the following virtual methods:
//
//     class PObject {
//     public:
//         virtual const PObjectType& persist_type_id   () const;
//         virtual Pistream&          persist_read      (Pistream&);
//         virtual Postream&          persist_write     (Postream&) const;
// #   define DEFINE_PERSISTENT_CLASS(ID)
//         virtual const PObjectType& persist_type_id   () const;
//         virtual Pistream&          persist_read      (Pistream&);
//         virtual Postream&          persist_write     (Postream&) const;
//     };
//
// Briefly, method 'persist_type_id()' identifies the type of each object.
// The method 'persist_type_name()' returns a string identifying the type.
//
// Method 'persist_read()' and 'persist_write()' are invoked during
// reading and writing from and to a persistence stream.  These methods
// should not be called by the client directly but are instead called from
// the persistent stream classes.  Being such it is alright to place
// these virtual methods in the private section of the class.
//
// Currently, the persistent stream class heirarchy as structured as follows:
//
//          Pstream
//         /       \
//    Pistream    Postream
//         \       /
//         Piostream
//
// Persistent input streams have the following protocol.  Notice that
// an std::istream must be attached to the Pistream during object construction.
// An optional memory manager can also be attached to the persistent stream,
// and if this is supplied then all new storage will be acquired from this
// memory manager instead of from the operator new.
//
//    class Pistream : public virtual Pstream {
//    public:
//       Pistream(std::istream&);
//       Pistream(std::istream&, Mem&);
//      ~Pistream();
//
//       friend Pistream& operator >> (Pistream&, int&);
//       friend Pistream& operator >> (Pistream&, unsigned int&);
//       friend Pistream& operator >> (Pistream&, short&);
//       friend Pistream& operator >> (Pistream&, unsigned short&);
//       friend Pistream& operator >> (Pistream&, char&);
//       friend Pistream& operator >> (Pistream&, unsigned char&);
//       friend Pistream& operator >> (Pistream&, long&);
//       friend Pistream& operator >> (Pistream&, unsigned long&);
//       friend Pistream& operator >> (Pistream&, float&);
//       friend Pistream& operator >> (Pistream&, double&);
//       friend Pistream& operator >> (Pistream&, const char *&);
//       friend Pistream& operator >> (Pistream&, const unsigned char *&);
//       friend Pistream& operator >> (Pistream&, PObject&);
//       friend Pistream& operator >> (Pistream&, const PObject *&);
//    };
//
// As such, the persistent streams do not actually perform the actual I/O;
// it only implements the serialization and marshalling protocol.  This extra
// layer of abstraction provides more flexibility with little performance
// cost.  For example, we can attach any subclass of std::istream to a Pistream.
//
// The serialization protocol performs the following functions:
//   (a) insert type information into the byte streams and decode the type
//       information on the way back.
//   (b) encode pointer sharing information so that the structure of a network
//       of objects is preserved on the receiving end.  And finally,
//   (c) encode the information in network byte order so that the output format
//       of an object is architecture independent and portable across platforms
//       (currently floating point numbers are not properly encoded.)
//
//
// The output stream protocol is an exact mirror of the input protocol:
//
//    class Postream : public virtual Pstream {
//    public:
//       Postream(std::ostream&);
//      ~Postream();
//
//       friend Postream& operator << (Postream&, int);
//       friend Postream& operator << (Postream&, unsigned int);
//       friend Postream& operator << (Postream&, short);
//       friend Postream& operator << (Postream&, unsigned short);
//       friend Postream& operator << (Postream&, char);
//       friend Postream& operator << (Postream&, unsigned char);
//       friend Postream& operator << (Postream&, long);
//       friend Postream& operator << (Postream&, unsigned long);
//       friend Postream& operator << (Postream&, float);
//       friend Postream& operator << (Postream&, double);
//       friend Postream& operator << (Postream&, const char *);
//       friend Postream& operator << (Postream&, const unsigned char *);
//       friend Postream& operator << (Postream&, const PObject&);
//       friend Postream& operator << (Postream&, const PObject *);
//    };
//
// Each type of persistent objects makes use of an 'object factory' to
// create objects of each type.  Object factories are created and registered
// using the template PObjectFactory:
//
// template <class T>
//    class PObjectFactory {
//    public:
//       PObjectFactory(const PObjectTypeId&);
//       virtual PObject * create_object() { return new T; }
//    };
//
// Here's an example: persistent classes Foo and Bar, where Bar is
// a subclass of Foo, can be defined in the following manner:
//
// In foo.h
//
//     class Foo : public PObject {
//        int    temp;        // temp is not a persistent member
//
//        int    integer;     // the rest are persistent
//        char * string;
//        short  array[10];
//        Foo  * next;
//        Foo  * last;
//     public:
//        DEFINE_PERSISTENT_CLASS(1, "Foo")
//     };
//
//     class Bar : public Foo {
//        Foo    foo;
//        char * name;
//     public:
//        DEFINE_PERSISTENT_CLASS(2, "Bar");
//     };
//
// In foo.cc
//
//     //
//     // Create an object factory for each persistent type.
//     // The supplied type id for each factory must match that
//     // of the object.
//     //
//     PObjectFactory<Foo> foo_factory(1);
//     PObjectFactory<Bar> bar_factory(2);
//
// Note the use of the macro DEFINE_PERSISTENT_CLASS to save work.
// The class specific read and write methods are defined as follows:
//
//     Postream& Foo::persist_write(Postream& f)
//     {  f << integer;
//        f << string;
//        for (int i = 0; i < 10; i++)
//           f << array[i];
//        f << next;
//        f << last;
//     }
//
//     Pistream& Foo::persist_read(Pistream& f)
//     {  f >> integer;
//        f >> string;
//        for (int i = 0; i < 10; i++)
//           f >> array[i];
//        f >> next;
//        f >> last;
//     }
//
//     Postream& Bar::persist_write(Postream& f)
//     {  Foo::persist_write(f);
//        f << foo;
//        f << name;
//     }
//
//     Pistream& Bar::persist_read(Pistream& f)
//     {  Foo::persist_read(f);
//        f >> foo;
//        f >> name;
//     }
//
// Notice that all the persistent members must be read and written in
// the same order.  The derivation of each persist_write() and persist_read()
// methods is very similar to the trace() method for the garbage collector,
// except that in this case we have to read and write all members, not just
// pointers.
//
// As we have mentioned, all sharing between pointers are preserved
// in the persistent encoding, so it is safe to store general graph
// like structures (i.e. even cyclic structures.)
//
// While reading from a persistent stream, the storage for pointers to
// PObject's are allocated by calling the appropriate object factories
// (e.g. next and last members in class Foo), which in turns calls the
// default new method for the class.  This, by default, is simply
// ::operator new().  It is up to the implementor for each class to override
// this method if other storage management strategy is needed.
//
// One final note about strings (char * and unsigned char *): the storage
// for a string is allocated on the fly during reading.  By default, this
// storage is allocated by calling 'new char []'.  If instead a memory manager
// is supplied to the Pistream's constructor, then memory will be allocated
// from the memory manager.  All storage allocated are not kept track of in
// any way by the persistent streams, and it is up to the user to release
// them when they are not longer needed.
//
// As a convenience, all garbage collectors are subclassed from GC, which in
// turns is subclassed from Mem, so it is possible to use garbage collection
// if it is difficult to manually manage the allocated storage.
//
// Feb 19, 1995.
// Allen Leung
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//  Persistent stream base class.
//
//  Stream format:
//     (1) Integers and float point numbers --- these are first encoded in
//         network byte order and send without any additional type information.
//         Float point numbers are currently not-encoded so they are
//         non-portable across different machines.
//     (2) Strings --- strings have two formats:
//         (a) null strings:  the type id -1 is sent
//         (b) non-empty strings:  length + contents
//     (3) PObject   --- All PObjects are prefixed by its typeid.
//////////////////////////////////////////////////////////////////////////////

class Pstream
{
  Pstream(const Pstream&);          // no copy constructor
  void operator = (const Pstream&); // no assignment

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////

public:
  Pstream();
  virtual ~Pstream();
  virtual void error (const char * message);
};

//////////////////////////////////////////////////////////////////////////////
//  Persistent input stream
//////////////////////////////////////////////////////////////////////////////

class Pistream : virtual public Pstream
{

  Pistream(const Pistream&);         // no copy constructor
  void operator = (const Pistream&); // no assignment

protected:

  std::istream&           _in;            // actual attached input stream
  class PMarkerLog * _marker_log;    // mapping from marker to pointer
  P_OBJECT_MARKER    _next_marker;   // next available marker.
  Mem *              _mem;           // memory manager

  friend class PObjectType;

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  explicit Pistream(std::istream&);
  Pistream(std::istream&, Mem&);
  virtual ~Pistream();

  ///////////////////////////////////////////////////////////////////////////
  //  Conversions
  ///////////////////////////////////////////////////////////////////////////
  inline operator const std::istream& () const
  {
    return _in;
  }
  inline operator       std::istream& ()
  {
    return _in;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Input for predefined types
  ///////////////////////////////////////////////////////////////////////////
  virtual int read (char buf[], int max);
  virtual int read (unsigned char buf[], int max);
  friend PObject * read_object (Pistream&);
#ifdef PROP_BOOL_IS_DEFINED

  friend Pistream& operator >> (Pistream&, bool&);
#endif

  friend Pistream& operator >> (Pistream&, P_char&);
  friend Pistream& operator >> (Pistream&, P_uchar&);
  friend Pistream& operator >> (Pistream&, int&);
  friend Pistream& operator >> (Pistream&, unsigned int&);
  friend Pistream& operator >> (Pistream&, P_int16&);
  friend Pistream& operator >> (Pistream&, P_uint16&);
  friend Pistream& operator >> (Pistream&, P_int32&);
  friend Pistream& operator >> (Pistream&, P_uint32&);
  friend Pistream& operator >> (Pistream&, P_real32&);
  friend Pistream& operator >> (Pistream&, P_real64&);
  friend Pistream& operator >> (Pistream&, const P_char *&);
  friend Pistream& operator >> (Pistream&, const P_uchar *&);
  friend Pistream& operator >> (Pistream&, PObject&);
  friend Pistream& operator >> (Pistream&, Quark&);
  friend Pistream& operator >> (Pistream&, void (*)(Pistream&));
  inline friend Pistream& operator >> (Pistream& f, const PObject*& p)
  {
    p = read_object(f);
    return f;
  }
};

//////////////////////////////////////////////////////////////////////////////
//  Persistent onput stream
//////////////////////////////////////////////////////////////////////////////

class Postream : virtual public Pstream
{

  Postream(const Postream&);         // no copy constructor
  void operator = (const Postream&); // no assignment

protected:

  std::ostream&           _out;           // actually attached output stream.
  class PObjectLog * _object_log;    // mapping from pointer to marker.
  P_OBJECT_MARKER    _next_marker;   // next available marker.

  friend class PObjectType;

public:
  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  explicit Postream(std::ostream&);
  virtual ~Postream();

  ///////////////////////////////////////////////////////////////////////////
  //  Conversions
  ///////////////////////////////////////////////////////////////////////////
  inline operator const std::ostream& () const
  {
    return _out;
  }
  inline operator       std::ostream& ()
  {
    return _out;
  }

  ///////////////////////////////////////////////////////////////////////////
  //  Output for predefined types
  ///////////////////////////////////////////////////////////////////////////
  virtual Postream& write (const char buf[], int len);
  virtual Postream& write (const unsigned char buf[], int len);
#ifdef PROP_BOOL_IS_DEFINED

  friend Postream& operator << (Postream&, bool);
#endif

  friend Postream& operator << (Postream&, P_char);
  friend Postream& operator << (Postream&, P_uchar);
  friend Postream& operator << (Postream&, int);
  friend Postream& operator << (Postream&, unsigned int);
  friend Postream& operator << (Postream&, P_int16);
  friend Postream& operator << (Postream&, P_uint16);
  friend Postream& operator << (Postream&, P_int32);
  friend Postream& operator << (Postream&, P_uint32);
  friend Postream& operator << (Postream&, P_real32);
  friend Postream& operator << (Postream&, P_real64);
  friend Postream& operator << (Postream&, const P_char *);
  friend Postream& operator << (Postream&, const P_uchar *);
  friend Postream& operator << (Postream&, const PObject&);
  friend Postream& operator << (Postream&, const PObject*);
  friend Postream& operator << (Postream&, const Quark&);
  friend Postream& operator << (Postream&, void (*)(Postream&));
};

//////////////////////////////////////////////////////////////////////////////
//  Persistent input/output stream
//////////////////////////////////////////////////////////////////////////////

class Piostream : public Pistream, public Postream
{
  Piostream(const Piostream&);        // no copy constructor
  void operator = (const Piostream&); // no assignment

public:

  ///////////////////////////////////////////////////////////////////////////
  //  Constructors and destructor
  ///////////////////////////////////////////////////////////////////////////
  Piostream(iostream&);
  Piostream(iostream&, Mem&);
  Piostream(std::istream&, std::ostream&);
  Piostream(std::istream&, std::ostream&, Mem&);
  virtual ~Piostream();
};

//////////////////////////////////////////////////////////////////////////////
//
//  Manipulator functions
//
//////////////////////////////////////////////////////////////////////////////
extern void version (Postream&);      // write version
extern void version (Pistream&);      // read and verify version
extern void start_group (Postream&);  // start a group
extern void start_group (Pistream&);  // check for start of group
extern void end_group (Postream&);    // end a group
extern void end_group (Pistream&);    // check for end of group

#endif
