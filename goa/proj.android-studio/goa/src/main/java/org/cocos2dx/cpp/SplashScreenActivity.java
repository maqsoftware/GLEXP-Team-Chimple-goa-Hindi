package org.cocos2dx.cpp;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

import com.google.android.vending.expansion.downloader.Helpers;
import com.maq.xprize.chimple.hindi.R;

import java.io.File;
import java.io.IOException;
import java.util.zip.ZipFile;

import chimple.DownloadExpansionFile;
import utils.Zip;
import static chimple.DownloadExpansionFile.xAPKs;

public class SplashScreenActivity extends Activity {

    Intent intent = null;
    String expansionFilePath;
    File expansionFile;
    ZipFile expansionZipFile;
    Zip _zip;
    String unzipFilePath;
    File packageNameDir;
    int defaultFileVersion = 0;
    int mainFileVersion;
    int patchFileVersion;
    boolean extractionRequired = false;

    public static String getUnzippedExpansionFilePath() {
        return "/storage/emulated/0/Android/data/com.maq.xprize.chimple.hindi/files/";
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case 1: {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    new DownloadFile().execute(null, null, null);
                } else {
                    Toast.makeText(this, "Permission required!", Toast.LENGTH_LONG).show();
                    finish();
                }
            }
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        if (Build.VERSION.SDK_INT < 19) { // lower api
            View v = this.getWindow().getDecorView();
            v.setSystemUiVisibility(View.GONE);
        } else {
            //for new api versions.
            View decorView = this.getWindow().getDecorView();
            int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
            decorView.setSystemUiVisibility(uiOptions);
        }
        setContentView(R.layout.activity_splash_screen);

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            // Permission is not granted
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        } else {
            new DownloadFile().execute(null, null, null);
        }
    }

    /* function to call the main application after extraction */
    public void toCallApplication() {
        intent = new Intent(this, AppActivity.class);
        startActivity(intent);
        finish();
    }

    public void unzipFile() {
        int totalZipSize = getTotalExpansionFileSize();
        SharedPreferences sharedPref = getSharedPreferences("ExpansionFile", MODE_PRIVATE);
        mainFileVersion = sharedPref.getInt(getString(R.string.mainFileVersion), defaultFileVersion);
        patchFileVersion = sharedPref.getInt(getString(R.string.patchFileVersion), defaultFileVersion);
        try {
            for (DownloadExpansionFile.XAPKFile xf : xAPKs) {
                if (!xf.mIsMain || (xf.mFileVersion != mainFileVersion)) {
                    expansionFilePath = getExpansionFilePath(xf.mIsMain, xf.mFileVersion);
                    expansionFile = new File(expansionFilePath);
                    expansionZipFile = new ZipFile(expansionFile);
                    _zip = new Zip(expansionZipFile, this);
                    unzipFilePath = getUnzippedExpansionFilePath();
                    packageNameDir = new File(unzipFilePath);
                    if (xf.mIsMain) {
                        if (packageNameDir.exists()) {
                            DownloadExpansionFile.deleteDir(packageNameDir);
                        }
                        packageNameDir.mkdir();
                    }
                    _zip.unzip(unzipFilePath, totalZipSize, xf.mIsMain, xf.mFileVersion);
                    _zip.close();
                }
            }
            toCallApplication();
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    public int getTotalExpansionFileSize() {
        int totalExpansionFileSize = 0;
        ZipFile zipFile;
        try {
            for (DownloadExpansionFile.XAPKFile xf : xAPKs) {
                expansionFilePath = getExpansionFilePath(xf.mIsMain, xf.mFileVersion);
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                        99);
                expansionFile = new File(expansionFilePath);
                zipFile = new ZipFile(expansionFile);
                totalExpansionFileSize += zipFile.size();
            }
        } catch (IOException ie) {
            System.out.println("Couldn't get total expansion file size");
            System.out.println("Stacktrace: " + ie);
        }
        return totalExpansionFileSize;
    }

    public String getExpansionFilePath(boolean isMain, int fileVersion) {
        return Environment.getExternalStorageDirectory().toString() + "/Android/obb/" + Helpers.getPackageName(this) + File.separator +
                Helpers.getExpansionAPKFileName(this, isMain, fileVersion);
    }

    private class DownloadFile extends AsyncTask<String, Integer, String> {
        @Override
        protected String doInBackground(String... sUrl) {
            unzipFile();
            return null;
        }
    }
}

