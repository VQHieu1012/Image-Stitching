## OpenMP Version
### Compile the Code
#### Compile on Ubuntu:

```
g++ -fopenmp -std=c++11 -fpermissive -Ofast -o test main.cpp fasthessian.cpp integral.cpp ipoint.cpp surf.cpp utils.cpp `pkg-config opencv --cflags --libs`
```
#### Compile on MacOS:
```
g++-7 -fopenmp -std=c++11 -fpermissive -O3 -o test main.cpp fasthessian.cpp integral.cpp ipoint.cpp surf.cpp utils.cpp `pkg-config opencv --cflags --libs`
```
Adapt `g++-7` to the version of g++.

### Run the Code

``./test -m <mode> [...]``

**Argument Options** (< > after flag indicates argument is required)

- -m | --mode < >: 

	
	- 1: run static image match between a pair of images
	- 2: run image stitching with local video files


- -b | --blend_mode: (no additional argument)
         
	- if set, run blending algorithm with stitching; otherwise, run regular stitching algorithm

- -r | --resolution (for mode 2 and 3):

	- user-specified resolution

- -L/R | --src1/src2 <path>
         
	- <path> path of  image/video to be processed.


