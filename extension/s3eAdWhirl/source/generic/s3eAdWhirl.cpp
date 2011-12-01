/*
Generic implementation of the s3eAdWhirl extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eAdWhirl_internal.h"
s3eResult s3eAdWhirlInit()
{
    //Add any generic initialisation code here
    return s3eAdWhirlInit_platform();
}

void s3eAdWhirlTerminate()
{
    //Add any generic termination code here
    s3eAdWhirlTerminate_platform();
}

s3eResult s3eAdWhirlStart(const char* appKey)
{
	return s3eAdWhirlStart_platform(appKey);
}

s3eResult s3eAdWhirlRequestFreshAd()
{
	return s3eAdWhirlRequestFreshAd_platform();
}

s3eResult s3eAdWhirlShow()
{
	return s3eAdWhirlShow_platform();
}

s3eResult s3eAdWhirlHide()
{
	return s3eAdWhirlHide_platform();
}
