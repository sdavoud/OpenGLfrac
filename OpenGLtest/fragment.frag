#version 450 core
uniform float sherwintime;
in vec2 uv;
in vec3 backcolor;
out vec4 Color;
void main (void)
{
  int maxIterations=500;
  float tmpval;
  int iter;
  float tempreal, tempimag, Creal, Cimag;
  float check;
  vec2 pos = fract (uv);
  float real = (pos.s * 3.0 ) - 2;
  float imag = (pos.t * 3.0 ) - 1.5;
  Creal = real;
  Cimag = imag;
  for (iter = 0; iter < maxIterations; iter++)
  {
    // z = z^2 + c
    tempreal = real;
    tempimag = imag;
    real = (tempreal * tempreal) - (tempimag * tempimag);
    imag = 2 * tempreal * tempimag;
	//imag = 2*(tempreal * tempreal) + 2*(tempimag * tempimag);
    real += Creal;
    imag += Cimag;
    check = (real * real) + (imag * imag);
    if (check >= 4)
      break;
  }
  vec4 color;
  if (check >= 4)
    color = vec4 (backcolor.x*sin(iter), backcolor.y*sin(iter), (0.5+0.5*sin(4*sherwintime)), 1.0);
  else
  {
    tmpval = fract ((iter / 10));
    color = vec4 (tmpval, tmpval, tmpval, 1.0);
  }
  Color = color;
  }