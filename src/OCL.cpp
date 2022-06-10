#include "OCL.h"

using namespace godot;

#include<fstream>

/*
 *
 * Registers methods could be use in GDscript code
 *
 *
 */

void OCL::_register_methods() {
    //register_method("_process", &GDExample::_process);

    register_method("write", &OCL::write);
    register_method("writeMat",&OCL::writeMat);

    register_method("run", &OCL::run);
    register_method("runMat",&OCL::runMat);

    register_method("read", &OCL::read);
    register_method("readMat",&OCL::readMat);

    register_method("set", &OCL::set);
    register_method("setByFile", &OCL::setByFile);

    register_method("getBufferFromImage",&OCL::getBufferFromImage);

    //enregistrement des getters et setters

    register_method("getmsgStr",&OCL::getmsgStr);
    register_method("setmsgStr",&OCL::setmsgStr);

    register_method("getDimension",&OCL::getDimension);
    register_method("setDimension",&OCL::setDimension);

    register_method("getTailleFile",&OCL::getTailleFile);
    register_method("setTailleFile",&OCL::setTailleFile);

    register_method("getDataImage",&OCL::getDataImage);

    register_method("toArrayTest",&OCL::toArrayTest);


    //register_property<GDExample,type>("name_attribute",&GDExample::name_attribute,default_val);
    register_property<OCL, String>("log", &OCL::log, "");
    register_property<OCL, String>("errMsg", &OCL::errMsg, "");


}

/*
 *
 * get error flag from cl_int
 *
 *
 */

const char * getErrorString(cl_int err) {

    switch (err) {
   	 	case 0: return "CL_SUCCESS";
    	case -1: return "CL_DEVICE_NOT_FOUND";
    	case -2: return "CL_DEVICE_NOT_AVAILABLE";
    	case -3: return "CL_COMPILER_NOT _AVAILABLE";
    	case -4: return "CL_MEM_OBJECT _ALLOCATION_FAILURE";
    	case -5: return "CL_OUT_OF_RESOURCES";
    	case -6: return "CL_OUT_OF_HOST_MEMORY";
    	case -7: return "CL_PROFILING_INFO_NOT _AVAILABLE";
    	case -8: return "CL_MEM_COPY_OVERLAP";
    	case -9: return "CL_IMAGE_FORMAT _MISMATCH";
    	case -10: return "CL_IMAGE_FORMAT_NOT _SUPPORTED";
    	case -11 : return "CL_BUILD_PROGRAM _FAILURE";
    	case -12 : return "CL_MAP_FAILURE";
    	case -13 : return "CL_MISALIGNED_SUB _BUFFER_OFFSET	";
    	case -14 : return "CL_EXEC_STATUS_ERROR_ FOR_EVENTS_IN_WAIT_LIST";
    	case -15 : return "CL_COMPILE_PROGRAM _FAILURE";
    	case -16 : return "CL_LINKER_NOT_AVAILABLE	";
    	case -17 : return "CL_LINK_PROGRAM_FAILURE";
    	case -18 : return "CL_DEVICE_PARTITION _FAILED";
    	case -19 : return "CL_KERNEL_ARG_INFO _NOT_AVAILABLECL_BUILD_PROGRAM _FAILURE";
    	case -30 : return "CL_INVALID_VALUE";
    	case -31 : return "CL_INVALID_DEVICE_TYPE";
    	case -32 : return "CL_INVALID_PLATFORM";
    	case -33 : return "CL_INVALID_DEVICE";
    	case -34 : return "CL_INVALID_CONTEXT";
    	case -35 : return "CL_INVALID_QUEUE_PROPERTIES";
    	case -36 : return "CL_INVALID_COMMAND_QUEUE";
    	case -37 : return "CL_INVALID_HOST_PTR";
    	case -38 : return "CL_INVALID_MEM_OBJECT";
    	case -39 : return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    	case -40 : return "CL_INVALID_IMAGE_SIZE";
    	case -41 : return "CL_INVALID_SAMPLER";
    	case -42 : return "CL_INVALID_BINARY";
    	case -43 : return "CL_INVALID_BUILD_OPTIONS";
    	case -44 : return "CL_INVALID_PROGRAM";
    	case -45 : return "CL_INVALID_PROGRAM_EXECUTABLE";
    	case -46 : return "CL_INVALID_KERNEL_NAME";
    	case -47 : return "CL_INVALID_KERNEL_DEFINITION";
    	case -48 : return "CL_INVALID_KERNEL";
    	case -49 : return "CL_INVALID_ARG_INDEX";
    	case -50 : return "CL_INVALID_ARG_VALUE";
    	case -51 : return "CL_INVALID_ARG_SIZE";
    	case -52 : return "CL_INVALID_KERNEL_ARGS";
    	case -53 : return "CL_INVALID_WORK_DIMENSION";
    	case -54 : return "CL_INVALID_WORK_GROUP_SIZE";
    	case -55 : return "CL_INVALID_WORK_ITEM_SIZE";
    	case -56 : return "CL_INVALID_GLOBAL_OFFSET";
    	case -57 : return "CL_INVALID_EVENT_WAIT_LIST";
    	case -58 : return "CL_INVALID_EVENT";
    	case -59 : return "CL_INVALID_OPERATION";
    	case -60 : return "CL_INVALID_GL_OBJECT";
    	case -61 : return "CL_INVALID_BUFFER_SIZE";
    	case -62 : return "CL_INVALID_MIP_LEVEL";
    	case -63 : return "CL_INVALID_GLOBAL_WORK_SIZE";
    	case -64 : return "CL_INVALID_PROPERTY";
    	case -65 : return "CL_INVALID_IMAGE_DESCRIPTOR";
    	case -66 : return "CL_INVALID_COMPILER_OPTIONS";
    	case -67 : return "CL_INVALID_LINKER_OPTIONS";
    	case -68 : return "CL_INVALID_DEVICE_PARTITION_COUNT";
    	case -69 : return "CL_INVALID_PIPE_SIZE";
    	case -70 : return "CL_INVALID_DEVICE_QUEUE";
    	case -1000 : return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    	case -1001 : return "CL_PLATFORM_NOT_FOUND_KHR";
    	case -1002 : return "CL_INVALID_D3D10_DEVICE_KHR";
    	case -1003 : return "CL_INVALID_D3D10_RESOURCE_KHR";
    	case -1004 : return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    	case -1005 : return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    	case -1006 : return "CL_INVALID_D3D11_DEVICE_KHR";
    	case -1007 : return "CL_INVALID_D3D11_RESOURCE_KHR";
    	case -1008 : return "CL_D3D11_RESOURCE_ALREADY_ACQUIRED_KHR";
    	case -1009 : return "CL_D3D11_RESOURCE_NOT_ACQUIRED_KHR";
    	case -1010 : return "CL_INVALID_D3D9_DEVICE_NV CL_INVALID_DX9_DEVICE_INTEL";

    	default: return "ERROR";

    }
}

