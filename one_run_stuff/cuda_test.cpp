#include <iostream>
using namespace std;

extern "C" void cudaMalloc(void** devPtr, size_t size);
extern "C" void cudaFree(void* devPtr);

int main()
{
	int* dev_buffer;
	cudaMalloc((void**)&dev_buffer, 8);
	cudaFree(dev_buffer);
	return 0;
}
