/****************************************************************************
 *
 * $Id$
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2014 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 * Acquire images using OpenCV cv::VideoCapture.
 *
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/

#include <visp3/core/vpConfig.h>

/*!
  \example grabOpenCV-2.cpp

  \brief Example of framegrabbing using OpenCV cv::VideoCapture class.

*/

#include <iostream>

#include <visp3/core/vpConfig.h>

#if defined(VISP_HAVE_OPENCV) && (VISP_HAVE_OPENCV_VERSION >= 0x020100)

#include <visp3/core/vpDisplayOpenCV.h>
#include <visp3/core/vpImage.h>
#include <visp3/core/vpImageConvert.h>
#include <visp3/sensor/vpOpenCVGrabber.h>


// usage: binary <device name>
// device name: 0 is the default to dial with the first camera, 
//              1 to dial with a second camera attached to the computer
int main(int argc, char** argv)
{
  try {
    int device = 0;
    if (argc > 1)
      device = atoi(argv[1]);

    std::cout << "Use device: " << device << std::endl;
    cv::VideoCapture cap(device); // open the default camera
#if (VISP_HAVE_OPENCV_VERSION >= 0x030000)
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
#else
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
#endif
    if(!cap.isOpened())  // check if we succeeded
      return -1;
    cv::Mat frame;
    cap >> frame; // get a new frame from camera

    std::cout << "Image size: "
#if (VISP_HAVE_OPENCV_VERSION >= 0x030000)
              << (int)cap.get(cv::CAP_PROP_FRAME_WIDTH) << " "
              << (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
#else
              << (int)cap.get(CV_CAP_PROP_FRAME_WIDTH) << " "
              << (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
#endif

    //vpImage<vpRGBa> I; // for color images
    vpImage<unsigned char> I; // for gray images
    vpImageConvert::convert(frame, I);

    vpDisplayOpenCV d(I);

    for(;;) {
      cap >> frame; // get a new frame from camera

      // Convert the image in ViSP format and display it
      vpImageConvert::convert(frame, I);
      vpDisplay::display(I);
      vpDisplay::flush(I);
      if (vpDisplay::getClick(I, false)) // a click to exit
        break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
  }
  catch(vpException e) {
    std::cout << "Catch an exception: " << e << std::endl;
    return 1;
  }
}

#else
int main()
{
  std::cout << "OpenCV is not available..." << std::endl;
}

#endif
