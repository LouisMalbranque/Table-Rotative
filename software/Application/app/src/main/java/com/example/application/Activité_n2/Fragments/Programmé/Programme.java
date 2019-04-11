package com.example.application.Activité_n2.Fragments.Programmé;


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
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_programme, container, false);

        Button save = v.findViewById(R.id.save);
        Button send = v.findViewById(R.id.send);

        EditText text = v.findViewById(R.id.text);

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().replace(R.id.MaintActivity,Menu.menu).addToBackStack(null).commit();
            }
        });

        return v;

    }

}
