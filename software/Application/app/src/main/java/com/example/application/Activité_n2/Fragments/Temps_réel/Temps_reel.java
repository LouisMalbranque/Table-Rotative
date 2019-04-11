package com.example.application.Activité_n2.Fragments.Temps_réel;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class Temps_reel extends Fragment {

    static public Temps_reel temps_reel = new Temps_reel();

    public Temps_reel() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_temps_reel, container, false);

        Button save = v.findViewById(R.id.save_temps_reel);
        Button send = v.findViewById(R.id.send_temps_reel);

        EditText text = v.findViewById(R.id.text);

        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //sauvegarder dans la BDD
            }
        });

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().replace(R.id.MaintActivity, Menu.menu).addToBackStack(null).commit();
            }
        });

        return v;

    }

}
