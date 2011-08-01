///////////////////////////////////////////////////////////////////////////////
//  This file is generated automatically using Prop (version 2.4.0),
//  last updated on Jul 1, 2011.
//  The original source file is "..\..\prop-src\prop-main.pcc".
///////////////////////////////////////////////////////////////////////////////

#define PROP_REGEXP_MATCHING_USED
#include <propdefs.h>
#line 1 "../../prop-src/prop-main.pcc"
///////////////////////////////////////////////////////////////////////////////
//
//      ////////
//     //     //   //////   /////   ///////
//    ////////   //       //   //  //    //
//   //         //       //   //  ///////
//  //         //        /////   //
//                              //      Version 2.4.x
//
//                                      Allen Leung (leunga@cs.nyu.edu)
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include <string>
#include "basics.h"
#include "config.h"
#include "author.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Help message
//
///////////////////////////////////////////////////////////////////////////////

static const char * HELP_MESSAGE =
"%s version %s.%s, last updated on %s\n"
"usage: %s [options] <files>\n"
"options:  [-automake]\n"
"          [-d -debug] [-G -GNU] [-html] [-I<path>]\n"
"          [-l -no_line_directives] [-M -make_depends]\n"
"          [-n -no_codegen] [-N -non_linear]\n"
"          [-o<outfile>] [-O#]\n"
"          [-Ofast_string_match] [-Oadaptive_matching]\n"
"          [-Oinline_casts] [-Otagged_pointer] [-Orewriting]\n"
"          [-r -report] [-s -strict] [-S -save_space]\n"
"          [-t -stdout] [-v#] [-V# -vector#] [-vcg]\n"
"          [-new_list_format]\n"
"          [-use_global_pools]\n"
"          [-memory_usage]\n"
;

///////////////////////////////////////////////////////////////////////////////
//
//  The global options data structure.
//
///////////////////////////////////////////////////////////////////////////////

PropOptions options;
static Bool print_memory_usage = false;

///////////////////////////////////////////////////////////////////////////////
//
//  Routine to process command line arguments
//
///////////////////////////////////////////////////////////////////////////////

