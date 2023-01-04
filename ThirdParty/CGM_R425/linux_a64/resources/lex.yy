/*
    Copyright (c) 2012 NVIDIA Corporation. All rights reserved.

    TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
    *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
    OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, NONINFRINGEMENT,IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA 
    OR ITS SUPPLIERS BE  LIABLE  FOR  ANY  DIRECT, SPECIAL,  INCIDENTAL,  INDIRECT,  OR  
    CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS 
    OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY 
    OTHER PECUNIARY LOSS) ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, 
    EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

    Please direct any questions to tlorach@nvidia.com (Tristan Lorach)
*/
%{
    #pragma warning(disable:4996)
    #include  <math.h>
    #include  <string>
    #include  <stack>

    #include <stdio.h>
    #include <assert.h>
    #include  "Grammar.h"
    #include  "FXParser.h"
    #define MAX_STR_CONST 16382 // TODO: Change this and make it dynamic... shaders could be big

    namespace nvFX
    {
        extern IncludeCb g_includeCb;
    }
    int  line_num  =  1;
    std::string file_name;
	int  bracket_level = 0;
	char  *string_buf_ptr;
    //#define  MAX_INCLUDE_DEPTH  10
    //YY_BUFFER_STATE  include_stack[MAX_INCLUDE_DEPTH];
    //int  include_stack_ptr  =  0;
    struct IncludeData {
        IncludeData(YY_BUFFER_STATE s, int ln, const char *fname, FILE *fd=NULL) :
            state(s), line_num(ln), file_name(fname), fileToClose(fd) {}
        YY_BUFFER_STATE state;
        int             line_num;
        std::string     file_name; // the name of the current file (when in #include, for example)
        FILE*           fileToClose; // keep track of the file descriptor to make sure we will close it
    };
    std::stack<IncludeData> include_stack;

    // we need to do this because yy_pop_state is generated as static
    static void yy_pop_state();
    void lex_pop_state()
    {
        yy_pop_state();
    }
%}
%option stack
%x fbo fbo1 clearmode rendermode incl comment comment2 str shader shaderbody cstbuffer technique pass sampler_state dst_state color_sample_state rasterization_state resource resource1
DIGIT       [0-9]
HEXNUM       0x[0-9a-fA-F]+
VARIABLE    [a-zA-Z_]+[\.a-zA-Z\-_0-9]*
%%
	int  comment_caller;
	char  string_buf[MAX_STR_CONST];

<shader,fbo1,resource1>{
    global return GLOBAL;
    local return LOCAL;
}
    /*==================================================================
      FBO
    */
FBO {
    bracket_level = 0;
    yy_push_state(fbo1);
    return FBO;
}
    /*==================================================================
      Texture for scene-level effect : RenderTexture and RenderBuffer
      They share the same as Texture : they are resources
    */
RenderTexture {
    bracket_level = 0;
    yy_push_state(resource1);
    return RENDERTEXTURE;
}
RenderTextureRect(angle)? {
    bracket_level = 0;
    yy_push_state(resource1);
    return RENDERTEXTURERECT;
}
RenderBuffer {
    bracket_level = 0;
    yy_push_state(resource1);
    return RENDERBUFFER;
}
    /*==================================================================
      
    */
Texture {
    bracket_level = 0;
	yy_push_state(resource1);
    return TEXTURE;
}
TextureCube {
    bracket_level = 0;
    yy_push_state(resource1);
    return TEXTURECUBE;
}
Texture1D {
    bracket_level = 0;
    yy_push_state(resource1);
    return TEXTURE1D;
}
Texture2D {
    bracket_level = 0;
    yy_push_state(resource1);
    return TEXTURE2D;
}
Texture3D {
    bracket_level = 0;
    yy_push_state(resource1);
    return TEXTURE3D;
}
TextureRect(angle)? {
    bracket_level = 0;
    yy_push_state(resource1);
    return TEXTURERECT;
}
GLSLSHADER {
	comment_caller  =  INITIAL;
    bracket_level = 0;
    yy_push_state(shader);
    return GLSLSHADER;
}
HLSL10SHADER {
    comment_caller  =  INITIAL;
    bracket_level = 0;
    yy_push_state(shader);
    return HLSL10SHADER;
}
HLSL11SHADER {
    comment_caller  =  INITIAL;
    bracket_level = 0;
    yy_push_state(shader);
    return HLSL11SHADER;
}
CGSHADER {
	comment_caller  =  INITIAL;
    bracket_level = 0;
    yy_push_state(shader);
    return CGSHADER;
}
SAMPLER(_)*STATE {
	yy_push_state(sampler_state);
    return SAMPLER_STATE;
}
DepthStencilState {
    yy_push_state(dst_state);
    return DST_STATE;
}
dst(_)*state {
	yy_push_state(dst_state);
    return DST_STATE;
}
BlendState {
    yy_push_state(color_sample_state);
    return COLOR_SAMPLE_STATE;
}
color(_)*sample(_)*state {
	yy_push_state(color_sample_state);
    return COLOR_SAMPLE_STATE;
}
RasterizerState {
    yy_push_state(rasterization_state);
    return RASTERIZATION_STATE;
}
rasterization(_)*state {
	yy_push_state(rasterization_state);
    return RASTERIZATION_STATE;
}
TECHNIQUE {
	yy_push_state(technique);
    return TECHNIQUE;
}
    /*
    Arbitrary Group of uniforms... TO REMOVE
    */
UniformGroup {
    yy_push_state(cstbuffer);
    return UNIFORM_GROUP;
}
    /*
    Constant Buffer
    */
C(st)*Buffer {
    yy_push_state(cstbuffer);
    return CSTBUFFER;
}
<INITIAL,cstbuffer>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();
        return yytext[0];
    }
    float  return FLOAT_TYPE;
    float2 return FLOAT2_TYPE;
    float3 return FLOAT3_TYPE;
    float4 return FLOAT4_TYPE;
    vec2   return FLOAT2_TYPE;
    vec3   return FLOAT3_TYPE;
    vec4   return FLOAT4_TYPE;
    mat2   return MAT2_TYPE;
    mat3   return MAT3_TYPE;
    mat4   return MAT4_TYPE;
    float2x2   return MAT2_TYPE;
    float3x3   return MAT3_TYPE;
    float4x4   return MAT4_TYPE;
    bool   return BOOL_TYPE;
    bvec2  return BOOL2_TYPE;
    bvec3  return BOOL3_TYPE;
    bvec4  return BOOL4_TYPE;
    int    return INT_TYPE;
    int2   return INT2_TYPE;
    int3   return INT3_TYPE;
    int4   return INT4_TYPE;
    ivec2  return INT2_TYPE;
    ivec3  return INT3_TYPE;
    ivec4  return INT4_TYPE;
    uniform return UNIFORM;
}
    /*==================================================================
      Float/double values
    */
