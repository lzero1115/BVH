# BVH

Simple tutorial to learn Bounding Volume Hierarchy (BVH), referring to:
https://github.com/alecjacobson/computer-graphics-bounding-volume-hierarchy  
Please refer to it for more details.

## Clone

git clone --recursive https://github.com/lzero1115/BVH.git
cd BVH


If you forgot `--recursive`:

git submodule update --init --recursive


## Build (Release)

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4


## Run

./rays ../data/rubber-ducky.obj
./distances 100000 10000
./intersections ../data/knight.obj ../data/cheburashka.obj
