package com.example.user.modernartui;

import android.app.FragmentManager;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity
        implements MoreInfoDialog.LaunchWebsiteListener {
    private static final String TAG                = MainActivity.class.getSimpleName();
    private static final String WEBSITE_URL_STRING = "http://moma.org/";
    private static final String[][] COLORS = {
            {"#FF00FF", "#00FF00"},
            {"#DFDFDF", "#DFDFDF"},
            {"#FFFF00", "#00FFFF"},
            {"#00FF00", "#FF00FF"},
            {"#DFDFDF", "#DFDFDF"}
    };
    private static final int[] VIEW_IDS = {
            R.id.layout1,
            R.id.layout2,
            R.id.layout3,
            R.id.layout4,
            R.id.layout5,
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initSeekBar();
        for (int i = 0; i < 5; i++) {
            View v = findViewById(VIEW_IDS[i]);
            assert v != null;
            v.setBackgroundColor(Color.parseColor(COLORS[i][0]));
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.options_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem menu) {
        switch (menu.getItemId()) {
            case R.id.option_more_information: displayDialog(); return true;
            default:                           return super.onOptionsItemSelected(menu);
        }
    }

    @Override
    public void onLaunchWebsite() {
        showWebsite(WEBSITE_URL_STRING);
    }

    private void displayDialog() {
        FragmentManager manager = getFragmentManager();
        MoreInfoDialog dialog = new MoreInfoDialog();
        dialog.show(manager, MoreInfoDialog.class.getSimpleName());
    }

    private void showWebsite(String url) {
        Log.i(TAG, "Entered showWebsite()");
        Uri webUri = Uri.parse(url);
        Intent intent = new Intent(Intent.ACTION_VIEW, webUri);
        if (intent.resolveActivity(getPackageManager()) != null) {
            startActivity(intent);
        } else {
            Toast.makeText(getApplicationContext(), R.string.error_webpage,
                    Toast.LENGTH_SHORT).show();
        }
    }

    private void initSeekBar() {
        final SeekBar bar = (SeekBar) findViewById(R.id.seekBar);
        assert bar != null;
        bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                setBackground(progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void setBackground(int progress) {
        for (int i = 0; i < 5; i++) {
            View v = findViewById(VIEW_IDS[i]);
            int x = Color.parseColor(COLORS[i][0]);
            int y = Color.parseColor(COLORS[i][1]);
            assert v != null;
            v.setBackgroundColor(colorInBetween(x, y, progress));
        }
    }

    // ratio between 0 and 100
    private int colorInBetween(int x, int y, int ratio) {
        final int xr = Color.red(x);
        final int xg = Color.green(x);
        final int xb = Color.blue(x);
        final int yr = Color.red(y);
        final int yg = Color.green(y);
        final int yb = Color.blue(y);

        final int zr = (yr - xr);
        final int zg = (yg - xg);
        final int zb = (yb - xb);
        float fratio = ratio / 100.0f;

        final int _r = (int) Math.floor(fratio * zr);
        final int _g = (int) Math.floor(fratio * zg);
        final int _b = (int) Math.floor(fratio * zb);

        return Color.rgb(xr + _r, xg + _g, xb + _b);
    }
}
