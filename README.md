# BVH: A Simple Bounding Volume Hierarchy Tutorial

This repository provides a straightforward tutorial for learning **Bounding Volume Hierarchy (BVH)**.

This project refers to the [computer-graphics-bounding-volume-hierarchy](https://github.com/alecjacobson/computer-graphics-bounding-volume-hierarchy) assignment. Please refer to the original repository for more detailed theoretical information.

## Installation

### Clone the Repository
To clone the repository and its submodules, use the following command:

    git clone --recursive [https://github.com/lzero1115/BVH.git](https://github.com/lzero1115/BVH.git)
    cd BVH

If you already cloned the project without the --recursive flag, run:

    git submodule update --init --recursive

## Build Instructions (Release Mode)

It is recommended to build the project in Release mode for optimal performance:

    mkdir -p build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j4

## Usage

After building, you can test the BVH implementation using these commands:

### Ray-Mesh Intersections
    ./rays ../data/rubber-ducky.obj

### Point-Mesh Distances
    ./distances 100000 10000

### Mesh-Mesh Intersections
    ./intersections ../data/knight.obj ../data/cheburashka.obj
