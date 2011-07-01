#include <stdlib.h>
#include <iostream.h>
#include <strstream.h>
#include <fstream.h>
#include <AD/visualize/vcg.h>

//
//  Visualize a CFG
//

class VisualizeCFG : public VCG
{
public:
   VisualizeCFG() {}

   VisualizeCFG& Start(const char * bb)
   {  begin_node(bb); label("START"); color(lightblue); 
      shape(ellipse); end_node(bb); return *this;
   }

   VisualizeCFG& Stop(const char * bb)
   {  begin_node(bb); label("STOP"); color(lightblue); 
      shape(ellipse); end_node(bb); return *this;
   }

   VisualizeCFG& Compute(const char * bb,const char * code)
   {  begin_node(bb); label(code); color(lightgreen); end_node(bb); 
      return *this; 
   }

   VisualizeCFG& Test(const char * bb, const char * test)
   {  begin_node(bb); label(test); color(lightyellow); 
      shape(rhomb); end_node(bb); return *this;
   }
  
   VisualizeCFG& TrueBranch(const char * a, const char * b)
   {  begin_edge(a,b); label("true"); end_edge(a,b); return *this; }

   VisualizeCFG& BackTrueBranch(const char * a, const char * b)
   {  begin_backedge(a,b); label("true"); end_edge(a,b); return *this; }

   VisualizeCFG& FalseBranch(const char * a, const char * b)
   {  begin_edge(a,b); label("false"); end_edge(a,b); return *this; }

   VisualizeCFG& BackFalseBranch(const char * a, const char * b)
   {  begin_backedge(a,b); label("false"); end_edge(a,b); return *this; }

   VisualizeCFG& Jump(const char * a, const char * b)
   {  begin_edge(a,b); end_edge(a,b); return *this; }

   VisualizeCFG& BackJump(const char * a, const char * b)
   {  begin_backedge(a,b); end_edge(a,b); return *this; }

   VisualizeCFG& BeginRegion(const char * r, const char * l)
   {  begin_graph(r); label(l); color(lightgreen); 
      return *this; 
   }
   VisualizeCFG& EndRegion(const char * r)
   {  end_graph(r); 
      return *this; 
   }
};

int main()
{
   VisualizeCFG V;
   ostrstream S;
   const char * G = "A Sample Graph";
   const char * a = "a";
   const char * b = "b";
   const char * c = "c";
   const char * d1 = "d1";
   const char * d2 = "d2";
   const char * d3 = "d3";
   const char * d4 = "d4";
   const char * e = "e";
   const char * f = "f";
   const char * g = "g";
   const char * h = "h";
   const char * i = "i";
   const char * r = "r";

   V . begin_graph(G) . label(G) . display_edge_labels(true) 
     . layoutalgorithm(VCG::minbackward)
     . xspace(40) . yspace(40); 

   //  Create a sample CFG
   V . Start(a) 
     . Jump(a,b) 
     . Compute(b,"x := y + z;\nq := r * s;") 
     . Jump(b,c)
     . Test(c,"q > x") 
     . FalseBranch(c,e) 
     . BeginRegion(r,"sub region")
        . Test(d1,"x > 0")
	. TrueBranch(d1,d2)
	. FalseBranch(d1,d3)
        . Compute(d2,"x := x + 1;\ny := y / z;\nq := q[0];") 
        . Compute(d3,"x := x - 1;\ny := y / z;\nq := q[1];") 
	. Jump(d2,d4)
	. Jump(d3,d4)
        . Compute(d4,"y := y + x;\nx := z + 1;") 
     . EndRegion(r)
     . TrueBranch(c,d1) 
     . Compute(e,"x := x - 2;\nz := x * x;\nq : = q/z;") 
     . Jump(d4,f)
     . Jump(e,g) 
     . Test(f,"x != 0")
     . TrueBranch(f,g) 
     . BackFalseBranch(f,b)
     . Stop(g);

   V . end_graph(G);

   //  translate it into GDL
   V.print_GDL_on(S);

   ofstream TMP("./cfg.vcg");
   TMP << S.str();
   TMP.close();
   system("xvcg ./cfg.vcg");

   return 0;
}