/*
 *
 *get File by 
 *
 *
 */

const char * getFileByVal(int val){

	switch(val){
		case 0: return "FindMind.cl";
		case 1: return "matMult.cl";

		default: return NULL;
	}
}

const char * getNameFuncByVal(int val){

	switch(val){
		case 0: return "func";
		case 1: return "matMult";

		default: return NULL;
	}
}

int OCL::getTailleFile(){
	return this->tailleFile;
}

void OCL::setTailleFile(int taille){
	this->tailleFile = taille;
}

Array OCL::getDataImage(){

	/*size_t taille = this->dataImage.size();
	vector<uint8_t> arr(taille);
	for(int i = 0; i < this->dataImage.size();i++){
		arr.push_back(this->dataImage[i]);
	}*/
	Array arr;

	return arr;


}

void OCL::toArrayTest(Array res){

	for(int i = 0; i < 10; i++){
		res[i] = i;
	}
}


String OCL::getmsgStr(){

	return this->msgStr;
}

void OCL::setmsgStr(String str){

	this->msgStr = str;
}

unsigned int OCL::getDimension(){

	return this->dimension;
}


void OCL::setDimension(unsigned int dim){

	this->dimension = dim;
}

OCL::OCL() {
}

OCL::~OCL() {
    // add your cleanup here
}

void OCL::_init() {

    this->errMsg = "";
  
}

