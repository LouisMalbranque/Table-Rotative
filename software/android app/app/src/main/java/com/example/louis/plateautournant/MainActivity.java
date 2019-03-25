package com.example.louis.plateautournant;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.SpinnerAdapter;
import android.widget.Switch;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    Spinner spinnerMode;
    EditText accelerationNumber;
    EditText speedNumber;
    SeekBar accelerationSeekBar;
    SeekBar speedSeekBar;
    Switch directionSwitch;
    Button sendButton;
    TextView dataText;

    ArrayList<String> spinnerModeItems = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spinnerMode = findViewById(R.id.spinnerMode);

        accelerationNumber = findViewById(R.id.numberAcceleration);
        accelerationSeekBar = findViewById(R.id.seekbarAcceleration);

        speedNumber = findViewById(R.id.numberSpeed);
        speedSeekBar = findViewById(R.id.seekbarSpeed);

        directionSwitch = findViewById(R.id.directionSwitch);

        sendButton = findViewById(R.id.buttonSend);

        //dataText = findViewById(R.id.data);

        spinnerModeItems.add("Mode Temps Réel");
        spinnerModeItems.add("Mode Programmé");

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, spinnerModeItems);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinnerMode.setAdapter(adapter);
        adapter.setNotifyOnChange(true);

        spinnerMode.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                switch (position){
                    case 0:
                        RealTimeRotation realTimeRotation = new RealTimeRotation();
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment, realTimeRotation).commit();
                    case 1:
                        //realTimeRotation = new RealTimeRotation();
                        getSupportFragmentManager().beginTransaction().remove(getSupportFragmentManager().findFragmentById(R.id.fragment)).commit();
                    default:
                        break;

                }
            }
        });



        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                
            }
        });

    }
}
