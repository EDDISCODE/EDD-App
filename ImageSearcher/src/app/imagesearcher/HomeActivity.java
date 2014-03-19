package app.imagesearcher;

import android.app.Activity;
import android.app.DialogFragment;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
public class HomeActivity extends Activity 
{
	SharedPreferences mPrefs;
	public boolean firstRun()
	{
		return mPrefs.getBoolean("firstRun",true);
	}
	public void setRunned()
	{
		SharedPreferences.Editor edit = mPrefs.edit();
		edit.putBoolean("firstRun",false);
		edit.commit();
	}
	
	public void firstRunPrefences()
	{
		Context mContext = this.getApplicationContext();
		mPrefs = mContext.getSharedPreferences("myAppPref",0);
	}
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_home);
		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN)
		{
			getActionBar().setDisplayHomeAsUpEnabled(true);
		}
		if(firstRun())
		{
			dialogFrag();
		}
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.home, menu);
		return true;
	}
	public void settings(View view)
	{
		Intent intent = new Intent(this, Setting.class);
		startActivity(intent);
	}
	public void take(View view)
	{
		Intent intent = new Intent(this, Take.class);
		startActivity(intent);
	}
	public void use(View view)
	{
		Intent intent = new Intent(this, Use.class);
		startActivity(intent);
	}
	public void dialogFrag()
	{
		DialogFragment newFragment = new AlertDialogFragment();
		newFragment.show(getFragmentManager(),"tutorial");
	}
}
