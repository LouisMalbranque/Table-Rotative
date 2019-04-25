package com.example.application.Activité_n2.Fragments.SauvegardeBDD;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;


import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVR;
import com.example.application.Activité_n2.AjoutBDD.ajoutVR;
import com.example.application.R;
import com.example.application.objets.valeurReel;

public class SauvegardeReel extends Fragment implements ajoutVR{
    private ajoutBDDVR majoutAsyncTask;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        final View view = inflater.inflate(R.layout.fragment_sauvegarde_reel,container,false);


        return view;

    }

    @Override
    public void onStart() {
        super.onStart();
        final EditText accelerationEditText = getActivity().findViewById(R.id.AccelerationTempsReel);
        final EditText vitesseEditText = getActivity().findViewById(R.id.VitesseTempsReel);
        final Switch directionSwitch = getActivity().findViewById(R.id.DirectionTempsReel);
        final EditText stepsEditText = getActivity().findViewById(R.id.StepsTempsReel);
        final EditText rotation_numberEditText = getActivity().findViewById(R.id.Rotation_number_TempsReel);
        final Switch choix_rotationSwitch = getActivity().findViewById(R.id.choix_rotation_TempsReel);
        final Button oKButton = getView().findViewById(R.id.sauverReel);
        final EditText idRentre=getActivity().findViewById(R.id.IDrentreReel);

        majoutAsyncTask=new ajoutBDDVR(this);

        getView().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().remove(SauvegardeReel.this).addToBackStack(null).commit();
            }
        });

        oKButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                valeurReel nouvelEnregistrement = new valeurReel();
                nouvelEnregistrement.id=idRentre.getText().toString();
                nouvelEnregistrement.acceleration=accelerationEditText.getText().toString();

                    nouvelEnregistrement.direction=directionSwitch.isChecked();

                nouvelEnregistrement.speed=vitesseEditText.getText().toString();
                nouvelEnregistrement.tableSteps=stepsEditText.getText().toString();
                nouvelEnregistrement.rotationNumber=rotation_numberEditText.getText().toString();

                    nouvelEnregistrement.rotationMode=choix_rotationSwitch.isChecked();

                majoutAsyncTask.execute(nouvelEnregistrement);

            }
        });
    }

    @Override
    public void ajoutBDDvaleursR() {

        final Button save = getActivity().findViewById(R.id.save_temps_reel);
        final Button send = getActivity().findViewById(R.id.send_temps_reel);
        final Button charger = getActivity().findViewById(R.id.charger);
        save.setClickable(true);
        charger.setClickable(true);
        send.setClickable(true);
        getFragmentManager().beginTransaction().remove(SauvegardeReel.this).commit();
    }

}
