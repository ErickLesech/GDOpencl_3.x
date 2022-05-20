#ifndef OCL_H
#define OCL_H

#include <Godot.hpp>
#include <Object.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <CL/cl.hpp>

using std::vector;
using std::cout;
using std::endl;

#define _CL_ENABLE_EXCEPTIONS

#define N ( 1 << 10 )
#define MAX_RANDOM ( 1 << 10)


namespace godot {

    class OCL : public Object {
        GODOT_CLASS(OCL, Object)

    private:
        size_t maxWorkGroupSize;

        cl::Kernel kernel;
        cl::CommandQueue queue;
        cl::Context context;

        cl::Buffer inputBuffer, outputBuffer;

        std::vector<cl::Device> devices;

        std::vector<int> data;

        String errMsg;
        String log;


    public:
        static void _register_methods();

        OCL();
        ~OCL();

        void set();
        void write(Array arr);
        void run();
        void read(Array arr);

        void _init(); // our initializer called by Godot

    };

}

#endif