# Tests For QIPAT

QIPAT is an image processing application which was written using Qt. The basic image operations are written from scratch so we had to implement and test entire low-level and high-level modules.

The Low level modules, which are crucial to many image processing algorithms are:

- Algebra Module
- Data Structures module
- Linear Algebra module
- Number Theory module
- Polynomial module
- Topology module



For high level modules, there are:

- ImageCore, which defines the basic image image type and many image processing algorithms
- ImageGUI, which defines the Graphical User Interface

## 1.  Unit Tests (Using  Boost.Test)

### 1.1 Algebra Module

- `pow` function (power) 
- `gcd` and `lcm` functios
- test of basic operators

 ## 1.2 Data Structures Module

- `segment_tree<O>` for any associative operation `O`
- `fenwick_tree<O>` for  any invertible associative operation `O`
- `sparse_table<O>` for any idempotent associative operation `O`
- `order_statistic_tree<T,V,S>` for any key `T`, value `V` and statistic `S`

## 1.3 Linear Algebra Module

#### 1.3.1 Exact Tests 

- For any type `R` which is a field and can store exact results
- vector/matrix addition  and substraction
- Scalar vector/matrix multiplication
- matrix matrix multiplication
- matrix vector multiplication
- matrix inversion
- Linear system solution

#### 1.3.2 Approximate Tests

- For any type `R` which is a field and can have some errors. tests are done with some tolerance $\epsilon\approx 10^{-4}$.
- vector/matrix addition  and substraction
- Scalar vector/matrix multiplication
- matrix matrix multiplication
- matrix vector multiplication
- matrix pow
- matrix inversion
- matrix trace
- matrix determinant
- Linear system solution

## 1.4 Number Theory Module

### 1.4.1 Modular Arithmetic Tests

- Ring operations `+,-,*` modulo $m$
- inverse `inv` and pseudo-inverse `pinv` 
- modular power `pow`
- discrete logarithm `log`
- modular square root `sqrt`

#### 1.4.2 Number Theory Tests

- Prime count function
- Prime Factorisation of an integer
- Prime Decomposition of an integer
- Euler's Totient function
- Set of positive divisors of an integer
- sum of divisors $\sum_{d\mid n}d$ of an integer $n$

## 1.5 Polynomial Module

- ring operations `+,-,*` for a polynomial
- euclidean division of polynomials
- polynomial evaluation
- scalar polynomial multiplication
- Newton's interpolation of a polynomial

### 1.6 Topology

- Testing $\mathscr{L}^1,\mathscr{L}^2,\mathscr{L}^\infty$ norms on real and complex vector spaces
- Testing inner products on real and complex vector spaces

### 1.7 Image Core

- Gray and RGB image construction
- Image reading from PGM,PPM and PBM formats
- Image noise, (a theoretical justification is also included)
- mean filter and gaussian filter
- Otsu's  segmentation algorithm

### 1.8 Image GUI

- `ImageView` class

# 2. Integration Tests

- Median filter (as it uses the image module and the data structures module)
- FFT (as it uses the number theory module and linear algebra module)

## 3. System Tests

- Testing speed of image spectral filters (implemented using $2$ dimensional FFT)
- Testing speed of polynomial FFT multiplication
- Testing speed of median filter

## 4. End to End Tests:

### 4.1 Scenario 1:

- Opening image `img/P6/marbles.ppm`
- Applying Salt and Pepper (Impulsive) noise
- Applying Median filter to reduce that noise
- Save the image

## 4.2 Scenario $2$:

- Opening image `img/P3/billCropped.ppm`
- Laplacian's algorithm for edge detection, with a gray filter and a threshold
- Applying otsu's segmentation algorithm

# 5. Acceptance Tests

Found on the user acceptance word document