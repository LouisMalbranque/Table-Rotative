package com.example.application.Activité_n2;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;
import android.widget.Spinner;

import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargmentVP;
import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.R;

public class MainActivity extends AppCompatActivity {

    private Menu menu = new Menu();
    private static Context sContext;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sContext = getApplicationContext();
        setContentView(R.layout.activity_main);


    }

    public static Context getContext() {
        return sContext;
    }
}
