package com.example.louis.plateautournant.Fragment;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.AppCompatEditText;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import com.example.louis.plateautournant.R;

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
        seekNumber.setMax(10);
        text = v.findViewById(R.id.timeTurnText);
        numberText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                try{
                    int position=numberText.length();
                    numberText.setSelection(position);
                    seekNumber.setProgress(Integer.parseInt(s.toString()));
                    if (numberText.length()==0){
                        seekNumber.setProgress(0);
                        numberText.setText(0);
                    }
                } catch(Exception ex) {}

            }
        });

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
