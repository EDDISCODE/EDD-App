package app.imagesearcher;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;

public class Use extends Activity {
	private static final int GET_REQUEST = 1337;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_use);
		getPhoto();
	}
	private void getPhoto()
	{
		Intent get = new Intent(Intent.ACTION_PICK, Uri.parse("content://gallery"));
		startActivityForResult(get,GET_REQUEST);
	}

	protected void onActivityResult(int requestCode, int resultCode,Intent data)
	{
		if(requestCode == GET_REQUEST)
		{
			if(resultCode == RESULT_OK)
			{
				//Do something with picture.
			}
		}
	}
	public void back(View view)
	{
		Intent home = new Intent(this, HomeActivity.class);
		startActivity(home);
	}
}
