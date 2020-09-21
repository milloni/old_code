package com.example.user.modernartui;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;

public class MoreInfoDialog extends DialogFragment {
    private static final String TAG = MoreInfoDialog.class.getSimpleName();

    private LaunchWebsiteListener listener;

    public interface LaunchWebsiteListener {
        void onLaunchWebsite();
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            listener = (LaunchWebsiteListener) activity;
        } catch (ClassCastException e) {
            Log.d(TAG, "Activity must implement" + LaunchWebsiteListener.class.getSimpleName());
            e.printStackTrace();
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setTitle(R.string.want_to_learn);
        builder.setMessage(R.string.this_app_is_inpired);
        builder.setPositiveButton(R.string.dialog_yes, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                listener.onLaunchWebsite();
            }
        });
        builder.setNegativeButton(R.string.dialog_no, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dismiss();
            }
        });
        return builder.create();
    }
}