void OCL::setByFile(int val, int dimension){

	if(dimension <= 0){
		this->errMsg = "dimension is 0 or less";
		return;
	}

	const char * SourcePath = getFileByVal(val);

	const char * name_func = getNameFuncByVal(val);

	std::vector<cl::Platform> platforms;

    cl::Platform::get(&platforms);

    if (platforms.empty()) {
        this->errMsg = "error not platform found";
        return;
    }

    // Get GPU device

    std::vector<cl::Device> devices;

    for (auto p = platforms.begin(); devices.empty() && p != platforms.end(); p++) {
        std::vector<cl::Device> pldev;

        try {
            p->getDevices(CL_DEVICE_TYPE_GPU, &pldev);

            for (auto d = pldev.begin(); devices.empty() && d != pldev.end(); d++) {

                if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;

                std::string ext = d->getInfo<CL_DEVICE_EXTENSIONS>();

                devices.push_back(*d);

                this->context = cl::Context(devices);
                break;
            }
        }
        catch (...) {
            devices.clear();
        }

    }

    if (devices.empty()) {
        this->errMsg = "Devices not found";
        return;
    }

    //create a command queue

    this->queue = cl::CommandQueue(context, devices[0]);

    std::ifstream file(SourcePath);
    std::string src = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    this->msgStr = godot::String(src.c_str());

    // Compile opencl program for found device

    cl::Program program(context, cl::Program::Sources(1, std::make_pair(src.c_str(), src.length() + 1)));

    cl_int err = program.build(devices, "-cl-std=CL1.2");


    if (err != CL_SUCCESS) {
        this->errMsg = "Failed OpenCL compilation error " + String(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]).c_str());
        return;
    }

    this->kernel = cl::Kernel(program, name_func);

    this->maxWorkGroupSize = this->kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0], &err);


    if (err != CL_SUCCESS) {
        this->errMsg = "Failed getting opencl markgroupSize " + String(getErrorString(err));
        return;
    }

    this->outputBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * dimension);
    this->matrixOutput = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * dimension);


}



/*
 *set device, context and informations about method from the openCL code 
 */

void OCL::set(String src, bool type_var, String function_name, int dimension) {

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    const char * func_name = function_name.utf8().get_data();
    std::string sourceStr;
    
    const char * source;

    if(type_var == true){

    	const char * SourcePath = src.utf8().get_data();;
    	std::ifstream file(SourcePath);
    	sourceStr = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    	source = sourceStr.c_str();

    	this->msgStr = godot::String(source);

    	//source = godotStringtoStdString(src);
    	
    }else if(type_var == false){

    	 source = src.utf8().get_data();

    	this->msgStr = godot::String(source);

    }

    if (platforms.empty()) {
        this->errMsg = "error not platform found";
        return;
    }

    // Get GPU device

    std::vector<cl::Device> devices;

    for (auto p = platforms.begin(); devices.empty() && p != platforms.end(); p++) {
        std::vector<cl::Device> pldev;

        try {
            p->getDevices(CL_DEVICE_TYPE_GPU, &pldev);

            for (auto d = pldev.begin(); devices.empty() && d != pldev.end(); d++) {

                if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;

                std::string ext = d->getInfo<CL_DEVICE_EXTENSIONS>();

                devices.push_back(*d);

                this->context = cl::Context(devices);
                break;
            }
        }catch (...) {
            devices.clear();
        }

    }

    if (devices.empty()) {
        this->errMsg = "Devices not found";
        return;
    }

    //create a command queue

    this->queue = cl::CommandQueue(context, devices[0]);

    // Compile opencl program for found device

    //cl::Program program(context, cl::Program::Sources(1, std::make_pair(src.c_str(), src.length() + 1)));

    cl::Program program(context, cl::Program::Sources(1, std::make_pair(source, strlen(source) + 1)));


    cl_int err = program.build(devices, "-cl-std=CL1.2");


    if (err != CL_SUCCESS) {
        this->errMsg = "Failed OpenCL compilation error " + String(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]).c_str());
        return;
    }

    this->kernel = cl::Kernel(program, func_name);

    this->maxWorkGroupSize = this->kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0], &err);


    if (err != CL_SUCCESS) {
        this->errMsg = "Failed getting opencl markgroupSize " + String(getErrorString(err));
        return;
    }

    this->outputBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * dimension);
    this->matrixOutput = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * dimension);

}

//read array and check results

void OCL::read(Array arr, int dimension) {

    std::vector<float>res(dimension);

    cl_int err = queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, dimension * sizeof(float), &res[0]);

    if (err != CL_SUCCESS) {
        this->errMsg = "Failed err : " + String(getErrorString(err));
        return;
    }

    int success = 0;

    for (int i = 0; i < dimension; i++) {
        if (res[i] = data[i] * data[i]) {
            success++;
        }
    }

    char buff[32] = { 0 };
    sprintf(buff, "%d / %d", success, dimension);
    this->log = "Success " + String(buff);
}

