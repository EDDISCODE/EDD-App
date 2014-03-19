package app.imagesearcher;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;

public class Take extends Activity 
{
	private Uri fileUri;
	private static final int CAMERA_REQUEST = 1337;
	private static final int MEDIA_TYPE_IMAGE = 1;
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_take);
		Intent take = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
		fileUri = getOutputMediaFileUri(MEDIA_TYPE_IMAGE);
		take.putExtra(MediaStore.EXTRA_OUTPUT,fileUri);
		startActivityForResult(take,CAMERA_REQUEST);
	}
	private Uri getOutputMediaFileUri(int type)
	{
		return Uri.fromFile(getOutputMediaFile(type));
	}
	private File getOutputMediaFile(int type)
	{
		File mediaStorageDir = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES), "ImageSearcher");
		if(! mediaStorageDir.exists()){
			if(! mediaStorageDir.mkdirs()){
				Log.d("ImageSeacher","failed to create directory");
				return null;
			}
		}
		String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
		File mediaFile;
		if(type == MEDIA_TYPE_IMAGE){
			mediaFile = new File(mediaStorageDir.getPath() + File.separator + "IMG_"+timeStamp +".jpg");
		}
		else if(type == MEDIA_TYPE_IMAGE){
			mediaFile = new File(mediaStorageDir.getPath() + File.separator + "VID_"+timeStamp +".mp4");
		}
		else{return null;}
		return mediaFile;
	}
}