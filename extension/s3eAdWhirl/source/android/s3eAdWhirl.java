/*
java implementation of the s3eAdWhirl extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import com.adwhirl.AdWhirlLayout;

import android.widget.RelativeLayout;
import android.view.View;

class s3eAdWhirl
{
	AdWhirlLayout adWhirlLayout;
	public int s3eAdWhirlStart(String appKey)
	{
		final String appKeyFinal = appKey;
		LoaderActivity.m_Activity.runOnUiThread(new Runnable() {
			@Override
			public void run()
			{
				adWhirlLayout = new AdWhirlLayout(LoaderActivity.m_Activity, appKeyFinal);
				
				int diWidth = 320;
				int diHeight = 52;
				float density = LoaderActivity.m_Activity.getResources().getDisplayMetrics().density;

				//adWhirlLayout.setAdWhirlInterface(this);
				adWhirlLayout.setMaxWidth((int)(diWidth * density));
				adWhirlLayout.setMaxHeight((int)(diHeight * density));
				
				RelativeLayout.LayoutParams adWhirlLayoutParams = new RelativeLayout.LayoutParams(
					RelativeLayout.LayoutParams.FILL_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
				adWhirlLayoutParams.addRule(RelativeLayout.CENTER_HORIZONTAL);
				LoaderActivity.m_Activity.addContentView(adWhirlLayout, adWhirlLayoutParams);
			}
		});
		return LoaderAPI.S3E_RESULT_SUCCESS;
	}
	public int s3eAdWhirlRequestFreshAd()
	{
		if (adWhirlLayout == null)
		{
			return LoaderAPI.S3E_RESULT_ERROR;
		}
		adWhirlLayout.rotateThreadedNow();
		return LoaderAPI.S3E_RESULT_ERROR;
	}
	public int s3eAdWhirlShow()
	{
		if (adWhirlLayout == null)
		{
			return LoaderAPI.S3E_RESULT_ERROR;
		}
		adWhirlLayout.setVisibility(View.VISIBLE);
		return LoaderAPI.S3E_RESULT_SUCCESS;
	}
	public int s3eAdWhirlHide()
	{
		if (adWhirlLayout == null)
		{
			return LoaderAPI.S3E_RESULT_ERROR;
		}
		adWhirlLayout.setVisibility(View.INVISIBLE);
		return LoaderAPI.S3E_RESULT_SUCCESS;
	}
}
