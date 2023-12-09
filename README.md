## To run the code:
* GCC 6 or higher
* OpenCV 3.4 (You need use `git checkout 3.4` to specify this version when install from OpenCV source code)
* pkg-config

## To install OpenCV in Ubuntu (For Windows users, you need to use WSL)
You can follow this tutorial: https://github.com/lynux0906/OpenCv-pp-Ubuntu
-> Remember to check out the branch 3.4

## Check this link for open source code SURF
https://github.com/julapy/ofxOpenSurf

## Compile
You need to open terminal and compile code.
Read readme.md in each folder for more information.

## Version
### Compile the Code
#### Compile on Ubuntu:
```
g++ -std=c++11 -fpermissive -o test main.cpp fasthessian.cpp integral.cpp ipoint.cpp surf.cpp utils.cpp `pkg-config opencv --cflags --libs`
```
#### GCC Optimize
```
g++ -std=c++11 -fpermissive -Ofast -o test main.cpp fasthessian.cpp integral.cpp ipoint.cpp surf.cpp utils.cpp `pkg-config opencv --cflags --libs`
```

#### To run parallel with openmp
```
g++ -fopenmp -std=c++11 -fpermissive -O3 -o test main.cpp fasthessian.cpp integral.cpp ipoint.cpp surf.cpp utils.cpp `pkg-config opencv --cflags --libs`

```

### Run the Code

``./test -m <mode> [...]``

**Argument Options** (< > after flag indicates argument is required)

- -m | --mode < >: 

	- 1: run static image match between a pair of images
    	- 2: run image stitching with local video files

- -b | --blend_mode: (no additional argument)
         
	- if set, run blending algorithm with stitching; otherwise, run regular stitching algorithm


- -L/R | --src1/src2 <path>
         
	--src1/src2 is the path to images or videos file

For example:
`./test -m 1 -L ./image/1.jpg -R ./image/2.jpg`


