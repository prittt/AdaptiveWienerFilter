# Adaptive Wiener Filter
<p align="justify">This project contains a quite fast C++ implementation of the adaptive Wiener filter. The source code requires OpenCV library to properly work.</p>

__Contributors__
- [Federico Bolelli](https://github.com/prittt)
- [Costantino Grana](https://github.com/CostantinoGrana)

## Requirements
- OpenCV 3.1.0 or higher (http://opencv.org/downloads.html);
- One of your favourite IDE/compiler: Visual Studio 2013 or higher, Xcode 5.0.1, gcc 4.7 or higher, .. (with C++11 support).

If you think it is convenience, you can use Cmake to create a project running this code. If OpenCV are installed in your environment, the "CMakeLists.txt" file (included in this repository) will automatically find OpenCV path and create the project.

## Algorithms
<p align="justify">The adaptive Wiener's filter estimates the local mean and variance around each pixel using the following formulas:</p>

$$\mu = \displaystyle\frac{1}{NM}\displaystyle\sum_{n_1,n_2 \in \eta} src(n_1, n_2)$$

and

$$\sigma^2 = \displaystyle\frac{1}{NM}\displaystyle\sum_{n_1,n_2 \in \eta} src^2(n_1, n_2) - \mu^2$$

<p align="justify">where $\eta$ is the N-by-M local neighborhood of each pixel in the source image ($src$). The implementation then creates a pixelwise Wiener filter using these estimations:</p>

$$dst(n_1, n_2) = \mu + \displaystyle\frac{\max(0,\sigma^2 - \nu^2)}{\max(\sigma^2, \nu^2)} \displaystyle (src(n_1,n_2) - \mu)$$
 
<p align="justify">where $\nu^2$ is the noise variance and $dst$ is the output filtered image. If the noise variance is not given, the function uses the average of all the local estimated variances. Note that the above formula is the one actually used by the Matlab's $wiener2$ function (differently from what declared in the documentation <sup><a href="#WIENER2_MATLAB">2</a></sup>).</p> 

## References

<a name="WIENER_REFERENCE">[1] </a><em>Lim, Jae S., Two-Dimensional Signal and Image Processing, Englewood Cliffs, NJ, Prentice Hall, 1990, p. 538, equations 9.26, 9.27, and 9.29.</em>
</br>
<a name="WIENER2_MATLAB">[2] </a><em>https://it.mathworks.com/help/images/ref/wiener2.html (Accessed on 15 March 2017)</em>