<INITIAL,cstbuffer,technique,sampler_state,dst_state,color_sample_state,rasterization_state,pass,resource>{
    {DIGIT}+ {
        yylval.ival = atoi(yytext);
        return FX_INT;
    }
    {HEXNUM} {
        sscanf(yytext, "0x%x", &yylval.ival);
        return FX_INT;
    }
{DIGIT}+"."{DIGIT}*f? {
        yylval.fval = (float)atof(yytext);
        return FX_FLOAT;
    }
}
    /*==================================================================
      Boolean
    */
<INITIAL,cstbuffer,technique,sampler_state,dst_state,color_sample_state,rasterization_state,pass,resource>{
    (GL)*(_)*TRUE return FX_TRUE;
    (GL)*(_)*FALSE return FX_FALSE;
}
    /*==================================================================
      OpenGL Enums
    */
<sampler_state,dst_state,color_sample_state,rasterization_state,pass,resource>{
    (GL)*(_)*ACCUM yylval.glenum=GLACCUM; return GLACCUM;
    (GL)*(_)*LOAD yylval.glenum=GLLOAD; return GLLOAD;
    (GL)*(_)*RETURN yylval.glenum=GLRETURN; return GLRETURN;
    (GL)*(_)*MULT yylval.glenum=GLMULT; return GLMULT;
    (GL)*(_)*ADD yylval.glenum=GLADD; return GLADD;
    (GL)*(_)*NEVER yylval.glenum=GLNEVER; return GLNEVER;
    (GL)*(_)*LESS yylval.glenum=GLLESS; return GLLESS;
    (GL)*(_)*EQUAL yylval.glenum=GLEQUAL; return GLEQUAL;
    (GL)*(_)*GREATER yylval.glenum=GLGREATER; return GLGREATER;
    (GL)*(_)*NOTEQUAL yylval.glenum=GLNOTEQUAL; return GLNOTEQUAL;
    (GL)*(_)*ALWAYS yylval.glenum=GLALWAYS; return GLALWAYS;
    (GL)*(_)*LEQUAL yylval.glenum=GLLEQUAL; return GLLEQUAL;
    (GL)*(_)*GEQUAL yylval.glenum=GLGEQUAL; return GLGEQUAL;
    (GL)*(_)*KEEP yylval.glenum=GLKEEP; return GLKEEP;
    (GL)*(_)*UPPER(_)*LEFT yylval.glenum=GLUPPERLEFT; return GLUPPERLEFT;
    (GL)*(_)*LOWER(_)*LEFT yylval.glenum=GLLOWERLEFT; return GLLOWERLEFT;
    (GL)*(_)*FRONT(_)*LEFT yylval.glenum=GLFRONTLEFT; return GLFRONTLEFT;
    (GL)*(_)*FRONT(_)*RIGHT yylval.glenum=GLFRONTRIGHT; return GLFRONTRIGHT;
    (GL)*(_)*BACK(_)*LEFT yylval.glenum=GLBACKLEFT; return GLBACKLEFT;
    (GL)*(_)*BACK(_)*RIGHT yylval.glenum=GLBACKRIGHT; return GLBACKRIGHT;
    (GL)*(_)*FRONT yylval.glenum=GLFRONT; return GLFRONT;
    (GL)*(_)*BACK yylval.glenum=GLBACK; return GLBACK;
    (GL)*(_)*LEFT yylval.glenum=GLLEFT; return GLLEFT;
    (GL)*(_)*RIGHT yylval.glenum=GLRIGHT; return GLRIGHT;
    (GL)*(_)*FRONT(_)*AND(_)*BACK yylval.glenum=GLFRONTANDBACK; return GLFRONTANDBACK;
    (GL)*(_)*CCW yylval.glenum=GLCCW; return GLCCW;
    (GL)*(_)*CW yylval.glenum=GLCCW; return GLCCW;
    (GL)*(_)*POINT yylval.glenum=GLPOINT; return GLPOINT;
    (GL)*(_)*LINE yylval.glenum=GLLINE; return GLLINE;
    (GL)*(_)*FILL yylval.glenum=GLFILL; return GLFILL;
    (GL)*(_)*ZERO yylval.glenum=GLZERO; return GLZERO;
    (GL)*(_)*ONE yylval.glenum=GLONE; return GLONE;
    (GL)*(_)*SRC(_)*COLOR yylval.glenum=GLSRCCOLOR; return GLSRCCOLOR;
    (GL)*(_)*ONE(_)*MINUS(_)*SRC(_)*COLOR yylval.glenum=GLONEMINUSSRCCOLOR; return GLONEMINUSSRCCOLOR;
    (GL)*(_)*SRC(_)*ALPHA yylval.glenum=GLSRCALPHA; return GLSRCALPHA;
    (GL)*(_)*ONE(_)*MINUS(_)*SRC(_)*ALPHA yylval.glenum=GLONEMINUSSRCALPHA; return GLONEMINUSSRCALPHA;
    (GL)*(_)*DST(_)*ALPHA yylval.glenum=GLDSTALPHA; return GLDSTALPHA;
    (GL)*(_)*ONE(_)*MINUS(_)*DST(_)*ALPHA yylval.glenum=GLONEMINUSDSTALPHA; return GLONEMINUSDSTALPHA;
    (GL)*(_)*DST(_)*COLOR yylval.glenum=GLDSTCOLOR; return GLDSTCOLOR;
    (GL)*(_)*ONE(_)*MINUS(_)*DST(_)*COLOR yylval.glenum=GLONEMINUSDSTCOLOR; return GLONEMINUSDSTCOLOR;
    (GL)*(_)*SRC(_)*ALPHA(_)*SATURATE yylval.glenum=GLSRCALPHASATURATE; return GLSRCALPHASATURATE;
    (GL)*(_)*CONSTANT(_)*COLOR yylval.glenum=GLCONSTANTCOLOR; return GLCONSTANTCOLOR;
    (GL)*(_)*ONE(_)*MINUS(_)*CONSTANT(_)*COLOR yylval.glenum=GLONEMINUSCONSTANTCOLOR; return GLONEMINUSCONSTANTCOLOR;
    (GL)*(_)*CONSTANT(_)*ALPHA yylval.glenum=GLCONSTANTALPHA; return GLCONSTANTALPHA;
    (GL)*(_)*ONE(_)*MINUS(_)*CONSTANT(_)*ALPHA yylval.glenum=GLONEMINUSCONSTANTALPHA; return GLONEMINUSCONSTANTALPHA;
    (GL)*(_)*BLEND(_)*COLOR yylval.glenum=GLBLENDCOLOR; return GLBLENDCOLOR;
    (GL)*(_)*FUNC(_)*ADD yylval.glenum=GLFUNCADD; return GLFUNCADD;
    (GL)*(_)*MIN yylval.glenum=GLMIN; return GLMIN;
    (GL)*(_)*MAX yylval.glenum=GLMAX; return GLMAX;
    (GL)*(_)*FUNC(_)*SUBTRACT yylval.glenum=GLFUNCSUBTRACT; return GLFUNCSUBTRACT;
    (GL)*(_)*FUNC(_)*REVERSE(_)*SUBTRACT yylval.glenum=GLFUNCREVERSESUBTRACT; return GLFUNCREVERSESUBTRACT;
    (GL)*(_)*CLEAR yylval.glenum=GLCLEAR; return GLCLEAR;
    (GL)*(_)*SET yylval.glenum=GLSET; return GLSET;
    (GL)*(_)*COPY yylval.glenum=GLCOPY; return GLCOPY;
    (GL)*(_)*COPY(_)*INVERTED yylval.glenum=GLCOPYINVERTED; return GLCOPYINVERTED;
    (GL)*(_)*NOOP yylval.glenum=GLNOOP; return GLNOOP;
    (GL)*(_)*INVERT yylval.glenum=GLINVERT; return GLINVERT;
    (GL)*(_)*AND yylval.glenum=GLAND; return GLAND;
    (GL)*(_)*NAND yylval.glenum=GLNAND; return GLNAND;
    (GL)*(_)*OR yylval.glenum=GLOR; return GLOR;
    (GL)*(_)*NOR yylval.glenum=GLNOR; return GLNOR;
    (GL)*(_)*XOR yylval.glenum=GLXOR; return GLXOR;
    (GL)*(_)*EQUIV yylval.glenum=GLEQUIV; return GLEQUIV;
    (GL)*(_)*AND(_)*REVERSE yylval.glenum=GLANDREVERSE; return GLANDREVERSE;
    (GL)*(_)*AND(_)*INVERTED yylval.glenum=GLANDINVERTED; return GLANDINVERTED;
    (GL)*(_)*OR(_)*REVERSE yylval.glenum=GLORREVERSE; return GLORREVERSE;
    (GL)*(_)*OR(_)*INVERTED yylval.glenum=GLORINVERTED; return GLORINVERTED;
}
<pass,rasterization_state>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();
        return yytext[0];
    }
    (GL)*(_)*POINT(_)*SIZE yylval.glenum=GLPOINTSIZE; return GLPOINTSIZE;
    (GL)*(_)*POINT(_)*SMOOTH yylval.glenum=GLPOINTSMOOTH; return GLPOINTSMOOTH;
    (GL)*(_)*POINT(_)*SPRITE yylval.glenum=GLPOINTSPRITE; return GLPOINTSPRITE;
    (GL)*(_)*POINT(_)*SPRITE(_)*COORD(_)*ORIGIN yylval.glenum=GLPOINTSPRITECOORDORIGIN; return GLPOINTSPRITECOORDORIGIN;
    (GL)*(_)*LINE(_)*WIDTH yylval.glenum=GLLINEWIDTH; return GLLINEWIDTH;
    (GL)*(_)*LINE(_)*SMOOTH yylval.glenum=GLLINESMOOTH; return GLLINESMOOTH;
    /*(GL)*(_)*COMBINED(_)*LINE(_)*STIPPLE(_)*NV yylval.glenum=GLCOMBINEDLINESTIPPLENV; return GLCOMBINEDLINESTIPPLENV;*/
    (GL)*(_)*LINE(_)*STIPPLE(_)*PATTERN yylval.glenum=GLLINESTIPPLEPATTERN; return GLLINESTIPPLEPATTERN;
    (GL)*(_)*LINE(_)*STIPPLE(_)*REPEAT yylval.glenum=GLLINESTIPPLEREPEAT; return GLLINESTIPPLEREPEAT;
    (GL)*(_)*LINE(_)*STIPPLE yylval.glenum=GLLINESTIPPLE; return GLLINESTIPPLE;
    (GL)*(_)*CULL(_)*FACE yylval.glenum=GLCULLFACE; return GLCULLFACE;
    (GL)*(_)*CULL(_)*FACE(_)*MODE yylval.glenum=GLCULLFACEMODE; return GLCULLFACEMODE;
    (GL)*(_)*FRONT(_)*FACE yylval.glenum=GLFRONTFACE; return GLFRONTFACE;
    (GL)*(_)*POLYGON(_)*SMOOTH yylval.glenum=GLPOLYGONSMOOTH; return GLPOLYGONSMOOTH;
    (GL)*(_)*POLYGON(_)*MODE yylval.glenum=GLPOLYGONMODE; return GLPOLYGONMODE;
    (GL)*(_)*POLYGON(_)*OFFSET(_)*FACTOR yylval.glenum=GLPOLYGONOFFSETFACTOR; return GLPOLYGONOFFSETFACTOR;
    (GL)*(_)*POLYGON(_)*OFFSET(_)*UNITS yylval.glenum=GLPOLYGONOFFSETUNITS; return GLPOLYGONOFFSETUNITS;
    (GL)*(_)*POLYGON(_)*OFFSET(_)*POINT yylval.glenum=GLPOLYGONOFFSETPOINT; return GLPOLYGONOFFSETPOINT;
    (GL)*(_)*POLYGON(_)*OFFSET(_)*LINE yylval.glenum=GLPOLYGONOFFSETLINE; return GLPOLYGONOFFSETLINE;
    (GL)*(_)*POLYGON(_)*OFFSET(_)*FILL yylval.glenum=GLPOLYGONOFFSETFILL; return GLPOLYGONOFFSETFILL;
    (GL)*(_)*POLYGON(_)*STIPPLE(_)*BIT yylval.glenum=GLPOLYGONSTIPPLEBIT; return GLPOLYGONSTIPPLEBIT;
    (GL)*(_)*RASTERIZER(_)*DISCARD yylval.glenum=GLRASTERIZERDISCARD; return GLRASTERIZERDISCARD;
}
<pass,color_sample_state>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();
        return yytext[0];
    }
    (GL)*(_)*ALPHA(_)*TEST yylval.glenum=GLALPHATEST; return GLALPHATEST;
    (GL)*(_)*ALPHA(_)*TEST(_)*FUNC yylval.glenum=GLALPHATESTFUNC; return GLALPHATESTFUNC;
    (GL)*(_)*ALPHA(_)*TEST(_)*REF yylval.glenum=GLALPHATESTREF; return GLALPHATESTREF;
    (GL)*(_)*BLEND yylval.glenum=GLBLEND; return GLBLEND;
    (GL)*(_)*BLEND(_)*SRC yylval.glenum=GLBLENDSRC; return GLBLENDSRC;
    (GL)*(_)*BLEND(_)*SRC(_)*RGB yylval.glenum=GLBLENDSRCRGB; return GLBLENDSRCRGB;
    (GL)*(_)*BLEND(_)*SRC(_)*ALPHA yylval.glenum=GLBLENDSRCALPHA; return GLBLENDSRCALPHA;
    (GL)*(_)*BLEND(_)*DST yylval.glenum=GLBLENDDST; return GLBLENDDST;
    (GL)*(_)*BLEND(_)*DST(_)*RGB yylval.glenum=GLBLENDDSTRGB; return GLBLENDDSTRGB;
    (GL)*(_)*BLEND(_)*DST(_)*ALPHA yylval.glenum=GLBLENDDSTALPHA; return GLBLENDDSTALPHA;
    /*(GL)*(_)*BLEND(_)*EQUATION(_)*RGBA(_)*NV yylval.glenum=GLBLENDEQUATIONRGBANV; return GLBLENDEQUATIONRGBANV;*/
    (GL)*(_)*BLEND(_)*EQUATION(_)*RGB yylval.glenum=GLBLENDEQUATIONRGB; return GLBLENDEQUATIONRGB;
    (GL)*(_)*BLEND(_)*EQUATION(_)*ALPHA yylval.glenum=GLBLENDEQUATIONALPHA; return GLBLENDEQUATIONALPHA;
    /*(GL)*(_)*PER(_)*DRAW(_)*BUFFER(_)*BLEND(_)*FUNCTION(_)*NV yylval.glenum=GLPERDRAWBUFFERBLENDFUNCTIONNV; return GLPERDRAWBUFFERBLENDFUNCTIONNV;
    (GL)*(_)*PER(_)*DRAW(_)*BUFFER(_)*BLEND(_)*EQUATION(_)*NV yylval.glenum=GLPERDRAWBUFFERBLENDEQUATIONNV; return GLPERDRAWBUFFERBLENDEQUATIONNV;
    (GL)*(_)*PER(_)*DRAW(_)*BUFFER(_)*BLEND(_)*ENABLE(_)*NV yylval.glenum=GLPERDRAWBUFFERBLENDENABLENV; return GLPERDRAWBUFFERBLENDENABLENV;
    (GL)*(_)*PER(_)*DRAW(_)*BUFFER(_)*COLOR(_)*WRITEMASK(_)*NV yylval.glenum=GLPERDRAWBUFFERCOLORWRITEMASKNV; return GLPERDRAWBUFFERCOLORWRITEMASKNV;*/
    (GL)*(_)*BLEND(_)*COLOR yylval.glenum=GLBLENDCOLOR; return GLBLENDCOLOR;
    (GL)*(_)*FRAMEBUFFER(_)*SRGB yylval.glenum=GLFRAMEBUFFERSRGB; return GLFRAMEBUFFERSRGB;
    (GL)*(_)*DITHER yylval.glenum=GLDITHER; return GLDITHER;
    (GL)*(_)*COLOR(_)*LOGIC(_)*OP yylval.glenum=GLCOLORLOGICOP; return GLCOLORLOGICOP;
    (GL)*(_)*LOGIC(_)*OP(_)*MODE yylval.glenum=GLLOGICOPMODE; return GLLOGICOPMODE;
    (GL)*(_)*COLOR(_)*WRITEMASK yylval.glenum=GLCOLORWRITEMASK; return GLCOLORWRITEMASK;
    (GL)*(_)*MULTISAMPLE yylval.glenum=GLMULTISAMPLE; return GLMULTISAMPLE;
    (GL)*(_)*SAMPLE(_)*MASK yylval.glenum=GLSAMPLEMASK; return GLSAMPLEMASK;
    (GL)*(_)*SAMPLE(_)*MASK(_)*VALUE yylval.glenum=GLSAMPLEMASKVALUE; return GLSAMPLEMASKVALUE;
    (GL)*(_)*SAMPLE(_)*ALPHA(_)*TO(_)*ONE yylval.glenum=GLSAMPLEALPHATOONE; return GLSAMPLEALPHATOONE;
    (GL)*(_)*SAMPLE(_)*ALPHA(_)*TO(_)*COVERAGE yylval.glenum=GLSAMPLEALPHATOCOVERAGE; return GLSAMPLEALPHATOCOVERAGE;
}
<pass,dst_state>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();
        return yytext[0];
    }
    (GL)*(_)*DEPTH(_)*TEST yylval.glenum=GLDEPTHTEST; return GLDEPTHTEST;
    (GL)*(_)*DEPTH(_)*FUNC yylval.glenum=GLDEPTHFUNC; return GLDEPTHFUNC;
    (GL)*(_)*DEPTH(_)*WRITEMASK yylval.glenum=GLDEPTHWRITEMASK; return GLDEPTHWRITEMASK;
    (GL)*(_)*DEPTH(_)*CLAMP yylval.glenum=GLDEPTHCLAMP; return GLDEPTHCLAMP;
    (GL)*(_)*DEPTH(_)*BOUNDS(_)*TEST(_)*EXT yylval.glenum=GLDEPTHBOUNDSTESTEXT; return GLDEPTHBOUNDSTESTEXT;
    (GL)*(_)*DEPTH(_)*BOUNDS(_)*EXT yylval.glenum=GLDEPTHBOUNDSEXT; return GLDEPTHBOUNDSEXT;
    (GL)*(_)*STENCIL(_)*TEST yylval.glenum=GLSTENCILTEST; return GLSTENCILTEST;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*FUNC yylval.glenum=GLSTENCILFUNC; return GLSTENCILFUNC;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*VALUE(_)*MASK yylval.glenum=GLSTENCILVALUEMASK; return GLSTENCILVALUEMASK;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*REF yylval.glenum=GLSTENCILREF; return GLSTENCILREF;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*FAIL yylval.glenum=GLSTENCILFAIL; return GLSTENCILFAIL;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*PASS(_)*DEPTH(_)*FAIL yylval.glenum=GLSTENCILPASSDEPTHFAIL; return GLSTENCILPASSDEPTHFAIL;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*PASS(_)*DEPTH(_)*PASS yylval.glenum=GLSTENCILPASSDEPTHPASS; return GLSTENCILPASSDEPTHPASS;
    (GL)*(_)*STENCIL(_)*(FRONT)*(_)*WRITEMASK yylval.glenum=GLSTENCILWRITEMASK; return GLSTENCILWRITEMASK;
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*FUNC yylval.glenum=GLSTENCILFRONTFUNC; return GLSTENCILFRONTFUNC;*/
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*VALUE(_)*MASK yylval.glenum=GLSTENCILFRONTVALUEMASK; return GLSTENCILFRONTVALUEMASK;*/
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*REF yylval.glenum=GLSTENCILFRONTREF; return GLSTENCILFRONTREF;*/
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*FAIL yylval.glenum=GLSTENCILFRONTFAIL; return GLSTENCILFRONTFAIL;*/
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*PASS(_)*DEPTH(_)*FAIL yylval.glenum=GLSTENCILFRONTPASSDEPTHFAIL; return GLSTENCILFRONTPASSDEPTHFAIL;*/
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*PASS(_)*DEPTH(_)*PASS yylval.glenum=GLSTENCILFRONTPASSDEPTHPASS; return GLSTENCILFRONTPASSDEPTHPASS;*/
    /*(GL)*(_)*STENCIL(_)*FRONT(_)*WRITEMASK yylval.glenum=GLSTENCILFRONTWRITEMASK; return GLSTENCILFRONTWRITEMASK;*/
    (GL)*(_)*STENCIL(_)*BACK(_)*FUNC yylval.glenum=GLSTENCILBACKFUNC; return GLSTENCILBACKFUNC;
    (GL)*(_)*STENCIL(_)*BACK(_)*VALUE(_)*MASK yylval.glenum=GLSTENCILBACKVALUEMASK; return GLSTENCILBACKVALUEMASK;
    (GL)*(_)*STENCIL(_)*BACK(_)*REF yylval.glenum=GLSTENCILBACKREF; return GLSTENCILBACKREF;
    (GL)*(_)*STENCIL(_)*BACK(_)*FAIL yylval.glenum=GLSTENCILBACKFAIL; return GLSTENCILBACKFAIL;
    (GL)*(_)*STENCIL(_)*BACK(_)*PASS(_)*DEPTH(_)*FAIL yylval.glenum=GLSTENCILBACKPASSDEPTHFAIL; return GLSTENCILBACKPASSDEPTHFAIL;
    (GL)*(_)*STENCIL(_)*BACK(_)*PASS(_)*DEPTH(_)*PASS yylval.glenum=GLSTENCILBACKPASSDEPTHPASS; return GLSTENCILBACKPASSDEPTHPASS;
    (GL)*(_)*STENCIL(_)*BACK(_)*WRITEMASK yylval.glenum=GLSTENCILBACKWRITEMASK; return GLSTENCILBACKWRITEMASK;
}
    /*==================================================================
      Start of string
    */