void OCL::readMat(Array arr, int dimension){

	std::vector<float> res(dimension);

	cl_int err;

	err = queue.enqueueReadBuffer(matrixOutput, CL_TRUE, 0, dimension * sizeof(float), &res[0]);

	 if (err != CL_SUCCESS) {
        this->errMsg = "Failed err : " + String(getErrorString(err));
        return;
    }

    int success = 0;

    double dim = sqrt(double(dimension));

    int dimInteger = int(dim);

    for(int i = 0; i < dimInteger; i++){

    	for(int j = 0 ; j < dimInteger ; j++){

    		float element = 0.0;

    			for(int k = 0; k < dimInteger ; k++){
    				element += data[i * dimInteger + k] * data[k * dimInteger + j];
    			}

    		if(res[i * dimInteger + j] == element){
    			success++;
    		}
    	}
    }


	char buff[32] = { 0 };
    sprintf(buff, "%d / %d", success, dimension);
    this->log = "Success " + String(buff);


}


//write in the array

void OCL::write(Array arr, int dimension) {

    cl_int err;

    if (arr.size() != dimension) {
        char buff[16] = { 0 };

        sprintf(buff, "%d", dimension);
        this->errMsg = "Data array size not match : data size is " + String(buff);
    }

    this->data = std::vector<float>(dimension);

    for (int i = 0; i < dimension; i++) {
        float member = arr[i];
        data[i] = member;
    }

    this->inputBuffer = cl::Buffer(this->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, dimension * sizeof(float), &data[0]);

    err = kernel.setArg(0, static_cast<cl_ulong>(dimension));

    err |= kernel.setArg(1, inputBuffer);
    err |= kernel.setArg(2, outputBuffer);

    if (err != CL_SUCCESS) {
        this->errMsg = "Failed to set kernel args on writing : " + String(getErrorString(err));
        return;
    }



}

void OCL::writeMat(Array arr, int dimension){

	cl_int err;

	if (arr.size() != dimension) {
        char buff[16] = { 0 };

        sprintf(buff, "%d", dimension);
        this->errMsg = "Data array size not match : data size is " + String(buff);
    }

    this->data = std::vector<float>(dimension);

    for (int i = 0; i < dimension; i++) {
        float member = arr[i];
        data[i] = member;
    }

    this->matrix1 = cl::Buffer(this->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(float), &data[0]);
    this->matrix2 = cl::Buffer(this->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(float), &data[0]);

    double dim = sqrt(double(dimension));

    err = kernel.setArg(0, matrix1);

    err |= kernel.setArg(1, matrix2);
    err |= kernel.setArg(2, matrixOutput);
    err |= kernel.setArg(3, static_cast<cl_ulong>(dim));

    if (err != CL_SUCCESS) {
        this->errMsg = "Failed to set kernel args on writing : " + String(getErrorString(err));
        return;
    }

}

void OCL::runMat(int dimension){

	cl_int err;

	err = queue.enqueueNDRangeKernel(kernel, 2, dimension, cl::NDRange(1));

	if (err != CL_SUCCESS) {
        this->errMsg = "Failed run : " + String(getErrorString(err));
        return;
    }

    err = queue.finish();

    if (err != CL_SUCCESS) {
        this->errMsg = "Failed finish : " + String(getErrorString(err));
        return;
    }

}


/*
 *
 * run kernel
 *
 */

void OCL::run(int dimension) {

    cl_int err;

    err = queue.enqueueNDRangeKernel(kernel, 0, dimension, cl::NDRange(1));

    if (err != CL_SUCCESS) {
        this->errMsg = "Failed run : " + String(getErrorString(err));
        return;
    }

    err = queue.finish();

    if (err != CL_SUCCESS) {
        this->errMsg = "Failed finish : " + String(getErrorString(err));
        return;
    }


}

void OCL::getBufferFromImage(String filePath){

	const char * file_conv = filePath.utf8().get_data();
	vector<int> res(50);
	uint8_t byte;
	std::ifstream file(file_conv);

	int dimension = 0;

	file >> byte;
	this->dataImage.push_back(byte);
	this->tailleFile++;
	
	if(file.is_open()){

		while(!file.eof()){

			this->dataImage.push_back(byte);
			this->tailleFile++;
			file >> byte;
		}
	}else{
			this->errMsg = "file is not open";
	}

	file.close();
}
