### Check if your system supports OpenCL

The following steps are for checking for OpenCL on a Linux Machine.  

* Compile the code and build an executable using the following command:  

```
g++ cl.h cl_platform.h printinfo.cpp -o printinfo -lOpenCL
```  

* Run the executable as `./printinfo`  

* If you have OpenCL, you will get an output. For Example:  

```
Number of Platforms = 1
Platform #0:
	Name    = 'Intel(R) CPU Runtime for OpenCL(TM) Applications'
	Vendor  = 'Intel(R) Corporation'
	Version = 'OpenCL 2.1 LINUX'
	Profile = 'FULL_PROFILE'
	Number of Devices = 1
	Device #0:
		Type = 0x0002 = CL_DEVICE_TYPE_CPU
		Device Vendor ID = 0x8086 (Intel)
		Device Maximum Compute Units = 4
		Device Maximum Work Item Dimensions = 3
		Device Maximum Work Item Sizes = 8192 x 8192 x 8192
		Device Maximum Work Group Size = 8192
		Device Maximum Clock Frequency = 2500 MHz

Device Extensions:
cl_khr_icd
cl_khr_global_int32_base_atomics
cl_khr_global_int32_extended_atomics
cl_khr_local_int32_base_atomics
cl_khr_local_int32_extended_atomics
cl_khr_byte_addressable_store
cl_khr_depth_images
cl_khr_3d_image_writes
cl_intel_exec_by_local_thread
cl_khr_spir
cl_khr_fp64
cl_khr_image2d_from_buffer
cl_intel_vec_len_hint
```
