#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>


int main(int argc, char **argv)
{
	cvNamedWindow( "Example", CV_WINDOW_AUTOSIZE );
	CvCapture* capture = cvCaptureFromCAM( 0 );
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 640 );
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 480 );
	IplImage* frame;
	if (!capture)
	{
		fprintf(stderr,"Cannot initialise camera!\n");
		return 1;
	}
	int key=0;
	while(key!='q') 
	{
		frame = cvQueryFrame( capture );
		if( !frame ) break;
		cvShowImage( "Example", frame );
		key = cvWaitKey(10);
	}
	cvReleaseCapture( &capture );
	cvDestroyWindow( "Example" );
	return 0;
}

