package com.example.application.Activité_n2.Fragments.SauvegardeBDD;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVR;
import com.example.application.Activité_n2.AjoutBDD.ajoutVR;
import com.example.application.Activité_n2.Fragments.Temps_réel.TempsReel;
import com.example.application.R;
import com.example.application.objets.valeurReel;

public class SauvegardeReel extends Fragment implements ajoutVR{

    private ajoutBDDVR majoutAsyncTask;

    String accelerationEditText;
    String vitesseEditText;
    String directionSwitch;
    String stepsEditText;
    String rotation_numberEditText;
    String choix_rotationSwitch;

    Button oKButton;
    EditText idRentre;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_sauvegarde_reel,container,false);

        accelerationEditText = getArguments().getString("AccelerationSaveTempsReel");
        vitesseEditText = getArguments().getString("VitesseSaveTempsReel");
        directionSwitch = getArguments().getString("DirectionSaveTempsReel");
        stepsEditText = getArguments().getString("TableStepsSaveTempsReel");
        rotation_numberEditText = getArguments().getString("RotationNumberSaveTempsReel");
        choix_rotationSwitch = getArguments().getString("RotationModeSaveTempsReel");

        oKButton = view.findViewById(R.id.sauverReel);
        idRentre=view.findViewById(R.id.IDrentreReel);

        return view;

    }

    @Override
    public void onStart() {
        super.onStart();


        majoutAsyncTask=new ajoutBDDVR(this);

        oKButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                valeurReel nouvelEnregistrement = new valeurReel();
                nouvelEnregistrement.id=idRentre.getText().toString();
                nouvelEnregistrement.acceleration=accelerationEditText;

                if (directionSwitch=="1"){
                    nouvelEnregistrement.direction=true;
                }else{
                    nouvelEnregistrement.direction=false;
                }

                nouvelEnregistrement.speed=vitesseEditText;
                nouvelEnregistrement.tableSteps=stepsEditText;
                nouvelEnregistrement.rotationNumber=rotation_numberEditText;

                if (choix_rotationSwitch=="1"){
                    nouvelEnregistrement.rotationMode=true;
                }else{
                    nouvelEnregistrement.rotationMode=false;
                }


                majoutAsyncTask.execute(nouvelEnregistrement);

            }
        });
    }

    @Override
    public void ajoutBDDvaleursR(Integer bool) {

        if(bool.equals(false)){
            Toast.makeText(getContext(),"Impossible d'ajouter, supprimez un élément", Toast.LENGTH_LONG).show();
        }
        getFragmentManager().beginTransaction().replace(R.id.fragment, TempsReel.temps_reel).addToBackStack(null).commit();
    }

}
