/*
 * iphone-specific implementation of the s3eAdWhirl extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eAdWhirl_internal.h"
#include "s3eEdk.h"
#include "s3eEdk_iphone.h"

#import <UIKit/UIKit.h>

#import "AdWhirlDelegateProtocol.h"
#import "AdWhirlView.h"
#import "AdWhirlLog.h"

@interface s3eAdWhirlDelegate : NSObject<AdWhirlDelegate>

@property (assign) NSString *appID;

@end

@implementation s3eAdWhirlDelegate

@synthesize appID=_appID;

- (NSString *)adWhirlApplicationKey
{
	return self.appID;
}

- (UIViewController *)viewControllerForPresentingModalView
{
	return s3eEdkGetUIViewController();
}

- (void)adWhirlDidReceiveAd:(AdWhirlView *)adWhirlView
{
#ifdef DEBUG
	NSLog(@"s3eAdWhirl received ad");
	NSLog(adWhirlView.mostRecentNetworkName);
#endif
	s3eEdkCallbacksEnqueue(S3E_EXT_ADWHIRL_HASH, S3E_ADWHIRL_CALLBACK_AD_LOAD,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}

- (void)adWhirlDidFailToReceiveAd:(AdWhirlView *)adWhirlView usingBackup:(BOOL)yesOrNo
{
#ifdef DEBUG
	NSLog(@"s3eAdWhirl failed to receive ad");
	NSLog(adWhirlView.lastError.description);
#endif
	s3eEdkCallbacksEnqueue(S3E_EXT_ADWHIRL_HASH, S3E_ADWHIRL_CALLBACK_AD_FAIL,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);}

- (void)adWhirlReceivedNotificationAdsAreOff:(AdWhirlView *)adWhirlView
{
#ifdef DEBUG
	NSLog(@"s3eAdWhirl notified ads are off");
#endif
}

- (void)adWhirlWillPresentFullScreenModal
{
#ifdef DEBUG
	NSLog(@"s3eAdWhirl will present full screen ad");
#endif
	s3eEdkCallbacksEnqueue(S3E_EXT_ADWHIRL_HASH, S3E_ADWHIRL_CALLBACK_FULLSCREEN_BEGIN,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}

- (void)adWhirlDidDismissFullScreenModal
{
#ifdef DEBUG
	NSLog(@"s3eAdWhirl dismissed full screen ad");
#endif
	
	// we need to reset the controller's view here
	// otherwise we end up wit ha black screen
	UIViewController *controller = s3eEdkGetUIViewController();
	UIView *view = s3eEdkGetUIView();
	controller.view = view;
	s3eEdkCallbacksEnqueue(S3E_EXT_ADWHIRL_HASH, S3E_ADWHIRL_CALLBACK_FULLSCREEN_END,
						   NULL, 0, NULL, S3E_FALSE, NULL, NULL);
}
@end

s3eAdWhirlDelegate* delegate = nil;
AdWhirlView* adWhirlView = nil;

s3eResult s3eAdWhirlInit_platform()
{
    delegate = [[s3eAdWhirlDelegate alloc] init];
    return S3E_RESULT_SUCCESS;
}

void s3eAdWhirlTerminate_platform()
{
    [delegate release];
}

s3eResult s3eAdWhirlStart_platform(const char* appKey)
{
	[delegate setAppID:[NSString stringWithCString:appKey encoding:NSASCIIStringEncoding]];
#ifdef DEBUG
	NSLog(@"s3eAdWhirl starting");
	NSLog(delegate.appID);
#endif
	
	adWhirlView = [AdWhirlView requestAdWhirlViewWithDelegate:delegate];
	UIView *view = s3eEdkGetUIView();
	[view addSubview:adWhirlView];
	
    return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdWhirlRequestFreshAd_platform()
{
	if (adWhirlView == nil)
	{
		return S3E_RESULT_ERROR;
	}
	
	[adWhirlView requestFreshAd];
#ifdef DEBUG
	NSLog(@"s3eAdWhirlView requested fresh ad");
#endif
	
	return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdWhirlShow_platform()
{
	if (adWhirlView == nil)
	{
		return S3E_RESULT_ERROR;
	}
	adWhirlView.hidden = false;
	return S3E_RESULT_SUCCESS;
}

s3eResult s3eAdWhirlHide_platform()
{
	if (adWhirlView == nil)
	{
		return S3E_RESULT_ERROR;
	}
	adWhirlView.hidden = true;
	return S3E_RESULT_SUCCESS;
}
