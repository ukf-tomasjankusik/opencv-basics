# opencv-basics
Simple demonstrations of basic use of OpenCV

### 3D to 2D Projection Equation
Many of the functions of the calib3d module relate to the pinhole camera model found in the Detailed Description on the
[Camera Calibration](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html) page and below.  Often, you'll have some of the values and want to know which function to use to solve for the unknown.  The table below shows inputs in *italic* and outputs in **bold**.


```
  | u |    | fx   0  cx || R R R Tx|| X |
s | v |  = |  0  fy  cy || R R R Ty|| Y |
  | 1 |    |  0   0   1 || R R R Tz|| Z |
                                    | 1 |
```


| Function           | objPts           | pts1/2  | M  | distort | R | T | E | F | H | R1/R2 | P1/P2 | Q | misc
| ------------------ |:-------------:|:-----:|:------:|:-----:|:--:|:--:| -- | -- | -- | -- | -- | -- | ----
| **calib3d**
| [calibrateCamera](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga3207604e4b1a1758aa66acb6ed5aa65d)    | *X*   | *1* | **X** | **X** | **X** | **X** |
| [projectPoints](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga1019495a2c8d1743ed5cc23fa0daff8c)      | *X*   | **1** | *X* | *X* | *X* | *X*
| [stereoCalibrate](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga246253dcc6de2e0376c599e7d692303a)    | *X*   | *1&2* | **1&2** | **1&2** | **X** | **X** | **X** | **X**
| [findEssentialMat](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga0c86f6478f36d5be6e450751bbf4fec0)   |       | *1&2*  | *foc/pp* |  |  |  | **X** |
| [findFundamentalMat](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga8e25cb8c64d8baa4749ca28ff1b0866a)   |       | *1&2*  |  |  |  |  |  | **X** |
| [findHomography](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga4abc2ece9fab9398f2e560d53c8c9780)   |       | *1&2*  |  |  |  |  |  |  | **X** |
| [stereoRectify](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga617b1685d4059c6040827800e72ad2b6)   |     |  | *1&2*  |*1&2*  | *X* | *X*  |  |  |  | **1&2** | **1&2** | **X** |
| [stereoRectifyUncalibrated](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#gaadc5b14471ddc004939471339294f052) |  | *1&2*  |  |  |  |  |  | *X* | **1&2**
| [computeCorrespondEpilines](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga19e3401c94c44b47c229be6e51d158b7) |  | *1*  |  |  |  |  |  | *X* 
| [reprojectImageTo3D](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga1bc1152bd57d63bc524204f21fde6e02) |  | *disparity* |  |  |  |  |  |  |  |  |  | *X* | **image3d**
|  |  |  |  |  |  |  |  |  |  |  |  |  | 
| [decomposeEssentialMat](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga54a2f5b3f8aeaf6c76d4a31dece85d5d) |  |  |  |  | *1&2* | *X* | **X** |  |  |  |  |  | 
| [decomposeHomographyMat](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga7f60bdff78833d1e3fd6d9d0fd538d92) |  |  | *X(K)* |  | **multiple** | **multiple** |  |  | *X* |  |  |  | 
| [decomposeProjectionMatrix](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#gaaae5a7899faa1ffdf268cd9088940248) |  |  | **X** |  | **X** | **X** |  |  |  |  | *P* |  | 
|  |  |  |  |  |  |  |  |  |  |  |  |  | 
| [recoverPose](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#gadb7d2dfcc184c1d2f496d8639f4371c0) |  | *1&2* | foc/pp |  | **X** | **X** | *X* |  |  |  |  |  | 
| [triangulatePoints](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#gad3fc9a0c82b08df034234979960b778c) |  | *1&2* |  |  |  |  |  |  |  |  | *P1&P2* |  | **points4D**
| [solvePnP](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga549c2075fac14829ff4a58bc931c033d) | *X* | *1* | *X* | *X* | **X** | **X** |  |  |  |  |  |  | 
| [solvePnPRansac](http://docs.opencv.org/3.2.0/d9/d0c/group__calib3d.html#ga50620f0e26e02caa2e9adc07b5fbf24e) | *X* | *1* | *X* | *X* | **X** | **X** |  |  |  |  |  |  | 
|   |  |  |  |  |  |  |  |  |  |  |  |  | 
| **core Operations on Arrays**
| [perspectiveTransform](http://docs.opencv.org/3.2.0/d2/de8/group__core__array.html#gad327659ac03e5fd6894b90025e6900a7) |  | *X* |  |  |  |  |  |  | *X* |  |  |  | **points**
|   |  |  |  |  |  |  |  |  |  |  |  |  | 
| **imgproc Geometric Image Transformation**
| [initUndistortRectifyMap](http://docs.opencv.org/3.2.0/da/d54/group__imgproc__transform.html#ga7dfb72c9cf9780a347fbe3d1c47e5d5a) |  |  | *X* | *X* |  |  |  |  |  | *X* | *X* |  | **mapx/y**
| [remap](http://docs.opencv.org/3.2.0/da/d54/group__imgproc__transform.html#gab75ef31ce5cdfb5c44b6da5f3b908ea4) |  | *srcImg* |  |  |  |  |  |  |  |  |  |  | *mapx/y***dstImg**
| [undistort](http://docs.opencv.org/3.2.0/da/d54/group__imgproc__transform.html#ga69f2545a8b62a6b0fc2ee060dc30559d) |  | *srcImg* | *X* | *X* |  |  |  |  |  |  |  |  | **dstImg**
| [undistortPoints](http://docs.opencv.org/3.2.0/da/d54/group__imgproc__transform.html#ga55c716492470bfe86b0ee9bf3a1f0f7e) |  | *X* | *X* | *X* |  |  |  |  |  | *X* | *X* |  | **points**
| [warpPerspective](http://docs.opencv.org/3.2.0/da/d54/group__imgproc__transform.html#gaf73673a7e8e18ec6963e3774e6a94b87) |  | *srcImg* |  |  |  |  |  |  | *X* |  |  |  | **dstImg**