void PropOptions::process_command_line_arguments
     (int argc, const char * argv[])
{
  Bool help = false;
  prog_name = argv[0];
  for (argc--, argv++; argc > 0; argc--, argv++)
  {
    
#line 67 "../../prop-src/prop-main.pcc"
#line 132 "../../prop-src/prop-main.pcc"
{
  char const * _V1 = argv[0];
  {
static const DFATables::Offset _X1_base [ 224 ] = {
   0, 359, 358, 0, 31, 43, 356, 356, 35, 355, 65, 24, 36, 0, 83, 352, 
   352, 352, 0, 99, 0, 0, 129, 351, 349, 344, 344, 344, 86, 343, 343, 0, 
   91, 343, 343, 342, 342, 342, 342, 341, 341, 340, 338, 338, 338, 336, 336, 327, 
   0, 324, 324, 324, 324, 323, 323, 323, 92, 322, 316, 316, 307, 302, 301, 301, 
   299, 298, 298, 297, 297, 0, 297, 297, 297, 297, 297, 297, 297, 296, 296, 296, 
   296, 296, 0, 0, 288, 281, 277, 276, 276, 276, 276, 272, 0, 271, 270, 269, 
   269, 269, 269, 269, 268, 268, 268, 0, 268, 261, 256, 255, 255, 249, 249, 0, 
   0, 249, 0, 249, 249, 247, 244, 244, 238, 238, 238, 235, 235, 234, 232, 232, 
   232, 232, 232, 232, 231, 231, 231, 231, 231, 229, 229, 227, 227, 227, 223, 219, 
   219, 219, 219, 213, 213, 0, 212, 212, 212, 206, 206, 206, 205, 205, 205, 203, 
   203, 200, 199, 199, 199, 199, 199, 199, 196, 191, 0, 191, 191, 191, 185, 0, 
   180, 180, 180, 176, 175, 174, 174, 171, 171, 171, 171, 163, 163, 159, 159, 0, 
   158, 158, 158, 156, 155, 155, 155, 154, 0, 154, 154, 154, 154, 154, 154, 154, 
   146, 136, 132, 0, 0, 104, 97, 0, 91, 91, 80, 75, 26, 24, 0, 0
   };
static const DFATables::State _X1_check [ 395 ] = {
   3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
   3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 11, 4, 221, 4, 5, 220, 
   4, 8, 12, 11, 4, 0, 12, 4, 4, 4, 4, 5, 4, 4, 4, 4, 
   4, 10, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
   10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
   10, 10, 10, 10, 10, 14, 19, 28, 32, 219, 218, 217, 56, 216, 0, 0, 
   0, 19, 14, 28, 56, 32, 19, 214, 0, 19, 0, 0, 0, 0, 0, 0, 
   19, 22, 19, 22, 22, 22, 22, 213, 22, 22, 22, 22, 22, 22, 22, 22, 
   22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 
   22, 22, 22, 22, 22, 210, 209, 208, 207, 198, 202, 194, 199, 0, 0, 189, 
   204, 187, 203, 201, 0, 0, 196, 206, 190, 205, 197, 195, 193, 192, 188, 186, 
   182, 180, 0, 0, 0, 184, 0, 0, 0, 183, 185, 181, 179, 178, 177, 174, 
   173, 168, 176, 172, 167, 165, 161, 0, 0, 0, 171, 164, 169, 166, 160, 156, 
   154, 162, 163, 158, 152, 159, 155, 148, 146, 143, 157, 153, 144, 145, 151, 142, 
   150, 141, 138, 147, 136, 130, 128, 127, 0, 135, 129, 137, 131, 124, 126, 122, 
   120, 119, 139, 134, 140, 121, 132, 133, 125, 117, 123, 116, 108, 0, 0, 0, 
   0, 0, 118, 115, 110, 113, 106, 105, 109, 107, 104, 0, 0, 102, 99, 0, 
   0, 0, 100, 97, 0, 0, 0, 98, 91, 86, 88, 95, 96, 94, 93, 101, 
   90, 87, 85, 89, 84, 81, 74, 68, 0, 72, 0, 71, 0, 70, 77, 64, 
   79, 76, 66, 78, 0, 80, 75, 67, 63, 73, 61, 60, 65, 62, 59, 57, 
   55, 49, 47, 46, 50, 53, 0, 58, 40, 0, 51, 25, 0, 0, 54, 52, 
   44, 45, 41, 17, 42, 38, 27, 23, 2, 1, 26, 0, 43, 35, 37, 36, 
   34, 24, 15, 30, 39, 9, 0, 0, 29, 33, 0, 0, 0, 0, 0, 0, 
   16, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0
};
static const DFATables::State _X1_next [ 395 ] = {
   4, 0, 4, 4, 4, 23, 22, 21, 20, 19, 18, 4, 17, 4, 16, 4, 
   4, 15, 4, 4, 4, 14, 4, 4, 13, 12, 11, 10, 4, 9, 8, 7, 
   6, 5, 4, 4, 4, 4, 4, 4, 4, 4, 33, 4, 223, 4, 25, 222, 
   4, 29, 35, 32, 4, 0, 34, 4, 4, 4, 4, 24, 4, 4, 4, 4, 
   4, 31, 28, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 31, 31, 37, 46, 52, 56, 13, 221, 220, 78, 219, 0, 0, 
   0, 45, 36, 51, 77, 55, 44, 218, 0, 43, 0, 0, 0, 0, 0, 0, 
   42, 22, 41, 22, 22, 22, 22, 217, 22, 22, 22, 22, 22, 22, 22, 22, 
   22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 
   22, 22, 22, 22, 22, 216, 215, 214, 213, 205, 208, 201, 206, 0, 0, 197, 
   210, 195, 209, 207, 0, 0, 203, 212, 198, 211, 204, 202, 200, 199, 196, 194, 
   191, 189, 0, 0, 0, 192, 0, 0, 0, 21, 193, 190, 188, 187, 186, 184, 
   183, 179, 185, 182, 178, 176, 172, 0, 0, 0, 181, 175, 180, 177, 171, 18, 
   167, 173, 174, 169, 165, 170, 168, 162, 160, 157, 20, 166, 158, 159, 164, 156, 
   163, 155, 152, 161, 150, 144, 142, 141, 0, 149, 143, 151, 145, 138, 140, 136, 
   134, 133, 153, 148, 154, 135, 146, 147, 139, 131, 137, 130, 125, 0, 0, 0, 
   0, 0, 132, 129, 127, 128, 123, 122, 126, 124, 121, 0, 0, 120, 117, 0, 
   0, 0, 118, 115, 0, 0, 0, 116, 110, 105, 107, 113, 114, 112, 111, 119, 
   109, 106, 104, 108, 103, 102, 95, 90, 0, 93, 0, 92, 0, 91, 98, 86, 
   100, 97, 88, 99, 0, 101, 96, 89, 85, 94, 83, 82, 87, 84, 81, 79, 
   76, 70, 69, 46, 71, 74, 0, 80, 40, 0, 72, 25, 0, 0, 75, 73, 
   67, 68, 64, 40, 65, 62, 50, 47, 3, 3, 49, 0, 66, 59, 61, 60, 
   58, 48, 38, 54, 63, 30, 0, 0, 53, 57, 0, 0, 0, 0, 0, 0, 
   39, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0
};
static const DFATables::State _X1_def [ 224 ] = {
   0, 0, 0, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 10, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
   };
static const unsigned char _X1_equiv_classes [ 256 ] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 
   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 5, 4, 6, 4, 4, 4, 7, 8, 9, 
   4, 4, 4, 10, 4, 11, 12, 4, 4, 4, 4, 4, 4, 4, 4, 13, 
   4, 14, 15, 16, 17, 18, 19, 20, 21, 22, 4, 23, 24, 25, 26, 27, 
   28, 4, 29, 30, 31, 32, 33, 34, 4, 35, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
   };
static const DFATables::Rule _X1_accept_rule [ 224 ] = {
   0, 0, 0, 31, 31, 23, 31, 9, 8, 7, 13, 3, 31, 4, 28, 2, 
   31, 31, 21, 31, 20, 25, 11, 5, 31, 23, 31, 31, 31, 31, 31, 12, 
   31, 31, 31, 31, 31, 31, 31, 31, 22, 31, 31, 31, 31, 31, 14, 31, 
   24, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 31, 31, 5, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 6, 28, 31, 31, 31, 31, 31, 31, 31, 31, 10, 31, 31, 31, 
   31, 31, 31, 31, 31, 31, 31, 2, 31, 31, 31, 31, 31, 31, 31, 8, 
   9, 31, 7, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 31, 31, 1, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 3, 31, 31, 31, 31, 19, 
   31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 
   31, 31, 31, 31, 31, 31, 31, 31, 17, 31, 31, 31, 31, 31, 31, 31, 
   31, 31, 31, 27, 18, 31, 31, 29, 31, 31, 31, 31, 31, 31, 15, 16
   };
    static const RegexMatch _X1
                    ( _X1_base,
                      _X1_check,
                      _X1_def,
                      _X1_next,
                      _X1_accept_rule,
                      _X1_equiv_classes );
    switch(_X1.MatchText(_V1)) {
      case 1: {
#line 68 "../../prop-src/prop-main.pcc"
       automake = true; 
#line 68 "../../prop-src/prop-main.pcc"
      } break;
      case 2: {
#line 69 "../../prop-src/prop-main.pcc"
       debug = true; 
#line 69 "../../prop-src/prop-main.pcc"
      } break;
      case 3: {
#line 70 "../../prop-src/prop-main.pcc"
       emit_code = false; 
#line 70 "../../prop-src/prop-main.pcc"
      } break;
      case 4: {
#line 71 "../../prop-src/prop-main.pcc"
       line_directives = false; 
#line 71 "../../prop-src/prop-main.pcc"
      } break;
      case 5: {
#line 72 "../../prop-src/prop-main.pcc"
       GNU_style_message = true; 
#line 72 "../../prop-src/prop-main.pcc"
      } break;
      case 6: {
#line 73 "../../prop-src/prop-main.pcc"
       generate_html = true; 
#line 73 "../../prop-src/prop-main.pcc"
      } break;
      case 7: {
#line 74 "../../prop-src/prop-main.pcc"
       generate_report = true; 
#line 74 "../../prop-src/prop-main.pcc"
      } break;
      case 8: {
#line 75 "../../prop-src/prop-main.pcc"
       strict_checking = true; 
#line 75 "../../prop-src/prop-main.pcc"
      } break;
      case 9: {
#line 76 "../../prop-src/prop-main.pcc"
       to_stdout = true; 
#line 76 "../../prop-src/prop-main.pcc"
      } break;
      case 10: {
#line 77 "../../prop-src/prop-main.pcc"
       trace = true; 
#line 77 "../../prop-src/prop-main.pcc"
      } break;
      case 11: {
#line 79 "../../prop-src/prop-main.pcc"
        
        char c[2]; c[0] = FILE_SEPARATOR; c[1] = '\0';
        strcat(search_paths,c);
        strcat(search_paths,argv[0]+2);
        
#line 83 "../../prop-src/prop-main.pcc"
      } break;
      case 12: {
#line 84 "../../prop-src/prop-main.pcc"
      strcpy(output_file_name,argv[0]+2); 
#line 84 "../../prop-src/prop-main.pcc"
      } break;
      case 13: {
#line 86 "../../prop-src/prop-main.pcc"
        
        if (argc > 1)
        {
          argv++; argc--;
          strcpy(output_file_name,argv[0]);
        }
        else
          help = true;
        
#line 94 "../../prop-src/prop-main.pcc"
      } break;
      case 14: {
#line 96 "../../prop-src/prop-main.pcc"
        
        int opt = atol(argv[0]+2);
        optimization_level = opt <= 0 ? 1 : opt;
        fast_string_match = optimization_level & 1;
        adaptive_matching = optimization_level & 2;
        inline_casts      = optimization_level & 4;
        tagged_pointer    = optimization_level & 8;
        optimize_rewrite  = optimization_level & 16;
        
#line 104 "../../prop-src/prop-main.pcc"
      } break;
      case 15: {
#line 105 "../../prop-src/prop-main.pcc"
       fast_string_match = true; 
#line 105 "../../prop-src/prop-main.pcc"
      } break;
      case 16: {
#line 106 "../../prop-src/prop-main.pcc"
       adaptive_matching = true; 
#line 106 "../../prop-src/prop-main.pcc"
      } break;
      case 17: {
#line 107 "../../prop-src/prop-main.pcc"
       inline_casts = true; 
#line 107 "../../prop-src/prop-main.pcc"
      } break;
      case 18: {
#line 108 "../../prop-src/prop-main.pcc"
       tagged_pointer = true; 
#line 108 "../../prop-src/prop-main.pcc"
      } break;
      case 19: {
#line 109 "../../prop-src/prop-main.pcc"
       optimize_rewrite = true; 
#line 109 "../../prop-src/prop-main.pcc"
      } break;
      case 20: {
#line 110 "../../prop-src/prop-main.pcc"
       nonlinear_patterns = true; 
#line 110 "../../prop-src/prop-main.pcc"
      } break;
      case 21: {
#line 111 "../../prop-src/prop-main.pcc"
       save_space = true; 
#line 111 "../../prop-src/prop-main.pcc"
      } break;
      case 22: {
#line 112 "../../prop-src/prop-main.pcc"
       max_vector_len = atol(argv[0]+2); 
#line 112 "../../prop-src/prop-main.pcc"
      } break;
      case 23: {
#line 114 "../../prop-src/prop-main.pcc"
        
        verbosity = atol(argv[0]+2);
        if (verbosity <= 0)
          verbosity = 1;
        
#line 118 "../../prop-src/prop-main.pcc"
      } break;
      case 24: {
#line 119 "../../prop-src/prop-main.pcc"
       visualization = true; 
#line 119 "../../prop-src/prop-main.pcc"
      } break;
      case 25: {
#line 120 "../../prop-src/prop-main.pcc"
       gen_dependences = true; 
#line 120 "../../prop-src/prop-main.pcc"
      } break;
      case 26: {
#line 121 "../../prop-src/prop-main.pcc"
       emit_code = false; 
#line 121 "../../prop-src/prop-main.pcc"
      } break;
      case 27: {
#line 122 "../../prop-src/prop-main.pcc"
       new_list_format = true; 
#line 122 "../../prop-src/prop-main.pcc"
      } break;
      case 28: {
#line 123 "../../prop-src/prop-main.pcc"
       help = true; 
#line 123 "../../prop-src/prop-main.pcc"
      } break;
      case 29: {
#line 124 "../../prop-src/prop-main.pcc"
       MEM::use_global_pools(); 
#line 124 "../../prop-src/prop-main.pcc"
      } break;
      case 30: {
#line 125 "../../prop-src/prop-main.pcc"
       print_memory_usage = true; 
#line 125 "../../prop-src/prop-main.pcc"
      } break;
      case 31: {
#line 127 "../../prop-src/prop-main.pcc"
        
        error("%s: unknown option %s\n", prog_name, argv[0]);
        help = true;
        
#line 130 "../../prop-src/prop-main.pcc"
      } break;
      default: {
#line 132 "../../prop-src/prop-main.pcc"
       input_files[file_count++] = argv[0]; 
#line 132 "../../prop-src/prop-main.pcc"
      }
    }
  }
}
#line 133 "../../prop-src/prop-main.pcc"
#line 133 "../../prop-src/prop-main.pcc"

    if ( argv[0][0] == '-')
      input_options[option_count++] = argv[0];
  }
  input_file_name = input_files[0];

  ////////////////////////////////////////////////////////////////////////////
  //  Print help message
  ////////////////////////////////////////////////////////////////////////////
  if (help || file_count == 0)
  {
    error( HELP_MESSAGE, prog_name, VERSION, PATCH_LEVEL, LAST_UPDATED, prog_name);
    exit(1);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Run a program recursively.
//
///////////////////////////////////////////////////////////////////////////////

static int run_prog( const char * prog, int argc, const char * argv[])
{
  char command[4096];
  strcpy( command, "\"");
  strcat( command, prog);
  strcat( command, "\"");
  for (int i = 0; i < argc; i++)
  {
    strcat( command, " ");
    strcat( command, argv[i]);
  }
  int stat = system( command);
  if (stat)
    error("Error in command: %s\n", command);
  return stat;
}

///////////////////////////////////////////////////////////////////////////////
//
//  The main program.
//
///////////////////////////////////////////////////////////////////////////////

int main( int argc, const char * argv [])
{
  extern int process_input( PropOptions&);

  options.process_command_line_arguments( argc, argv);
  options.compute_output_file_name();

  int stat;

  if (options.file_count == 1)
  {
    stat = process_input( options);
    if (print_memory_usage)
    {
      msg("[global pool size = %i local pool size = %i string pool size = %i]\n",
           global_pool.bytes_used(), mem_pool.bytes_used(), str_pool.bytes_used());
    }
  }
  else
  {
    for (int i = 0; i < options.file_count; i++)
    {
      options.input_options[options.option_count] = options.input_files[i];
      stat = run_prog(options.prog_name,
                      options.option_count+1,
                      options.input_options);
      if (stat) break;
    }
  }
  exit(stat);
}
#line 209 "../../prop-src/prop-main.pcc"
/*
------------------------------- Statistics -------------------------------
Merge matching rules         = yes
Number of DFA nodes merged   = 0
Number of ifs generated      = 0
Number of switches generated = 1
Number of labels             = 0
Number of gotos              = 0
Adaptive matching            = disabled
Fast string matching         = disabled
Inline downcasts             = disabled
--------------------------------------------------------------------------
*/
