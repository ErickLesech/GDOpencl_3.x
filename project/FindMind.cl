kernel void func(ulong n, global const int * data, global int * res){
	size_t i = get_global_id(0);
	res[i] = data[i] * data[i];
}