#include "opencv2/opencv.hpp"

/*
 * Objective: This is a very simple to implement minimal verision of augmented
 * reality.  Show dots at a fixed distance above a chessboard independent of
 * the orientation of the camera relative to the chessboard.  Use solvePnp()
 * to compute the extrinsics matrix.
 *
 * Prerequisites: CameraMatrices.yaml from CameraCalibrationMono.cpp
 */


int main(int argc, const char * argv[]) {
    
    // Retrieve the camera matrix.
    cv::FileStorage fs;
    fs.open("CameraMatrices.yaml", cv::FileStorage::READ);
    
    if (!fs.isOpened())
    {
        std::cout << "Cannot find CameraMatrices.yaml" << std::endl;
        exit(1);
    }
    
    cv::Mat cameraMatrix, distCoeffs;
    cv::Size chessboardSize;
    cv::Size imageSize;
    
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;
    fs["chessboardSize"] >> chessboardSize;
    fs["imageSize"] >> imageSize;
    fs.release();
    
    std::cout << "cameraMatrix" << std::endl << cameraMatrix << std::endl;
    std::cout << "distCoeffs" << std::endl << distCoeffs << std::endl;
    std::cout << "chessboardSize" << std::endl << chessboardSize << std::endl;
    std::cout << "imageSize" << std::endl << imageSize << std::endl;
    
    // Make object points that represent the coordinate space each frame defined
    // relative to the chessboard.  They are provided to solvePnP along with the
    // u,v coordinates in the image plane to find the rotation and translation
    // of the camera relative to the chessboard.
    
    // Also create some augmented points that are 1 unit above the chessboard.
    std::vector<cv::Point3f> objectPoints, objectPointsAugmented;
    
    for (int r=0; r<chessboardSize.height; r++)
        for (int c=0; c<chessboardSize.width; c++)
        {
            objectPoints.push_back(cv::Point3f(c, r, 0.0f)); // Point3f(x,y,z)
            objectPointsAugmented.push_back(cv::Point3f(c, r, -1.0f));
        }
    
    // Capture and process frames, looking for a chessboard and drawing virtual
    // points "above" the chessboard.
    cv::Mat frame;
    
    cv::VideoCapture cap(0);
    
    // Set the dimensions to be consistent with the calibration images.
    cap.set(CV_CAP_PROP_FRAME_WIDTH, imageSize.width);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, imageSize.height);
    
    do
    {
        cap.read(frame);
        
        // Find the location of the chessboard corners.
        std::vector<cv::Point2f> corners;
        bool patternFound = cv::findChessboardCorners(frame, chessboardSize, corners);
        
        if (patternFound)
        {
            cv::drawChessboardCorners(frame, chessboardSize, cv::Mat(corners), patternFound);
            
            // By defining the chessboard as the definition of the world coordinate space
            // and the location of the chessboard corners in the image, determine the
            // extrinsics matrix using solvePnP to get the rotation and translation of the
            // camera relative to the chessboard.
            cv::Mat rvec, tvec;
            bool foundPnP = cv::solvePnP(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);
            
            if (foundPnP)
            {
                // Show the numeric position of the camera relative to the chessboard.
                //                std::cout << rvec << " " << tvec << std::endl;
                
                // Project the augmented points through the extrinsics matrix (rvec and tvec)
                // into the 2-D image plane.
                std::vector<cv::Point2f> cornersAugmented;
                cv::projectPoints(objectPointsAugmented, rvec, tvec, cameraMatrix, distCoeffs, cornersAugmented);
                
                // Draw the augmented points onto the frame.
                for (int i=0; i<cornersAugmented.size(); i++)
                {
                    cv::circle(frame, cornersAugmented[i], 5, cv::Scalar(0,255,0), -1);
                    cv::line(frame, cornersAugmented[i], corners[i], cv::Scalar(0,255,0));
                }
            }
        }
        
        cv::imshow("Camera", frame);
        
        // Press ESC to exit.
    } while (cv::waitKey(1) != 27);
    
    return 0;
}
