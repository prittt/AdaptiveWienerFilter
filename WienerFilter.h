/*Copyright(c) 2017 Federico Bolelli
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :

*Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and / or other materials provided with the distribution.

* Neither the name of YACCLAB nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Federico Bolelli: federico.bolelli@unimore.it
*/

#pragma once

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <assert.h>

/** @brief Implementation of the adaptive Wiener filter

This function applies to the src image the adaptive Wiener filter and 
store the result in the dst image. The formula that will be apply is 
the following one: 

dst(x, y) = u + max(0, s^2 - v^2)(src(x, y) - u) / max(s^2, v^2)

where u is the local mean, s^2 is the variance at NxM neighborhood
around each pixel (they depend on block dimension) e v^2 is the noise 
variance calculated as the average of all the local estimated variances
if not given.

@param[in] src input grayscale image (Mat1b)
@param[out] dst output grayscale image (Mat1b)
@param[in] block dimension of the block (width, height) to use in order
			to compute the filtering process, default is 5x5

@return estimated noise variance
*/
double WienerFilter(const cv::Mat& src, cv::Mat& dst, const cv::Size& block = cv::Size(5, 5));

/** @overload 

@param[in] src input grayscale image (Mat1b)
@param[out] dst output grayscale image (Mat1b)
@param[in] noiseVariance noise variance to use in order to calculate Wiener filter (must be positive)
@param[in] block dimension of the block (width, height) to use in order
			to compute the filtering process, default is 5x5

@return estimated noise variance
*/
void WienerFilter(const cv::Mat& src, cv::Mat& dst, double noiseVariance, const cv::Size& block = cv::Size(5, 5));