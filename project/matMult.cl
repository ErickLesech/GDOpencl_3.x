kernel void matMult(const global float * a,const global float * b, global float * c, ulong n){
	int x = get_global_id(0); //get x
	int y = get_global_id(1); //get y

	float element = 0.0;

	for(int i = 0; i < n; i++){
		element += a[x * n + i] * b[i * n + y];
	}

	c[x * n + y] = element;
}