<INITIAL,resource,pass,technique,cstbuffer>
{
    \"	string_buf_ptr  =  string_buf;  yy_push_state(str);
}
    /*==================================================================
      fallback for any other character : sent as a token ID
    */
    /*. return yytext[0];*/

    /*==================================================================
      Comment starting points
    */
<INITIAL,str,shader,cstbuffer,technique,pass,sampler_state,dst_state,color_sample_state,rasterization_state,resource,resource1,fbo,fbo1>"/*" {
	comment_caller  =  INITIAL;
	yy_push_state(comment);
}

<INITIAL,str,shader,cstbuffer,technique,pass,sampler_state,dst_state,color_sample_state,rasterization_state,resource,resource1,fbo,fbo1>"//" {
	comment_caller  =  INITIAL;
	yy_push_state(comment2);
}

<comment>{
    [^*\n]* /*  eat  anything  that's  not  a  '*'  */
    "*"+[^*/\n]*     /*  eat  up  '*'s  not  followed  by  '/'s  */
    \n ++line_num;
    "*"+"/" yy_pop_state();//BEGIN(comment_caller);
}

<comment2>{
    .*
    \n ++line_num;  yy_pop_state();//BEGIN(comment_caller);
}

    /*==================================================================
      rules for inside a string
    */
<str>{
    \"	{  /*  saw  closing  quote  -  all  done  */
    	yy_pop_state();//BEGIN(INITIAL);
	    *string_buf_ptr  =  '\0';
        yylval.s = new std::string(string_buf);
        return FX_STR;
    }
    \n	{
	    fprintf(stderr,"\nunterminated  string  constant at line %d\n", line_num);
        yyterminate();
    }
    \\[0-7]{1,3}	{
	    /*  octal  escape  sequence  */
	    int  result;
	    (void)  sscanf(  yytext  +  1,  "%o",  &result  );
	    if  (  result  >  0xff  )
		    /*  error,  constant  is  out-of-bounds  */
	    *string_buf_ptr++  =  result;
    }
    \\[0-9]+	{
	    /*  generate  error  -  bad  escape  sequence;  something
	    *  like  '\48'  or  '\0777777'
	    */
    }
    \\n    *string_buf_ptr++  =  '\n';
    \\t    *string_buf_ptr++  =  '\t';
    \\r    *string_buf_ptr++  =  '\r';
    \\b    *string_buf_ptr++  =  '\b';
    \\f    *string_buf_ptr++  =  '\f';
    \\(.|\n)    *string_buf_ptr++  =  yytext[1];
    [^\\\n\"]+ {
	    char  *yptr  =  yytext;
	    while  (  *yptr  )
	    *string_buf_ptr++  =  *yptr++;
    }
}

    /*==================================================================
      rules for inside a GLSL section
    */
