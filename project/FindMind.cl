kernel void func(ulong n, global const float * data, global float * res){
	size_t i = get_global_id(0);
 	res[i] = data[i] * data[i];
 }