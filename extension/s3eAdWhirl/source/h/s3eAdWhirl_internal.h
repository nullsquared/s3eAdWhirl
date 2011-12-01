/*
Internal header for the s3eAdWhirl extension.

This file should be used for any common function definitions etc that need to
be shared between the platform-dependent and platform-indepdendent parts of
this extension.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EADWHIRL_H_INTERNAL
#define S3EADWHIRL_H_INTERNAL

#include "s3eTypes.h"
#include "s3eAdWhirl.h"
#include "s3eAdWhirl_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eAdWhirlInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eAdWhirlInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eAdWhirlTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eAdWhirlTerminate_platform();
s3eResult s3eAdWhirlStart_platform(const char* appKey);

s3eResult s3eAdWhirlRequestFreshAd_platform();

s3eResult s3eAdWhirlShow_platform();

s3eResult s3eAdWhirlHide_platform();


#endif /* S3EADWHIRL_H_INTERNAL */