<shader>{
    \{  {
        bracket_level = 1; // must be one...
        string_buf_ptr  =  string_buf;
        *string_buf_ptr = '\0';
        yy_push_state(shaderbody);
        return yytext[0];
    }
    {VARIABLE} {
        // TODO create and REGISTER the variable in a table
        yylval.s = new std::string(yytext);
        return VARNAME;
    }
}
<shaderbody>{
    \{  {
        bracket_level++;
        *string_buf_ptr++  =  yytext[0];
    }
    \} {
        bracket_level--;
        if((bracket_level) == 0)
        {
	        *string_buf_ptr  =  '\0';
            yylval.s = new std::string(string_buf);
            // shall I just do BEGIN(INITIAL) ?
            yy_pop_state(); // back to shader
            yy_pop_state();// back to INITIAL
            return CODEBODY;
        } else {
	        *string_buf_ptr++  =  yytext[0];
        }
    }
    \n {  /*copy the GLSL data*/
        char  *yptr  =  yytext;
        while  (  *yptr  )
        *string_buf_ptr++  =  *yptr++;
        ++line_num; 
    }
    [^\n^\{^\}]+ {  /*copy the GLSL data*/
        char  *yptr  =  yytext;
        while  (  *yptr  )
        *string_buf_ptr++  =  *yptr++;
    }
}
    /*==================================================================
      rules for inside a  section
    */
<technique>{
    Pass {
	    comment_caller  =  INITIAL;
	    yy_push_state(pass);
        return PASS;
    }
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();//BEGIN(INITIAL);
        return yytext[0];
    }
    Technique return TECHNIQUE;
    OFF return OFF;
}
    /*==================================================================
      rules for inside a  section
    */
