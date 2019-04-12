package com.example.louis.plateautournant;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.view.View;
import android.view.inputmethod.InputConnection;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;

import com.example.louis.plateautournant.BDD.valeurProgramme;
import com.example.louis.plateautournant.Bluetooth.Peripherique;
import com.example.louis.plateautournant.Fragment.ProgrammedRotation;
import com.example.louis.plateautournant.Fragment.RealTimeRotation;
import com.example.louis.plateautournant.UtilisationBDD.ajoutBDDVP;
import com.example.louis.plateautournant.UtilisationBDD.ajoutValeur;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity{


    //ajoutValeur mListener = this;

    private String data ="";

    private Spinner spinnerMode;
    private EditText accelerationNumber;
    private EditText speedNumber;
    private EditText stepsNumber;
    private SeekBar accelerationSeekBar;
    private SeekBar speedSeekBar;
    private Switch directionSwitch;
    private Button sendButton;
    private Button saveButton;

    private ArrayList<String> spinnerModeItems = new ArrayList<String>();

    private RealTimeRotation realTimeRotation = new RealTimeRotation();
    private ProgrammedRotation programmedRotation = new ProgrammedRotation();

    private Peripherique peripherique;

    private int mode;
    private int direction;
    private int acceleration;
    private int speed;
    private int rotation_number;
    private int rotation_time;
    private int frame;
    private int camera_number;
    private int pause_between_camera;
    private int steps;

    private int minimumValSpeed=100;
    private int maximumValSpeed=400;
    private int minimumValAcceleration=100;
    private int maximumValAcceleration=4000;
    private static Context sContext;
    private ajoutBDDVP majoutAsyncTask;
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        sContext = getApplicationContext();
        setContentView(R.layout.activity_main);

        peripherique = Peripherique.peripherique;
        spinnerMode = findViewById(R.id.spinnerMode);
        accelerationNumber = findViewById(R.id.numberAcceleration);
        accelerationSeekBar = findViewById(R.id.seekbarAcceleration);
        speedNumber = findViewById(R.id.numberSpeed);
        speedSeekBar = findViewById(R.id.seekbarSpeed);
        directionSwitch = findViewById(R.id.directionSwitch);
        sendButton = findViewById(R.id.buttonSend);
        stepsNumber=findViewById(R.id.stepstableNumber);
        saveButton=findViewById(R.id.save);
        accelerationNumber.setFilters(new InputFilter[]{new MinMaxFilter(minimumValAcceleration-100,maximumValAcceleration)});
        accelerationNumber.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                try{
                    int position=accelerationNumber.length();
                    accelerationNumber.setSelection(position);
                    accelerationSeekBar.setProgress((Integer.parseInt(s.toString()))-minimumValAcceleration);
                } catch(Exception ex) {}
            }
        });
        accelerationNumber.setOnFocusChangeListener(new View.OnFocusChangeListener(){
            @Override
            public void onFocusChange(View v, boolean hasFocus){
                if (hasFocus==false){
                    if (accelerationNumber.length()<=2)
                    {
                        accelerationNumber.setText("100");

                        InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(accelerationNumber.getWindowToken(), 0);
                    }
                }
            }
        });
        accelerationSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                try{
                    if (accelerationNumber.length()<=2) {
                        accelerationNumber.setText(accelerationSeekBar.getProgress());
                    } else{
                        accelerationNumber.setText(Integer.toString(accelerationSeekBar.getProgress()+minimumValAcceleration));
                    }
                }catch (Exception ex){}

            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                if (accelerationNumber.length()<=2){
                    accelerationNumber.setText(Integer.toString(minimumValAcceleration));
                    accelerationSeekBar.setProgress(minimumValAcceleration);
                }
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        accelerationNumber.clearFocus();

        speedNumber.setFilters(new InputFilter[]{new MinMaxFilter((minimumValSpeed-100),maximumValSpeed)});
        speedNumber.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                try{
                    int position=speedNumber.length();
                    speedNumber.setSelection(position);
                    speedSeekBar.setProgress((Integer.parseInt(s.toString()))-minimumValSpeed);
                } catch(Exception ex) {}

            }
        });
        speedNumber.setOnFocusChangeListener(new View.OnFocusChangeListener(){
            @Override
            public void onFocusChange(View v, boolean hasFocus){
                if (hasFocus==false){
                    if (speedNumber.length()<=2)
                    {
                        speedNumber.setText("100");

                        InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(speedNumber.getWindowToken(), 0);
                    }
                }
            }
        });
        speedSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                try{
                    if (speedNumber.length()<=2) {
                        speedNumber.setText(speedSeekBar.getProgress());
                    } else{
                        speedNumber.setText(Integer.toString(speedSeekBar.getProgress()+minimumValSpeed));
                    }
                }catch (Exception ex){}

            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                if (speedNumber.length()<=2){
                    speedNumber.setText(Integer.toString(minimumValSpeed));
                    speedSeekBar.setProgress(minimumValSpeed);
                }
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        speedNumber.clearFocus();


        spinnerModeItems.add("Mode Programmé");
        spinnerModeItems.add("Mode Temps Réel");
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.custom_spinner, spinnerModeItems);
        adapter.setDropDownViewResource(R.layout.custom_spinner);
        spinnerMode.setAdapter(adapter);
        adapter.setNotifyOnChange(true);
        spinnerMode.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switch (position){
                    case 0:
                        //realTimeRotation = new RealTimeRotation();
                        mode=0;
                        getFragmentManager().beginTransaction().replace(R.id.fragment, programmedRotation).commit();
                        break;
                    case 1:
                        mode=1;
                        getFragmentManager().beginTransaction().replace(R.id.fragment, realTimeRotation).commit();
                        break;
                    default:
                        break;

                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!directionSwitch.isChecked()){
                    direction=0;
                }
                else{
                    direction=1;
                }

                acceleration = Integer.parseInt(accelerationNumber.getText().toString());
                speed = Integer.parseInt(speedNumber.getText().toString());

                switch(mode){
                    case 0:
                        rotation_number = -1;
                        rotation_time = -1;
                        frame = Integer.parseInt(programmedRotation.getFrameNumber().getText().toString());
                        camera_number = Integer.parseInt(programmedRotation.getCameraNumber().getText().toString());
                        pause_between_camera = Integer.parseInt(programmedRotation.getTimeBetweenPhotosNumber().getText().toString());
                        break;
                    case 1:
                        if (realTimeRotation.isModeTime()){
                            rotation_number=-1;
                            rotation_time=Integer.parseInt(realTimeRotation.getNumberText().getText().toString());
                        }else{
                            rotation_number=Integer.parseInt(realTimeRotation.getNumberText().getText().toString());
                            rotation_time=-1;
                        }
                        frame=-1;
                        camera_number=-1;
                        pause_between_camera=-1;
                        break;

                }

                steps=Integer.parseInt(stepsNumber.getText().toString());

                data="";
                data +=Integer.toString(mode)+",";
                data +=Integer.toString(acceleration)+",";
                data +=Integer.toString(speed)+",";
                data +=Integer.toString(direction)+",";
                data +=Integer.toString(rotation_number)+",";
                data +=Integer.toString(rotation_time)+",";
                data +=Integer.toString(frame)+",";
                data +=Integer.toString(camera_number)+",";
                data +=Integer.toString(pause_between_camera)+",";
                data +=Integer.toString(steps);

                peripherique.envoyer(data);
            }
        });

        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                majoutAsyncTask=new ajoutBDDVP();

                switch(mode){
                    case 0:
                        valeurProgramme nouvelEnregistrement = new valeurProgramme();
                        nouvelEnregistrement.id="exemple1";
                        nouvelEnregistrement.frame = programmedRotation.getFrameNumber().getText().toString();
                        nouvelEnregistrement.camera_number = programmedRotation.getCameraNumber().getText().toString();
                        nouvelEnregistrement.timeBetweenPhotosNumber = programmedRotation.getTimeBetweenPhotosNumber().getText().toString();
                        nouvelEnregistrement.acceleration = accelerationNumber.getText().toString();
                        nouvelEnregistrement.speed = speedNumber.getText().toString();
                        if (!directionSwitch.isChecked()){
                            nouvelEnregistrement.direction="0";
                        }
                        else{
                            nouvelEnregistrement.direction="1";
                        }
                        majoutAsyncTask.execute(nouvelEnregistrement);
                        break;
                    /*case 1:
                        if (realTimeRotation.isModeTime()){
                            rotation_number=-1;
                            rotation_time=Integer.parseInt(realTimeRotation.getNumberText().getText().toString());
                        }else{
                            rotation_number=Integer.parseInt(realTimeRotation.getNumberText().getText().toString());
                            rotation_time=-1;
                        }

                        break;*/

                }

            }
        });
    }

    public static Context getContext() {
        return sContext;
    }

}