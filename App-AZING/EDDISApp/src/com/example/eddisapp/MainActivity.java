package com.example.eddisapp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


   
    
    /**Called on when the used presses the option button on home screen*/
    public void appsettings (View s){
    	Intent settings = new Intent(this, DisplaySettingsActivity.class);
    	startActivity (settings);
    }
    //Called on when user presses "upload" button on main menu
    public void uploadphoto (View u){
    	Intent upload = new Intent(this, UploadPhotoActivity);
    	startActivity (upload);
    }
    //Called on when user presses "take photo" button on main menu
    public void takephoto (View p){
    	Intent takephoto = new Intent(this, TakePhotoActivity);
    	startActivity (takephoto);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu items for use in the action bar
    	getMenuInflater().inflate(R.menu.main, menu);
    	MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main, menu);
        return super.onCreateOptionsMenu(menu);
    }
   
}