<pass>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();
        return yytext[0];
    }
    VertexProgram       return VERTEXSHADER;
    VertexShader        return VERTEXSHADER;
    FragmentProgram     return FRAGMENTSHADER;
    FragmentShader      return FRAGMENTSHADER;
    PixelShader         return FRAGMENTSHADER;
    GeometryProgram     return GEOMETRYSHADER;
    GeometryShader      return GEOMETRYSHADER;
    HullShader          return HULLSHADER;
    EvalShader          return EVALSHADER;

    VertexProgramOverride   return VERTEXSHADEROVERRIDE;
    VertexShaderOverride    return VERTEXSHADEROVERRIDE;
    FragmentProgramOverride return FRAGMENTSHADEROVERRIDE;
    FragmentShaderOverride  return FRAGMENTSHADEROVERRIDE;
    PixelShaderOverride     return FRAGMENTSHADEROVERRIDE;
    GeometryProgramOverride return GEOMETRYSHADEROVERRIDE;
    GeometryShaderOverride  return GEOMETRYSHADEROVERRIDE;
    HullShaderOverride      return HULLSHADEROVERRIDE;
    EvalShaderOverride      return EVALSHADEROVERRIDE;

    PROFILE                   return SHDPROFILE;
    (SET)*SAMPLERRESOURCE       return SAMPLERRESOURCE;
    (SET)*SAMPLERTEXUNIT        return SAMPLERTEXUNIT;
    (SET)*SAMPLERSTATE          return SETSAMPLERSTATE;
    (SET)*DST(_)*(STATE)*           return SETDSTSTATE;
    (SET)*RASTERIZATION(_)*(STATE)* return SETRASTERIZATIONSTATE;
    (SET)*COLOR(_)*SAMPLE(_)*(STATE)*   return SETCOLORSAMPLESTATE;

    ClearMode {
        yy_push_state(clearmode);
        return CLEARMODE;
    }
    RenderMode {
        yy_push_state(rendermode);
        return RENDERMODE;
    }
    RenderGroup             return RENDERGROUP;
    BlitFBOToActiveTarget   return BLITFBOTOACTIVETARGET;
    ClearColor              return CLEARCOLOR;
    CurrentTarget           return CURRENTTARGET;
    Viewport                return VIEWPORT;
    SwapResources           return SWAPRESOURCES;

    Loop                    return LOOP;
    Active                  return ACTIVE;
}
<clearmode>{
    \= return '=';
    none { yy_pop_state(); yylval.clear_mode = nvFX::Clear_none; return CLEAR_ENUM; }
    all { yy_pop_state(); yylval.clear_mode = nvFX::Clear_all; return CLEAR_ENUM; }
    color_depth { yy_pop_state(); yylval.clear_mode = nvFX::Clear_color_depth; return CLEAR_ENUM; }
    color { yy_pop_state(); yylval.clear_mode = nvFX::Clear_color; return CLEAR_ENUM; }
    depth { yy_pop_state(); yylval.clear_mode = nvFX::Clear_depth; return CLEAR_ENUM; }
    stencil { yy_pop_state(); yylval.clear_mode = nvFX::Clear_stencil; return CLEAR_ENUM; }
    depth_stencil { yy_pop_state(); yylval.clear_mode = nvFX::Clear_depth_stencil; return CLEAR_ENUM; }
}
<rendermode>{
    \= return '=';
    render_scenegraph_shaded { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_SHADED; return RENDERMODE_ENUM; }
    render_scenegraph_noshading { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_NOSHADING; return RENDERMODE_ENUM; }
    render_fullscreen_quad { yy_pop_state(); yylval.render_mode = nvFX::RENDER_FULLSCREEN_QUAD;return RENDERMODE_ENUM; }
    render_scenegraph_shaded_opaque_only { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_SHADED_OPAQUE_ONLY;return RENDERMODE_ENUM; }
    render_scenegraph_shaded_transparent_only { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_SHADED_TRANSPARENT_ONLY;return RENDERMODE_ENUM; }
    render_scenegraph_noshading_opaque_only { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_NOSHADING_OPAQUE_ONLY;return RENDERMODE_ENUM; }
    render_scenegraph_noshading_transparent_only { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_NOSHADING_TRANSPARENT_ONLY;return RENDERMODE_ENUM; }
    render_scenegraph_outlines_only { yy_pop_state(); yylval.render_mode = nvFX::RENDER_SCENEGRAPH_OUTLINES_ONLY;return RENDERMODE_ENUM; }
    render_debug_quad0 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_DEBUG_QUAD0;return RENDERMODE_ENUM; }
    render_debug_quad1 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_DEBUG_QUAD1;return RENDERMODE_ENUM; }
    render_debug_quad2 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_DEBUG_QUAD2;return RENDERMODE_ENUM; }
    render_debug_quad3 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_DEBUG_QUAD3;return RENDERMODE_ENUM; }
    render_debug_scene { yy_pop_state(); yylval.render_mode = nvFX::RENDER_DEBUG_SCENE;return RENDERMODE_ENUM; }
    render_debug_scene_lines { yy_pop_state(); yylval.render_mode = nvFX::RENDER_DEBUG_SCENE_LINES;return RENDERMODE_ENUM; }
    do_nothing { yy_pop_state(); yylval.render_mode = nvFX::DO_NOTHING;return RENDERMODE_ENUM; }
    render_optix_reflection { yy_pop_state(); yylval.render_mode = nvFX::RENDER_OPTIX_REFLECTION;return RENDERMODE_ENUM; }
    render_optix_shadow { yy_pop_state(); yylval.render_mode = nvFX::RENDER_OPTIX_SHADOW;return RENDERMODE_ENUM; }
    render_optix_reflection_and_shadow { yy_pop_state(); yylval.render_mode = nvFX::RENDER_OPTIX_REFLECTION_AND_SHADOW;return RENDERMODE_ENUM; }
    render_optix { yy_pop_state(); yylval.render_mode = nvFX::RENDER_OPTIX;return RENDERMODE_ENUM; }
    run_cuda { yy_pop_state(); yylval.render_mode = nvFX::RUN_CUDA;return RENDERMODE_ENUM; }
    render_custom0 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM0;return RENDERMODE_ENUM; }
    render_custom1 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM1;return RENDERMODE_ENUM; }
    render_custom2 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM2;return RENDERMODE_ENUM; }
    render_custom3 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM3;return RENDERMODE_ENUM; }
    render_custom4 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM4;return RENDERMODE_ENUM; }
    render_custom5 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM5;return RENDERMODE_ENUM; }
    render_custom6 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM6;return RENDERMODE_ENUM; }
    render_custom7 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM7;return RENDERMODE_ENUM; }
    render_custom8 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM8;return RENDERMODE_ENUM; }
    render_custom9 { yy_pop_state(); yylval.render_mode = nvFX::RENDER_CUSTOM9;return RENDERMODE_ENUM; }
}
<pass,technique>{
    Attribute           return ATTRIBUTE;
}
    /*==================================================================
      rules for inside a  FBO section 
    */
