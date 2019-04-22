package com.example.application.Activité_n2.Fragments.Focus;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import com.example.application.R;

import java.util.ArrayList;

/**
 * A simple {@link Fragment} subclass.
 */
public class FocusParametre extends Fragment {



    static public FocusParametre focusParametre = new FocusParametre();
    static public Button sendFocus;
    static public Button reset;
    static public int compteurPas;
    static public TextView compteur;
    static public Spinner spinnerCamera;
    static boolean spinnerFirstTime=true;
    static public ArrayList<String> spinnerCameraItems = new ArrayList<String>();
    static public int numeroCamera;

    public FocusParametre() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_focus_parametre, container, false);
        sendFocus = v.findViewById(R.id.sendFocus);
        reset = v.findViewById(R.id.reset);
        compteur = v.findViewById(R.id.compteur);
        compteur.setEnabled(false);

        spinnerCamera=v.findViewById(R.id.spinnerFocus);

        if (spinnerFirstTime){
            spinnerCameraItems.add("Camera 1");
            spinnerCameraItems.add("Camera 2");
            spinnerCameraItems.add("Camera 3");
            spinnerCameraItems.add("Camera 4");
            spinnerCameraItems.add("Camera 5");
            spinnerCameraItems.add("Camera 6");
            spinnerCameraItems.add("Camera 7");
            spinnerCameraItems.add("Camera 8");
            spinnerCameraItems.add("Camera 9");

            spinnerFirstTime=false;
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(getContext(), R.layout.custom_spinner, spinnerCameraItems);
        adapter.setDropDownViewResource(R.layout.custom_spinner);
        spinnerCamera.setAdapter(adapter);
        adapter.setNotifyOnChange(true);
        spinnerCamera.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switch (position){
                    case 1:
                        numeroCamera = 1;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 2:
                        numeroCamera = 2;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 3:
                        numeroCamera = 3;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 4:
                        numeroCamera = 4;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 5:
                        numeroCamera = 5;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 6:
                        numeroCamera = 6;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 7:
                        numeroCamera = 7;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 8:
                        numeroCamera = 8;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    case 9:
                        numeroCamera = 9;
                        compteurPas=0;
                        compteur.setText(Integer.toString(compteurPas));
                        break;
                    default:
                        break;

                }
            }
            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });


        sendFocus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().remove(FocusParametre.focusParametre).addToBackStack(null).commit();
            }
        });

        reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                compteurPas = 0;
                compteur.setText(Integer.toString(compteurPas));

            }
        });


        return v;
    }

}
