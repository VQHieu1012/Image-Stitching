## To run the code:
* GCC 6 or higher
* OpenCV 3.4 (You need use `git checkout 3.4` to specify this version when install from OpenCV source code)
* pkg-config

## To install OpenCV in Ubuntu (For Windows users, you need to use WSL)

Step 1: Update the Ubuntu system packages
`sudo apt-get update && sudo apt-get upgrade`

Step 2: Install required tools and packages
`sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev`

Step 3: Download OpenCV sources using git
`sudo -s`
`cd /opt`
`git clone https://github.com/Itseez/opencv.git`
`git clone https://github.com/Itseez/opencv_contrib.git`

Step 4: Checkout branch 3.4 in opencv and opencv_contrib
`cd opencv_contrib`
`git checkout 3.4`
`cd ..`
`cd opencv`
`git checkout 3.4`

Step 5: Build and Install OpenCV
`mkdir release`
`cd release`
`cmake -D BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D OPENCV_GENERATE_PKGCONFIG=ON -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules /opt/opencv/`
`make -j4`
`make install`
`ldconfig`
`exit`
`cd ~`

Step 6: Find and Set "opencv.pc" file path
`ls /usr/local/lib/pkgconfig/`
`sudo cp /usr/local/lib/pkgconfig/opencv.pc  /usr/lib/x86_64-linux-gnu/pkgconfig/opencv.pc`

Step 7: Check OpenCV version
`pkg-config --modversion opencv`
If the output is "3.4.x", you are good to go.


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
g++ -fopenmp -std=c++11 -fpermissive -Ofast -o test main.cpp fasthessian.cpp integral.cpp ipoint.cpp surf.cpp utils.cpp `pkg-config opencv --cflags --libs`

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