<fbo1>{
    \{  {
        yy_push_state(fbo); //leads to 'fbo' (fbo1 is a fast transition part)
        return yytext[0];
    }
    ; {
        yy_pop_state();
        return yytext[0];
    }
}
    /*==================================================================
      rules for inside a  FBO section 
    */
<fbo>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state(); // back to resource1
        //yy_pop_state(); // back to the one before resource1
        return yytext[0];
    }
    Color        return COLORTARGETS;
    Dst          return DSTTARGET;
}
    /*==================================================================
      rules for inside a  texture section 
    */
<resource1>{
    \{  {
        yy_push_state(resource); //leads to resource' (resource1 is a fast transition part)
        return yytext[0];
    }
    ; {
        yy_pop_state();
        return yytext[0];
    }
}
    /*==================================================================
      rules for inside a  texture section 
    */
<resource>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state(); // back to resource1
        //yy_pop_state(); // back to the one before resource1
        return yytext[0];
    }
    (SET)*SAMPLERSTATE        return SETSAMPLERSTATE;
    (SET)*RESOURCE      return SETRESOURCE;
    App(lication)?Defined          return APPDEFINED;
    Default             return APPDEFINED;
    MSAA                return RESOURCEMSAA;
    Format              return RESOURCEFORMAT;
    Size                return RESOURCESIZE;
    SizeFactor          return RESOURCESIZEFACTOR;
    ResolveTarget       return RESOURCERESOLVETARGET;
    AppDefined          return APPDEFINED;
    RGBA8               yylval.resource_format = FMT_RGBA8; return RESOURCEFORMAT_ENUM;
    RGBA16F             yylval.resource_format = FMT_RGBA16F; return RESOURCEFORMAT_ENUM;
    RGBA32F             yylval.resource_format = FMT_RGBA32F; return RESOURCEFORMAT_ENUM;
    INTENSITY8          yylval.resource_format = FMT_INTENSITY8; return RESOURCEFORMAT_ENUM;
    INTENSITY16F        yylval.resource_format = FMT_INTENSITY16F; return RESOURCEFORMAT_ENUM;
    INTENSITY32F        yylval.resource_format = FMT_INTENSITY32F; return RESOURCEFORMAT_ENUM;
    LUMINANCE_ALPHA8    yylval.resource_format = FMT_LUMINANCE_ALPHA8; return RESOURCEFORMAT_ENUM;
    RG16F_NV            yylval.resource_format = FMT_RG16F_NV; return RESOURCEFORMAT_ENUM;
    LUMINANCE_ALPHA16F  yylval.resource_format = FMT_LUMINANCE_ALPHA16F; return RESOURCEFORMAT_ENUM;
    LUMINANCE_ALPHA32F  yylval.resource_format = FMT_LUMINANCE_ALPHA32F; return RESOURCEFORMAT_ENUM;
    RG32F_NV            yylval.resource_format = FMT_RG32F_NV; return RESOURCEFORMAT_ENUM;
    RGB8                yylval.resource_format = FMT_RGB8; return RESOURCEFORMAT_ENUM;
    RGB16F              yylval.resource_format = FMT_RGB16F; return RESOURCEFORMAT_ENUM;
    RGB32F              yylval.resource_format = FMT_RGB32F; return RESOURCEFORMAT_ENUM;
    RGBA32F             yylval.resource_format = FMT_RGBA32F; return RESOURCEFORMAT_ENUM;
    DEPTH24STENCIL8     yylval.resource_format = FMT_DEPTH24STENCIL8; return RESOURCEFORMAT_ENUM;
    DEPTH_COMPONENT32F  yylval.resource_format = FMT_DEPTH_COMPONENT32F; return RESOURCEFORMAT_ENUM;
    DEPTH32F_STENCIL8   yylval.resource_format = FMT_DEPTH32F_STENCIL8; return RESOURCEFORMAT_ENUM;
    RGBA8UI             yylval.resource_format = FMT_RGBA8UI; return RESOURCEFORMAT_ENUM;
    Depth24Stencil8     yylval.resource_format = FMT_DEPTH24STENCIL8; return RESOURCEFORMAT_ENUM;
    FLOAT_RGBA16_NV     yylval.resource_format = FMT_FLOATRGBA16NV; return RESOURCEFORMAT_ENUM;
}
    /*==================================================================
      rules for inside a  section
    */
