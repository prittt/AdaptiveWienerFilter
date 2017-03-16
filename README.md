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

<p align="center"><img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/0f6d38bd78ab115ade732f29fe7f51eb.svg?invert_in_darkmode" align=middle width=200.28525pt height=42.855945pt/></p>

and

<p align="center"><img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/2c27573c993c3eca49333fac0a44d38f.svg?invert_in_darkmode" align=middle width=251.65964999999997pt height=42.855945pt/></p>

<p align="justify">where <img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/1d0496971a2775f4887d1df25cea4f7e.svg?invert_in_darkmode" align=middle width=8.752095000000004pt height=14.155350000000013pt/> is the N-by-M local neighborhood of each pixel in the source image (<img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/1908ca5a63cf1f081022d43f2c9fc506.svg?invert_in_darkmode" align=middle width=22.692285000000005pt height=14.155350000000013pt/>). The implementation then creates a pixelwise Wiener filter using these estimations:</p>

<p align="center"><img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/d266789f17a403dd3b734b38eb403fab.svg?invert_in_darkmode" align=middle width=365.57235pt height=39.8871pt/></p>
 
<p align="justify">where <img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/e7dc9be6ee00c810989d0325235b9647.svg?invert_in_darkmode" align=middle width=15.719220000000005pt height=26.76201000000001pt/> is the noise variance and <img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/957032ada3b5dead2ff9d51bd89cd07e.svg?invert_in_darkmode" align=middle width=22.197615000000003pt height=22.831379999999992pt/> is the output filtered image. If the noise variance is not given, the function uses the average of all the local estimated variances. Note that the above formula is the one actually used by the Matlab's <img src="https://rawgit.com/prittt/AdaptiveWienerFilter/master/svgs/a6e6fc428a6fd4f993180ca32c929e64.svg?invert_in_darkmode" align=middle width=59.141445pt height=21.683310000000006pt/> function (differently from what declared in the documentation <sup><a href="#WIENER2_MATLAB">2</a></sup>).</p> 

## References

<a name="WIENER_REFERENCE">[1] </a><em>Lim, Jae S., Two-Dimensional Signal and Image Processing, Englewood Cliffs, NJ, Prentice Hall, 1990, p. 538, equations 9.26, 9.27, and 9.29.</em>
</br>
<a name="WIENER2_MATLAB">[2] </a><em>https://it.mathworks.com/help/images/ref/wiener2.html (Accessed on 15 March 2017)</em>
