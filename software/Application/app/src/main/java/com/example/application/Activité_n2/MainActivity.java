package com.example.application.Activité_n2;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.R;

public class MainActivity extends AppCompatActivity {

    private Menu menu = new Menu();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getSupportFragmentManager().beginTransaction().add(R.id.MaintActivity, Menu.menu).addToBackStack(null).commit();

    }
}