<sampler_state>{
    \{  {
        return yytext[0];
    }
    \} {
        //yy_pop_state();
        return yytext[0];
    }
    (GL)*(_)*(TEXTURE_)*MIN_FILTER    yylval.glenum=GLTEXTUREMINFILTER; return GLTEXTUREMINFILTER;
    (GL)*(_)*(TEXTURE_)*MAG_FILTER    yylval.glenum=GLTEXTUREMAGFILTER; return GLTEXTUREMAGFILTER;
    (GL)*(_)*(TEXTURE_)*WRAP_S        yylval.glenum=GLTEXTUREWRAPS; return GLTEXTUREWRAPS;
    (GL)*(_)*(TEXTURE_)*WRAP_T        yylval.glenum=GLTEXTUREWRAPT; return GLTEXTUREWRAPT;
    (GL)*(_)*(TEXTURE_)*WRAP_R        yylval.glenum=GLTEXTUREWRAPR; return GLTEXTUREWRAPR;
    AddressS                          yylval.glenum=GLTEXTUREWRAPS; return GLTEXTUREWRAPS;
    AddressT                          yylval.glenum=GLTEXTUREWRAPT; return GLTEXTUREWRAPT;
    AddressR                          yylval.glenum=GLTEXTUREWRAPR; return GLTEXTUREWRAPR;
    AddressU                          yylval.glenum=GLTEXTUREWRAPS; return GLTEXTUREWRAPS;
    AddressV                          yylval.glenum=GLTEXTUREWRAPT; return GLTEXTUREWRAPT;
    AddressW                          yylval.glenum=GLTEXTUREWRAPR; return GLTEXTUREWRAPR;
    (GL)*(_)*LINEAR_MIPMAP_LINEAR  yylval.glenum=GLLINEARMIPMAPLINEAR; return GLLINEARMIPMAPLINEAR;
    (GL)*(_)*LINEAR              yylval.glenum=GLLINEAR; return GLLINEAR;
    (GL)*(_)*CLAMP               yylval.glenum=GLCLAMP; return GLCLAMP;
    (GL)*(_)*CLAMP_TO_EDGE       yylval.glenum=GLCLAMP; return GLCLAMPTOEDGE;
    (GL)*(_)*REPEAT              yylval.glenum=GLREPEAT; return GLREPEAT;
    (GL)*(_)*NEAREST             yylval.glenum=GLNEAREST; return GLNEAREST;
    (GL)*(_)*MIRRORED_REPEAT      yylval.glenum=GLMIRROREDREPEAT; return GLMIRROREDREPEAT;
    (GL)*(_)*MIRROR              yylval.glenum=GLMIRROREDREPEAT; return GLMIRROREDREPEAT;
}

    /*==================================================================
      Variable
    */
