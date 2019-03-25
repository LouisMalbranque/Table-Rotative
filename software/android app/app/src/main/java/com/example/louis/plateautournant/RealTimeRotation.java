package com.example.louis.plateautournant;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.AppCompatEditText;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.zip.Inflater;

public class RealTimeRotation extends Fragment {


    private String timeText = "Time Mode";
    private String turnText = "Turn Mode";

    private Switch switchModeTurnTime;
    private EditText numberText;
    private SeekBar seekNumber;
    private TextView text;

    private boolean modeTime = true;

    public RealTimeRotation() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v= inflater.inflate(R.layout.real_time_rotation,container,false);

        switchModeTurnTime = v.findViewById(R.id.switchTimeTurn);
        numberText = v.findViewById(R.id.numberTurnTime);
        seekNumber = v.findViewById(R.id.seekBarTimeTurn);
        text = v.findViewById(R.id.timeTurnText);

        switchModeTurnTime.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                numberText.setText("0");
                seekNumber.setProgress(0);
                modeTime=!modeTime;
                if (modeTime){
                    seekNumber.setMax(10);
                    text.setText(timeText);
                }else{
                    seekNumber.setMax(10);
                    text.setText(turnText);

                }
            }
        });

        seekNumber.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                numberText.setText(Integer.toString(seekNumber.getProgress()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        return v;
    }

}
