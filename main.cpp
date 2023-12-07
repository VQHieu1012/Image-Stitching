#include "surflib.h"
// #include "kmeans.h"
#include <ctime>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <getopt.h>
#include <opencv2/core/core_c.h>
using namespace cv;

std::mutex img_lock;

int THREAD_EXIT_FLAG = false;
int capture_count=0;
int imshow_count=0;
int stitch_count=0;


int mainStitch(int blend_mode, const char* src1, const char* src2)
{
    IplImage *img_0, *img_1;
    cv::Mat warpped, stitched, mask2;
    std::vector<cv::Mat> warp_mask;

    img_0 = cvLoadImage(src1);
    img_1 = cvLoadImage(src2);

    // CvCapture* capture_0 = cvCaptureFromCAM(0);
    // CvCapture* capture_1 = cvCaptureFromCAM(1);

    // img1 = cvQueryFrame(capture_1);
    // img2 = cvQueryFrame(capture_0);

    clock_t start = clock();
    IpVec ipts1, ipts2;
    surfDetDes(img_0,ipts1,0,false,4,4,2,0.0001f);
    surfDetDes(img_1,ipts2,0,false,4,4,2,0.0001f);


    IpPairVec matches;
    clock_t t0 = clock();
    getMatches(ipts1,ipts2,matches);
    clock_t t1 = clock();
    cv::Mat H = findHom(matches);
    clock_t t2 = clock();

    std::cout << "Keypoint matching took: " << float(t1 - t0) / CLOCKS_PER_SEC << " seconds" << std::endl;
    std::cout << "Finding homography took: " << float(t2 - t1) / CLOCKS_PER_SEC << " seconds" << std::endl;

    if(blend_mode == 0)
        warpped = getWarpped(img_1, H);
    else
    {
        warp_mask = getWarpped_blend(img_1, H);
        mask2 = warp_mask[1];
        warpped = warp_mask[0];
    }
    clock_t t3 = clock();
    std::cout<< "Warping took: " << float(t3 - t2) / CLOCKS_PER_SEC << std::endl;

    if(blend_mode == 0)
        stitched = getCvStitch(img_0, warpped);
    else
        stitched = getBlended(img_0, img_1, matches, warpped, mask2);
    
    clock_t t4 = clock();
    std::cout<< "Stitching (blending) took: " << float(t4 - t3) / CLOCKS_PER_SEC << std::endl;
    std::cout << "----------------------------------------------" << endl;
    std::cout << "Took: " << float(t4 - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    cvNamedWindow("stitched", CV_WINDOW_NORMAL );
    cv::imshow("stitched", stitched);
    cvWaitKey(0);

    imwrite("./output/output.jpg", stitched);

    return 0;
}


int mainVideo(int blend_mode, int resolution_mode, const char* src1, const char* src2)
{
    VideoCapture capture_0, capture_1;
    capture_0.open(src1);
    capture_1.open(src2);

    
    if(!capture_0.isOpened() || !capture_1.isOpened())
        throw "Error when reading videos";

    IpVec ipts_0, ipts_0_cpy;
    IpVec ipts_1, ipts_1_cpy;
    IplImage *img_0 = NULL;
    IplImage *img_1 = NULL;
    IplImage *img_0_ptr, *img_1_ptr;
    cv::Mat H, stitched, H_mean, *stitched_cpy=NULL;
    IpPairVec matches;
    CvSize sz;
    clock_t start, end;

    int H_count=0, fps_count=0;

    Mat frame_0;
    Mat frame_1;

    cvNamedWindow("stitched", CV_WINDOW_AUTOSIZE);
    clock_t sss = clock_t();
    IplImage ipl_0, ipl_1;
    // int n = 1;
    while(1) 
    {   
        
        // if(img_0==NULL || img_1==NULL)
        //     cout << "image null" << endl;
        //     continue;
        
        // cout<< "start while"<<endl;
        try{
            capture_0 >> frame_0;
            capture_1 >> frame_1;
            // n++;
            // if (n % 5 != 0)
            //     continue;

            ipl_0 = cvIplImage(frame_0);
            img_0 = cvCloneImage(&ipl_0);

            ipl_1 = cvIplImage(frame_1);
            img_1 = cvCloneImage(&ipl_1);

            img_0_ptr = img_0;
            img_1_ptr = img_1;

            sz.width = (int)(img_0_ptr->width*1.f*resolution_mode/1080);  
            sz.height = (int)(img_0_ptr->height*1.f*resolution_mode/1080);  
            IplImage* desc_0 = cvCreateImage(sz, img_0_ptr->depth, img_0_ptr->nChannels);
            IplImage* desc_1 = cvCreateImage(sz, img_0_ptr->depth, img_0_ptr->nChannels);  
            cvResize(img_0_ptr, desc_0, CV_INTER_CUBIC);
            cvResize(img_1_ptr, desc_1, CV_INTER_CUBIC);
            img_0_ptr = desc_0;
            img_1_ptr = desc_1;

            surfDetDes(img_0_ptr, ipts_0, 0, true, 4, 4, 2, 0.002f);        
            surfDetDes(img_1_ptr, ipts_1, 0, true, 4, 4, 2, 0.002f);        

            start = clock();
            getMatches(ipts_0, ipts_1, matches);
            end = clock();
            std::cout<< "Keypoint matching took: " << float(end - start) / CLOCKS_PER_SEC << std::endl;

            start = clock();
            H = findHom(matches);
            end = clock();
            std::cout<< "Homography took: " << float(end - start) / CLOCKS_PER_SEC << std::endl;

            
            H_count++;

            if(H_count == 1)
                H_mean = H;
            else
            {
                H_mean = 0.9*H_mean + 0.1*H;
            }   

            cv::Mat warpped, mask2;
            std::vector<cv::Mat> warp_mask;

            start = clock();
            if(blend_mode == 0){
                warpped = getWarpped(img_1_ptr, H_mean);
                // stitched = getCvStitch(img_0_ptr, warpped);}
            }
            else
            {   
                // cout << "blend mode = 1"<< endl;
                warp_mask = getWarpped_blend(img_1_ptr, H_mean);
                mask2 = warp_mask[1];
                warpped = warp_mask[0];
                // stitched = getBlended(img_0_ptr, img_1_ptr, matches, warpped, mask2);
            }
            end = clock();
            std::cout<< "Warping took: " << float(end - start) / CLOCKS_PER_SEC << std::endl;

            start = clock();
            if(blend_mode == 0)
                stitched = getCvStitch(img_0_ptr, warpped);
            else{
                stitched = getBlended(img_0_ptr, img_1_ptr, matches, warpped, mask2);
            }
            end = clock();
            std::cout<< "Stitching took: " << float(end - start) / CLOCKS_PER_SEC << std::endl;

            imshow_count++;

            start = clock();
            img_lock.lock();

            IplImage ipl = cvIplImage(stitched);

            IplImage* display = cvCloneImage(&ipl);

            img_lock.unlock();

            //int fps_count = min(min(stitch_count, capture_count), imshow_count);

            // cout << stitch_count*1.f/(clock()-sss)* CLOCKS_PER_SEC << ", " \
            //             << capture_count*1.f/(clock()-sss)* CLOCKS_PER_SEC\
            //              << ", " << imshow_count*1.f/(clock()-sss)* CLOCKS_PER_SEC << endl;

            // drawFPS(display);

            cvShowImage("stitched", display);
            
            cvReleaseImage(&display);

            end = clock();
            std::cout<< "Imshow took: " << float(end - start) / CLOCKS_PER_SEC << std::endl;            
            std::cout << "----------------------------------------------" << endl;
        }
        catch(cv::Exception& e)
        {   
            std::cerr<<  std::endl;
        }

        // If ESC key pressed exit loop
        if( (cvWaitKey(10) & 255) == 27 ) break;
    }

    THREAD_EXIT_FLAG = true;
    // cvReleaseCapture(&capture_0);
    capture_0.release();
    capture_1.release();
    
    cvDestroyWindow("stitched");
    return 0;
}

//-------------------------------------------------------

int main(int argc, char* argv[]) 
{
    int debug_flag, compile_flag, size_in_bytes;

    static struct option longopts[] =
    {
        {"mode", required_argument, NULL, 'm'},
        {"blend_mode", no_argument, NULL, 'b'},
        {"src1", required_argument, NULL, 'L'}, // left src file
        {"src2", required_argument, NULL, 'R'}, // right src file
        {NULL, 0, NULL, 0}
    };
    
    int idx = 0;
    char c;
    int mode = -1, blend_mode = 0, resolution_mode = 480;
    std::string src = "", src1 = "", src2 = "";
    
    while((c = getopt_long(argc, argv, "m:br:S:L:R:", longopts, &idx)) != -1)
    {
        switch (c)
        {
            case 'm':
                mode = atoi(optarg);
                break;
            case 'b':
                blend_mode = 1;
                break;
            case 'L':
                src1 = optarg;
                break;
            case 'R':
                src2 = optarg;
                break;
        }
    }
    // Check mandatory parameters:
    if (mode == -1) {
        printf("Mode (-m) option is mandatory\n");
        exit(1);
    }

    switch (mode)
    {

        case 1 : // run static image match between a pair of images
            if (src1 == "") src1 = "../images/1.png"; // if not provided, use sample image
            if (src2 == "") src2 = "../images/2.png"; // if not provided, use sample image
            return mainStitch(blend_mode, src1.c_str(), src2.c_str());

                
        case 2 : // run image stitching with local video files
            if (src1 == "") src1 = "./video_left.mp4"; // if not provided, use sample video
            if (src2 == "") src2 = "./video_right.mp4"; // if not provided, use sample video
            return mainVideo(blend_mode, resolution_mode, src1.c_str(), src2.c_str());

        default : 
            printf("Include mode number. \n");
            exit(1);
    }
}
