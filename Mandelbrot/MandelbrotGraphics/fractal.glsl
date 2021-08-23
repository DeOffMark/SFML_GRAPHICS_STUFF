uniform int uIterations; // how many iterations
uniform bool uIsMandelbrot; // render mandelbrot or julia
uniform vec2 uJuliaConsts; // if it's julia set, use these as constants for C
uniform vec2 uScreenRes; //screen resolution for normalizing coordinates
uniform int uPallete; // enum value for a color pallete
uniform float uScale;
uniform vec2 uOffSet; 

void main(){

	vec2 uv = gl_FragCoord;
	vec2 Z; //complex number
	vec2 mapX = vec2(-2.0, 1.0);
	vec2 mapY = vec2(-1.0, 1.0);
	Z.x = mapX[0] + uv.x * (mapX[1] - mapX[0]) / uScreenRes.x; //real
	Z.y = mapY[0] + uv.y * (mapY[1] - mapY[0]) / uScreenRes.y; //imaginary

	Z.x = (Z.x / uScale) + uOffSet.x;
	Z.y = (Z.y / uScale) + uOffSet.y;
	vec2 C; // C value
	C.x = Z.x ;
	C.y = Z.y ;
	if (!uIsMandelbrot) { // else we set C value to Julia constants
		Z.x = uJuliaConsts.x;
		Z.y = uJuliaConsts.y;
	}
	vec3 col = vec3(0.0, 0.0, 0.0);
	int n = 0;
	while (n < uIterations){ // now we count the equation
		float xsq = C.x * C.x;
		float ysq = C.y * C.y;
		float twoC = 2.0 * C.x * C.y;
		if (abs(xsq) + abs(ysq) > 4.0){
			break;
		}
		C.x = xsq - ysq + Z.x;
		C.y = twoC + Z.y;
		++n;
	}
	if (n == uIterations){
		n = 0;
		col = vec3(0);
	} else {
	switch (uPallete){
	case 1:
		col = vec3(1.0);
		break;
	case 2:
		col = vec3(((float)n/float(uIterations)) );
		break;
	case 3:
		float hue = 360.0 * (1.0 - (float)n/float(uIterations));
		float sat = 1.0;
		float val = 1.0;
		float c = val * sat;
		float x = c * (1.0 - abs(mod(hue/60.0, 2.0) - 1.0));
		float m = val - c;
		if (hue < 60.0){
			col = vec3(c, x, 0.0);
		} else if (hue < 120.0){
			col = vec3(x, c, 0.0);
		} else if (hue < 180.0){
			col = vec3(0.0, c, x);
		} else if (hue < 240.0){
			col = vec3(0.0, x, c);
		} else if (hue < 300.0){
			col = vec3(x, 0.0, c);
		} else {
			col = vec3(c, 0.0, x);
		}
		break;
	}
		
	}
	gl_FragColor = vec4(col, 1.0);
}