/*Copyright(c) 2017-2018 Federico Bolelli, Costantino Grana
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :

*Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and / or other materials provided with the distribution.

* Neither the name of AdaptiveWienerFilter nor the names of its
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

#include "WienerFilter.h"

using namespace cv;

double WienerFilterImpl(const Mat& src, Mat& dst, double noiseVariance, const Size& block){

	assert(("Invalid block dimensions", block.width % 2 == 1 && block.height % 2 == 1 && block.width > 1 && block.height > 1));
	assert(("src and dst must be one channel grayscale images", src.channels() == 1, dst.channels() == 1));
	
	int h = src.rows;
	int w = src.cols;

	dst = Mat1b(h, w);

	Mat1d means, sqrMeans, variances;
	Mat1d avgVarianceMat; 

	boxFilter(src, means, CV_64F, block, Point(-1, -1), true, BORDER_REPLICATE);
	sqrBoxFilter(src, sqrMeans, CV_64F, block, Point(-1, -1), true, BORDER_REPLICATE);

	Mat1d means2 = means.mul(means);
	variances = sqrMeans - (means.mul(means));

	if (noiseVariance < 0){
		// I have to estimate the noiseVariance
		reduce(variances, avgVarianceMat, 1, CV_REDUCE_SUM, -1);
		reduce(avgVarianceMat, avgVarianceMat, 0, CV_REDUCE_SUM, -1);
		noiseVariance = avgVarianceMat(0, 0) / (h*w);
	}

	for (int r = 0; r < h; ++r){
		// get row pointers
		uchar const * const srcRow = src.ptr<uchar>(r);
		uchar * const dstRow = dst.ptr<uchar>(r);
		double * const varRow = variances.ptr<double>(r);
		double * const meanRow = means.ptr<double>(r);
		for (int c = 0; c < w; ++c) {
			dstRow[c] = saturate_cast<uchar>(
				meanRow[c] + max(0., varRow[c] - noiseVariance) / max(varRow[c], noiseVariance) * (srcRow[c] - meanRow[c])
			);
		}
	}

	return noiseVariance;
}

void WienerFilter(const Mat& src, Mat& dst, double noiseVariance, const Size& block){
	WienerFilterImpl(src, dst, noiseVariance, block);
	return;
}


double WienerFilter(const Mat& src, Mat& dst, const Size& block){
	return WienerFilterImpl(src, dst, -1, block);
}
