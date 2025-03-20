__kernel void mat_mul (const int n, __global int *A, __global int *B, __global int *C, __local int *priv_b){
    int i = get_global_id(0);
    int j = get_global_id(1);
    int iloc = get_local_id(0);
    int nloc = get_local_size(0);
    float tmp = 0.0;
    int priv_a[1024];  
    for(int k=0; k < n; k++){
        priv_a[k] = A[i * n + k];
    }

    for(int k=iloc; k<n; k+=nloc){
        priv_b[k] = B[k*n+j];
    }

    barrier(CLK_LOCAL_MEM_FENCE);

    for (int k = 0; k < n; k++){
        tmp += priv_a[k] * B[k];
    }
    C[i*n + j] = tmp;

    barrier(CLK_LOCAL_MEM_FENCE);
}