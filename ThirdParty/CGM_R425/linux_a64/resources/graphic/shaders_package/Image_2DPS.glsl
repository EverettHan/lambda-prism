const int GL_NEVER = 0;    
const int GL_LESS = 1;     
const int GL_EQUAL = 2;    
const int GL_LEQUAL = 3;   
const int GL_GREATER = 4;  
const int GL_NOTEQUAL = 5; 
const int GL_GEQUAL = 6;   
const int GL_ALWAYS = 7;   

#ifndef GLES2Platform

  int ResolveAlphaTest(float value, float limit, int func)
  {
    int alphaDifference = ((value-limit)>=0) ? 1 : -1;
    return ((1<<(1+alphaDifference)) & func); 
  }

#else

  int ResolveAlphaTest(float value, float limit, int func)
  {  
    int result = 0;

    if(func ==  GL_NEVER)
    {
      result = 0;
    }
    else
    {
      if(func == GL_LESS)
      {
        if(value < limit)
          result = 1;
        else
          result = 0;
      }
      else
      {
        if(func == GL_EQUAL)
        {
          if(value == limit)
            result = 1;
          else
            result = 0;
        }
        else
        {
          if(func == GL_LEQUAL)
          {
            if(value <= limit)
              result = 1;
            else
              result = 0;
          }
          else
          {
            if(func == GL_GREATER)
            {
              if(value > limit)
                result = 1;
              else
                result = 0;
            }
            else
            {
              if(func == GL_NOTEQUAL)
              {
                if(value != limit)
                  result = 1;
                else
                  result = 0;
              }
              else
              {
                if(func == GL_GEQUAL)
                {
                  if(value >= limit)
                    result = 1;
                  else
                    result = 0;
                }
                else
                {
                  if(func == GL_ALWAYS)
                    result = 1;
                  else
                    result = 0;  
                }
              }
            }
          }
        }
      }
    }

    return result;
  }
#endif

vec4 textureSample;

void ComputeCommonValues()
{
  textureSample = texture(imageTexture, vTexCoord0);
}

vec3 ComputeAlbedo()
{
  return textureSample.xyz;
}

float ComputeOpacity()
{
  return textureSample.w;
}

bool ComputeDiscard()
{
  return ((ResolveAlphaTest(ComputeOpacity(), cb_Image_2D.Image_AlphaLimit, cb_Image_2D.Image_AlphaFunc)) == 0);
}
