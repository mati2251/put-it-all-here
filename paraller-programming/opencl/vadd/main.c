#define CL_TARGET_OPENCL_VERSION 110

#include <CL/opencl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i = 0;
  const int LIST_SIZE = 256;
  int *A = (int *)malloc(sizeof(int) * LIST_SIZE);
  int *B = (int *)malloc(sizeof(int) * LIST_SIZE);

  srand(0);
  for (i = 0; i < LIST_SIZE; i++)
  {
    A[i] = rand() % LIST_SIZE;
    B[i] = rand() % LIST_SIZE;
  }

  FILE *vadd_kernel_file;
  char *vadd_kernel_source;
  size_t vadd_kernel_size;

  vadd_kernel_file = fopen("vadd.cl", "r");
  if (!vadd_kernel_file)
  {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
  }
  fseek(vadd_kernel_file, 0L, SEEK_END);
  vadd_kernel_size = ftell(vadd_kernel_file);
  fseek(vadd_kernel_file, 0L, SEEK_SET);
  vadd_kernel_source = (char *)malloc(vadd_kernel_size + 1);
  vadd_kernel_size = fread(vadd_kernel_source, 1, vadd_kernel_size, vadd_kernel_file);
  vadd_kernel_source[vadd_kernel_size] = '\0';
  fclose(vadd_kernel_file);
  cl_platform_id platform_id = NULL;
  cl_device_id device = NULL;
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to get platform id.\n");
    exit(1);
  }
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device, &ret_num_devices);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to get device id.\n");
    exit(1);
  }
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &ret);
  cl_command_queue command_queue = clCreateCommandQueue(context, device, 0, &ret);

  cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to create buffer.\n");
    exit(1);
  }
  cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to create buffer.\n");
    exit(1);
  }
  cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to create buffer.\n");
    exit(1);
  }

  ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to write buffer.\n");
    exit(1);
  }
  ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), B, 0, NULL, NULL);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to write buffer.\n");
    exit(1);
  }

  cl_program program = clCreateProgramWithSource(context, 1, (const char **)&vadd_kernel_source, (const size_t *)&vadd_kernel_size, &ret);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to create program with source.\n");
    exit(1);
  }
  ret = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to build program.\n");
    size_t log_size;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

    char *log = (char *)malloc(log_size);

    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

    printf("%s\n", log);
    fprintf(stderr, "Error code: %d\n", ret);
    exit(1);
  }

  cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to create kernel.\n");
    exit(1);
  }
  ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to set kernel arg 0.\n");
    exit(1);
  }
  ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to set kernel arg 1.\n");
    exit(1);
  }
  ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to set kernel arg 2.\n");
    exit(1);
  }

  size_t global_item_size = LIST_SIZE;
  size_t local_item_size = 64;
  ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, 0, NULL);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to enqueue ND range kernel.\n");
    fprintf(stderr, "Error code: %d\n", ret);
    exit(1);
  }

  int *C = (int *)malloc(sizeof(int) * LIST_SIZE);
  ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), C, 0, NULL, NULL);
  if (ret != CL_SUCCESS)
  {
    fprintf(stderr, "Failed to read buffer.\n");
    exit(1);
  }

  for (i = 0; i < LIST_SIZE; i++)
  {
    printf("%d + %d = %d\n", A[i], B[i], C[i]);
  }

  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(a_mem_obj);
  ret = clReleaseMemObject(b_mem_obj);
  ret = clReleaseMemObject(c_mem_obj);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
  free(A);
  free(B);
  free(C);
  return 0;
}
