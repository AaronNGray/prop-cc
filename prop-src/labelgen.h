#ifndef label_generators_h
#define label_generators_h

///////////////////////////////////////////////////////////////////////////////
//  Label generator
///////////////////////////////////////////////////////////////////////////////

class LabelGen
{
  LabelGen(const LabelGen&);         // no copy constructor
  void operator = (const LabelGen&); // no assignment

private:
  const char * prefix;
  int          counter;
  const char * last;
public:

  LabelGen(const char *);
  ~LabelGen();

  const char * new_label ();
  const char * this_label() const
  {
    return last;
  }
};

#endif
