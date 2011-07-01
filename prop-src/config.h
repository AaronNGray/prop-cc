#ifndef configuration_h
#define configuration_h

#define VERSION                  "2.3"         // major version number
#define FILE_SEPARATOR           ':'           // search file separator
#define PATH_SEPARATOR           '/'           // path separator
#define DEFAULT_SEARCH_PATH      "."           // default search path
#define DEV_NULL                 "/dev/null"   // some place to dump output
#define MAX_CONJUNCTS            256           // max conjuncts in inference
#define MAX_INFERENCE_RULE_ARITY 256           // max objects in inference
#define MAX_COST                 32767         // max matching cost 
#define MAX_VECTOR_LEN           10            // max vector elements
#define MAX_TUPLE_ARITY          12            // maximum arity of .(...)

extern const char * PATCH_LEVEL;
extern const char * LAST_UPDATED;

#endif