<INITIAL,cstbuffer,technique,sampler_state,dst_state,color_sample_state,rasterization_state,pass,resource,resource1,fbo,fbo1>{VARIABLE} {
    // TODO create and REGISTER the variable in a table
    yylval.s = new std::string(yytext);
    return VARNAME;
}
    /*==================================================================
      strip space and tabs
    */
<INITIAL,cstbuffer,sampler_state,dst_state,color_sample_state,rasterization_state,technique,pass,shader,resource,resource1,fbo,fbo1>[ \t]+ {
}
    /*==================================================================
      New Line : count and strip it out
    */
<INITIAL,cstbuffer,sampler_state,dst_state,color_sample_state,rasterization_state,technique,pass,shader,resource,resource1,fbo,fbo1>\n {
    ++line_num;
    /*return yytext[0];*/
}
    /*==================================================================
      other chars
    */
<INITIAL,cstbuffer,sampler_state,dst_state,color_sample_state,rasterization_state,technique,pass,shader,resource,resource1,fbo,fbo1>. {
    if((yytext[0] >= 33) && (yytext[0] <= 126))
        return yytext[0];
    else {
        nvFX::printf("Warning: line %d : odd character found (%u)...\n", line_num, (unsigned char)yytext[0]);
    }
}
    /*==================================================================
      ==================================================================
      !! SIMPLIFIED PREPROCESSOR !!
      More complex preprocessor would require a complete parser that would
      pre-process the code. Here we avoid doing so : directly loading nested 
      includes : Not even using the grammar analyzer !
      ==================================================================
      ==================================================================
    */
#include BEGIN(incl);
<incl>[<" \t]* /*  eat  the  whitespace and " or < as often in #include */
<incl>[^ \t\n]+     {  /*  got  the  include  file  name  */
    char * s = strchr(yytext, '\"'); // get rid of the quote or >
    if(!s) s = strchr(yytext, '>');
    if(s)
        *s = '\0';
    include_stack.push(IncludeData(YY_CURRENT_BUFFER, line_num, file_name.c_str()));
    file_name = std::string(yytext);
    line_num  = 1;
    FILE *fd = NULL;
    const char *buf = NULL;
    if(nvFX::g_includeCb)
        nvFX::g_includeCb(yytext, fd, buf);
    if(buf)
        yy_switch_to_buffer( yy_scan_string(buf) );
    else if(fd)
        yy_switch_to_buffer( yy_create_buffer(  fd,  YY_BUF_SIZE  )  );
    else {
        fd  =  fopen(  yytext,  "r"  );
        if(!fd)
        {
            fprintf(  stderr,  "err loading file %s", yytext);
        } else {
            yy_switch_to_buffer( yy_create_buffer(  fd,  YY_BUF_SIZE  )  );
        }
    }
    // let's keep track of this newly opened file : when poping, we will have to close it
    IncludeData &incData = include_stack.top();
    incData.fileToClose = fd;
    BEGIN(INITIAL);
}
<<EOF>> {
    if(include_stack.empty())//(  --include_stack_ptr  <  0  )
    {
        yyterminate();
    }
    else
    {
        yy_delete_buffer(  YY_CURRENT_BUFFER  );
        IncludeData &incData = include_stack.top();
        yy_switch_to_buffer(incData.state);//[include_stack_ptr]);
        line_num = incData.line_num;
        file_name = incData.file_name;
        if(incData.fileToClose)
            fclose(incData.fileToClose);
        include_stack.pop();
    }
}
