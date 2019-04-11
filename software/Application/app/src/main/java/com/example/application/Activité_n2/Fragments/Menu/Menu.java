package com.example.application.Activité_n2.Fragments.Menu;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.Activité_n2.Fragments.Temps_réel.Temps_reel;
import com.example.application.R;

import java.util.ArrayList;

/**
 * A simple {@link Fragment} subclass.
 */
public class Menu extends Fragment {

    static public Menu menu = new Menu();

    private Spinner spinnerMode;
    private ArrayList<String> spinnerModeItems = new ArrayList<String>();
    private boolean spinnerFirstTime=true;


    public Menu() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v= inflater.inflate(R.layout.fragment_menu,container,false);
        
        spinnerMode=v.findViewById(R.id.spinner);

        if (spinnerFirstTime){
            spinnerModeItems.add("New order");
            spinnerModeItems.add("Mode Programmé");
            spinnerModeItems.add("Mode Temps Réel");
            spinnerFirstTime=false;
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(getActivity(), R.layout.custom_spinner, spinnerModeItems);
        adapter.setDropDownViewResource(R.layout.custom_spinner);
        spinnerMode.setAdapter(adapter);
        adapter.setNotifyOnChange(true);
        spinnerMode.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switch (position){
                    case 1:
                        getFragmentManager().beginTransaction().replace(R.id.MaintActivity, Programme.programme).commit();
                        spinnerMode.setSelection(0);
                        break;
                    case 2:
                        getFragmentManager().beginTransaction().replace(R.id.MaintActivity, Temps_reel.temps_reel).commit();
                        spinnerMode.setSelection(0);
                        break;
                    default:
                        break;

                }
            }
            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });

        return v;
    }
}
