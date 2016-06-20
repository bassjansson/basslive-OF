
// Fragment shader

#version 150

#define SIZE       4
#define PRECISION  0.675
#define ITERATIONS 5

uniform float height;
uniform vec2  translate;
uniform float zoom;
uniform vec2  a;

uniform vec2 coef0;
uniform vec2 coef1;
uniform vec2 coef2;
uniform vec2 coef3;
//uniform vec2 coef4;
//uniform vec2 coef5;

out vec4 outputColor;

vec2 complexAdd (vec2 left, vec2 right)
{
	vec2 result;

	result.x = left.x + right.x;
	result.y = left.y + right.y;

	return result;
}

vec2 complexMin (vec2 left, vec2 right)
{
	vec2 result;
    
	result.x = left.x - right.x;
	result.y = left.y - right.y;
    
	return result;
}

vec2 complexMul (vec2 left, vec2 right)
{
	vec2 result;
    
	result.x = left.x * right.x - left.y * right.y;
	result.y = left.x * right.y + left.y * right.x;
    
	return result;
}

vec2 complexDev (vec2 left, vec2 right)
{
	vec2 result;
    
    float devide = right.x * right.x + right.y * right.y;
    result.x = (left.x * right.x + left.y * right.y) / devide;
    result.y = (left.y * right.x - left.x * right.y) / devide;
    
	return result;
}

vec2 complexPow (vec2 base, int power)
{
    vec2 result = vec2(1., 0.);
    
    for (int i = 0; i < power; i++)
        result = complexMul(result, base);
    
    return result;
}

vec2 getY (vec2[SIZE] coefs, vec2 x)
{
    vec2 y = vec2(0., 0.);
    
    for (int i = 0; i < SIZE; i++)
        y = complexAdd(y, complexMul(coefs[i], complexPow(x, i)));
    
    return y;
}

vec2[SIZE] getDerivative (vec2[SIZE] coefs)
{
    vec2[SIZE] derivative;
    
    for (int i = 1; i < SIZE; i++)
        derivative[i - 1] = complexMul(coefs[i], vec2(i, 0.));
    
    derivative[SIZE - 1] = vec2(0., 0.);
    
    return derivative;
}

vec2 getNextZ (vec2[SIZE] coefs, vec2[SIZE] derivative, vec2 z, vec2 a)
{
    return complexMin(z, complexMul(a, complexDev(getY(coefs, z), getY(derivative, z))));
}

vec4 getColor (vec2 z, float i)
{
    float radius = sqrt(z.x * z.x + z.y * z.y);
    float theta  = mod(atan(z.y / z.x) / 6.2832 + 0.75 + abs(z.x)/z.x * 0.25, 1.);

    vec4 color;
    
//    color.r = (1. - i) * mod(theta + 0.00, 1.);// * radius;
//    color.g = (1. - i) * mod(theta + 0.33, 1.);// * radius;
//    color.b = (1. - i) * mod(theta + 0.66, 1.);// * radius;
//    color.a = 0.5;
    
//    color.r = (1. - i) * sqrt(z.x * z.x + z.y * z.y);
//    color.g = (1. - i) * (z.x / 2. + 0.5);
//    color.b = (1. - i) * (z.y / 2. + 0.5);
//    color.a = 0.5;
    
//    color.r = 0.25 + 0.75 * (1. - i) * mod(theta + 0.00, 1.) * radius;
//    color.g = 0.25 + 0.75 * (1. - i) * mod(theta + 0.33, 1.) * radius;
//    color.b = 0.25 + 0.75 * (1. - i) * mod(theta + 0.66, 1.) * radius;
//    color.a = 0.5;
    
    color.r = 0.2 + 0.8 * (1. - i) * sqrt(z.x * z.x + z.y * z.y);
    color.g = 0.2 + 0.8 * (1. - i) * (z.x / 2. + 0.5);
    color.b = 0.2 + 0.8 * (1. - i) * (z.y / 2. + 0.5);
    color.a = 0.5;
    
    return color;
}

void main()
{
    vec2[SIZE] coefs;
    
    coefs[0] = coef0;
    coefs[1] = coef1;
    coefs[2] = coef2;
    coefs[3] = coef3;
    //coefs[4] = coef4;
    //coefs[5] = coef5;
    
    vec2[SIZE] derivative = getDerivative(coefs);
    
    vec2 z = vec2(( gl_FragCoord.x - translate.x         ) * zoom / height,
                  (-gl_FragCoord.y - translate.y + height) * zoom / height);
    
    float i = 0.;
    
    while (i < 1.)
    {
        vec2 y = getY(coefs, z);
        if (sqrt(y.x * y.x + y.y * y.y) < PRECISION) break;
        
        z  = getNextZ(coefs, derivative, z, a);
        i += 1. / ITERATIONS;
    }
    
    outputColor = getColor(z, i);
}
