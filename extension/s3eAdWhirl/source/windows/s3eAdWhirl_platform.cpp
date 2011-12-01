/*
 * windows-specific implementation of the s3eAdWhirl extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eAdWhirl_internal.h"

s3eResult s3eAdWhirlInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eAdWhirlTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eResult s3eAdWhirlStart_platform(const char* appKey)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdWhirlRequestFreshAd_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdWhirlShow_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eAdWhirlHide_platform()
{
    return S3E_RESULT_ERROR;
}
