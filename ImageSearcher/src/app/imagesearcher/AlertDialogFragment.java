package app.imagesearcher;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;

public class AlertDialogFragment extends DialogFragment 
{
	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) 
	{
		AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
		builder.setMessage("Would You like to enable the tutorial?").setPositiveButton("Yes",new DialogInterface.OnClickListener() 
		{	
			@Override
			public void onClick(DialogInterface dialog, int id) 
			{// Turn on tutorial
			}
		}).setNegativeButton("No", new DialogInterface.OnClickListener() 
		{
			
			@Override
			public void onClick(DialogInterface dialog, int id) {
				// Turn off tutorial
				}
			});
		return builder.create();
	}
}
