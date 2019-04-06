package com.example.louis.plateautournant.Fragment;


import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.AppCompatEditText;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import com.example.louis.plateautournant.Bluetooth.Peripherique;
import com.example.louis.plateautournant.MinMaxFilter;
import com.example.louis.plateautournant.R;

import org.w3c.dom.Text;

import java.util.zip.Inflater;

public class RealTimeRotation extends android.app.Fragment {


    private String timeText = "Time Mode";
    private String turnText = "Turn Mode";

    private Switch switchModeTurnTime;
    private EditText numberText;
    private SeekBar seekNumber;
    private TextView text;
    private ImageButton backward;
    private ImageButton backward2;
    private ImageButton forward;
    private ImageButton forward2;

    private int minimumValMode=1;

    private boolean modeTime = true;

    public RealTimeRotation() {
        // Required empty public constructor
    }

    public EditText getNumberText() {
        return numberText;
    }

    public boolean isModeTime() {
        return modeTime;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v= inflater.inflate(R.layout.real_time_rotation,container,false);

        switchModeTurnTime = v.findViewById(R.id.switchTimeTurn);
        numberText = v.findViewById(R.id.numberTurnTime);
        seekNumber = v.findViewById(R.id.seekBarTimeTurn);
        seekNumber.setMax(9);
        text = v.findViewById(R.id.timeTurnText);
        backward = v.findViewById(R.id.backward);
        backward2 = v.findViewById(R.id.backward2);
        forward = v.findViewById(R.id.forward);
        forward2 = v.findViewById(R.id.forward2);

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
                    seekNumber.setProgress((Integer.parseInt(s.toString()))-1);
                } catch(Exception ex) {}

            }
        });
        numberText.setOnFocusChangeListener(new View.OnFocusChangeListener(){
            @Override
            public void onFocusChange(View v, boolean hasFocus){
                System.out.println("test");
                System.out.println(Integer.parseInt(numberText.getText().toString()));
                if (hasFocus==false){
                    if (numberText.getText().equals(0)){
                        numberText.setText("1");

                        InputMethodManager imm = (InputMethodManager) getActivity().getApplicationContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(v.getWindowToken(), 0);
                    }
                }
            }
        });
        seekNumber.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                numberText.setText((Integer.toString(seekNumber.getProgress()+1)));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        switchModeTurnTime.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                numberText.setText("1");
                seekNumber.setProgress(0);
                modeTime=!modeTime;
                if (modeTime){
                    seekNumber.setMax(9);
                    text.setText(timeText);
                }else{
                    seekNumber.setMax(99);
                    text.setText(turnText);

                }
            }
        });

        forward2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data="";
                data +=Integer.toString(1)+",";  //mode
                data +=Integer.toString(400)+",";  //acceleration
                data +=Integer.toString(400)+","; //speed
                data +=Integer.toString(0)+","; //direction
                data +=Integer.toString(10)+","; //rotation number
                data +=Integer.toString(-1)+","; //rotation time
                data +=Integer.toString(-1)+","; //frame
                data +=Integer.toString(-1)+","; //camera number
                data +=Integer.toString(-1)+","; //pause between camera
                data +=Integer.toString(1); //steps
                Peripherique.peripherique.envoyer(data);
            }
        });
        forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data="";
                data +=Integer.toString(1)+",";  //mode
                data +=Integer.toString(400)+",";  //acceleration
                data +=Integer.toString(400)+","; //speed
                data +=Integer.toString(0)+","; //direction
                data +=Integer.toString(1)+","; //rotation number
                data +=Integer.toString(-1)+","; //rotation time
                data +=Integer.toString(-1)+","; //frame
                data +=Integer.toString(-1)+","; //camera number
                data +=Integer.toString(-1)+","; //pause between camera
                data +=Integer.toString(1); //steps
                Peripherique.peripherique.envoyer(data);
            }
        });
        backward2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data="";
                data +=Integer.toString(1)+",";  //mode
                data +=Integer.toString(400)+",";  //acceleration
                data +=Integer.toString(400)+","; //speed
                data +=Integer.toString(1)+","; //direction
                data +=Integer.toString(10)+","; //rotation number
                data +=Integer.toString(-1)+","; //rotation time
                data +=Integer.toString(-1)+","; //frame
                data +=Integer.toString(-1)+","; //camera number
                data +=Integer.toString(-1)+","; //pause between camera
                data +=Integer.toString(1); //steps
                Peripherique.peripherique.envoyer(data);
            }
        });
        backward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data="";
                data +=Integer.toString(1)+",";  //mode
                data +=Integer.toString(400)+",";  //acceleration
                data +=Integer.toString(400)+","; //speed
                data +=Integer.toString(1)+","; //direction
                data +=Integer.toString(1)+","; //rotation number
                data +=Integer.toString(-1)+","; //rotation time
                data +=Integer.toString(-1)+","; //frame
                data +=Integer.toString(-1)+","; //camera number
                data +=Integer.toString(-1)+","; //pause between camera
                data +=Integer.toString(1); //steps
                Peripherique.peripherique.envoyer(data);
            }
        });
        return v;
    }

}
