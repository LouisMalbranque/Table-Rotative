package com.example.application.Activité_n2.Fragments.Programmé;


import android.annotation.SuppressLint;
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
public class Programme extends Fragment {

    static public Programme programme = new Programme();

    public Programme() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_programme, container, false);

        Button save = v.findViewById(R.id.save_programme);
        Button send = v.findViewById(R.id.send_programme);

        EditText text = v.findViewById(R.id.text);

        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //sauvegarder dans la BDD
            }
        });

        send.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("ResourceType")
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().remove(Programme.programme).addToBackStack(null).commit();
            }
        });

        return v;

    }

}
