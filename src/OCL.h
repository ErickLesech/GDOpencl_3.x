#ifndef OCL_H
#define OCL_H

#include <Godot.hpp>
#include <Object.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <CL/cl.hpp>
#include <stdint.h>

using std::vector;
using std::cout;
using std::endl;
using std::string;

#define _CL_ENABLE_EXCEPTIONS

#define N ( 1 << 10 )
#define MAX_RANDOM ( 1 << 10)


namespace godot {

	//enum file_enum {FindMind,matMult};

    class OCL : public Object {
        GODOT_CLASS(OCL, Object)

    private:
        size_t maxWorkGroupSize;

        unsigned int dimension;

        unsigned int rowDimension;
        unsigned int colDimension;

        cl::Kernel kernel;
        cl::CommandQueue queue;
        cl::Context context;

        cl::Buffer inputBuffer, outputBuffer;
        cl::Buffer matrix1,matrix2,matrixOutput;

        std::vector<cl::Device> devices;

        std::vector<float> data;
        std::vector<std::vector<float>> data2d;
        std::vector<std::vector<std::vector<float>>> data3d;

        vector<uint8_t> dataImage;
        unsigned int tailleFile;

        String errMsg;
        String log;

        String msgStr;

    public:
        static void _register_methods();

        OCL();
        ~OCL();

        /* Param
		src -> value is a String or a path to the .cl file
		type -> true for string or false for the path to .cl file
        function_name ->name of the function 
        */
        void set(String src,bool type_var, String function_name, int dimension);
        void setByFile(int val, int dimension);
        
        void write(Array arr, int dimension);
        void writeMat(Array arr, int dimension);
        void run(int dimension);
        void runMat(int dimension);
        void read(Array arr, int dimension);
        void readMat(Array arr, int dimension);

        void getBufferFromImage(String filePath);

        /*
        *
        *getters and setters
        *
        */

        String getmsgStr();
        void setmsgStr(String str);

        unsigned int getDimension();
        void setDimension(unsigned int dim);

        int getTailleFile();
        void setTailleFile(int taille);
    
        Array getDataImage();

        void toArrayTest(Array res);

        void _init(); // our initializer called by Godot

    };

}

#endif