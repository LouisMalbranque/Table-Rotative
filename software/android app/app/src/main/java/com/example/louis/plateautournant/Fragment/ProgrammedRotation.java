package com.example.louis.plateautournant.Fragment;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.SeekBar;

import com.example.louis.plateautournant.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class ProgrammedRotation extends android.app.Fragment {


    private SeekBar timeBetweenPhotosSeekbar;
    private EditText timeBetweenPhotosNumber;
    private EditText cameraNumber;
    private EditText frameNumber;

    public ProgrammedRotation() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v= inflater.inflate(R.layout.programmed_rotation,container,false);

        timeBetweenPhotosSeekbar = v.findViewById(R.id.timeBetweenPhotosSeekbar);
        timeBetweenPhotosNumber = v.findViewById(R.id.timeBetweenPhotosNumber);
        cameraNumber = v.findViewById(R.id.cameraNumber);
        frameNumber = v.findViewById(R.id.frameNumber);

        timeBetweenPhotosSeekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                timeBetweenPhotosNumber.setText(Integer.toString(timeBetweenPhotosSeekbar.getProgress()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        timeBetweenPhotosNumber.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                try{
                    int position=timeBetweenPhotosNumber.length();
                    timeBetweenPhotosNumber.setSelection(position);
                    timeBetweenPhotosSeekbar.setProgress(Integer.parseInt(s.toString()));
                    if (timeBetweenPhotosNumber.length()==0){
                        timeBetweenPhotosSeekbar.setProgress(0);
                        timeBetweenPhotosNumber.setText(0);
                    }
                } catch(Exception ex) {ex.printStackTrace();}

            }
        });
        return v;
    }

    public EditText getTimeBetweenPhotosNumber() {
        return timeBetweenPhotosNumber;
    }

    public EditText getCameraNumber() {
        return cameraNumber;
    }

    public EditText getFrameNumber() {
        return frameNumber;
    }
}
