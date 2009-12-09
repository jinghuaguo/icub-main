// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#ifndef _WATERSHEDOPERATOR_H_
#define _WATERSHEDOPERATOR_H_

#include <yarp/sig/Image.h>//#include <yarp/YARPImage.h>
#include <yarp/math/Math.h>//#include <yarp/YARPMath.h>

#include <ace/config.h>

//YARP include
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

//openCV include
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
//IPP include
#include <ipp.h>

//within Project Include
//#include <iCub/ImageProcessor.h>

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::sig::draw;

#include <iCub/ColorVQ.h>
#include <iCub/YARPBox.h>


/**
* Operator that manages the watershed operations (rain falling) and extracts blobs
* \author Francesco Rea
*/
class WatershedOperator {
	bool logpolar;
	int neighSize;
	int *neigh;
	int *neighL;
	int *neighR;
	int padding;
	int imageSize;
	int* tempRegion;
	/**
	* intensity value considered as a threshold
	*/
	PixelMono threshold;
	bool neighborhood8;
	int height, width;
	int widthStep;
	int watershedColor;
	int basinColor;

	
	
	//YARPLogpolar m_lp;
	ImageOf<PixelInt> downPos2;
	ImageOf<PixelInt> downPos;
	ImageOf<PixelMono> tmp;
	IplImage *tmpMsk;
	/**
	* reference to the colour quantizator
	*/
	ColorVQ colorVQ;
	/**
	* create the neighbourhood considering the 4 proximity or the 8 proximity
	*/
    void createNeighborhood(const int widthStep, const bool neigh8);
	//__OLD//void initBorderLUT(const int width, const int height);
	//__OLD//inline bool invalidNeighbor(const int currentPoint, const int currentNeighbor) const;
	//__OLD//inline bool validNeighbor(const int currentPoint, const int currentNeighbor) const;
	int markMinimas(ImageOf<PixelInt>& result);
	/**
	* starts the actual process or watershed (rain falling)
	*/
	void letsRain(ImageOf<PixelInt>& result);
	/**
	* find the neighbour with the minumum level of intensity
	*/
	void findLowerNeigh(const ImageOf<PixelMono>& src);
	void createTmpImage(const ImageOf<PixelMono>& src);

public:
	/**
	* destructor
	*/
	~WatershedOperator();
	/**
	* constructor
	*/
	WatershedOperator(const bool lp, const int width1, const int height1, const int wstep, const PixelMono th);
	/*
	* resize
	*/
	void resize(const int width1, const int height1, const int wstep, const PixelMono th);
	/**
	* set threashold
	*/
	inline void setThreshold(PixelMono th) {threshold=th;}
	//__OLD//bool apply(ImageOf<PixelMono>& srcdest);
	//__OLD//bool apply(const ImageOf<PixelMono>& src, ImageOf<PixelMono>& dest);

	/**
	* applies the rain watershed from the edge picture, and returns the tagged image of integer
	*/
	int apply(const ImageOf<PixelMono> &src, ImageOf<PixelInt> &result); //
	/**
	* applies the rain watershed from the edge picture, and returns the tagged image of integer (OLD)
	*/
	int applyOnOld(const ImageOf<PixelMono> &src, ImageOf<PixelInt> &result);
	void tags2Watershed(const ImageOf<PixelInt>& src, ImageOf<PixelMono>& dest);
	/**
	* find neighbours to the position x,y
	*/
	void findNeighborhood(ImageOf<PixelInt>& tagged, int x, int y, char *blobList);
	/**
	* extracts the connectivity graph
	*/
	void connectivityGraph(const ImageOf<PixelInt>& src, bool *matr, int max_tag);
	/**
	* get the first plane of the input image
	*/
	ImageOf<PixelMono>* getPlane ( ImageOf<PixelRgb>* src ); //
	// public attributes
	ImageOf<PixelMono> tSrc;
	ImageOf<PixelMono>* outputImage;
};

#endif //_WATERSHEDOPERATOR_H_