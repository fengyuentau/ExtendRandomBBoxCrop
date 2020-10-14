# ExtendRandomBBoxCrop
Extend `RandomBBoxCrop` from [NVIDA/DALI](https://github.com/NVIDIA/DALI) to perform the same operations to both bounding boxes and extra data, such as bbox-related landmarks.

Follow [official guide](https://docs.nvidia.com/deeplearning/dali/user-guide/docs/examples/custom_operations/custom_operator/create_a_custom_operator.html) to compile and load this plugin.

## Tips
- In case `cmake` locate the wrong `CUDA` root, run `cmake` with the following command:
    ```shell
    cmake -D CUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda ..
    ```
    ***NOTE***: Modify the value of `CUDA_TOOLKIT_ROOT_DIR` according to your case.
- An example of using this plugin vs `RandomBBoxCrop` is presented in the `dev` branch: [dev:examples](https://github.com/fengyuentau/ExtendRandomBBoxCrop/tree/dev/examples).