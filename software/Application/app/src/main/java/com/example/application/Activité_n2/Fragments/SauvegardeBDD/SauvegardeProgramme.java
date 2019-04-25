package com.example.application.Activité_n2.Fragments.SauvegardeBDD;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVP;
import com.example.application.Activité_n2.AjoutBDD.ajoutVP;
import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

public class SauvegardeProgramme extends Fragment implements ajoutVP{

    private ajoutBDDVP majoutAsyncTask;

    String accelerationEditText;
    String vitesseEditText;
    String directionSwitch;
    String stepsEditText;
    String frameEditText;
    String camera_numberEditText;
    String pause_between_cameraEditText;
    String focus_stackingSwitch;

    Button oKButton;
    EditText idRentre;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_sauvegarde_programme,container,false);

        accelerationEditText = getArguments().getString("AccelerationSaveProgramme");
        vitesseEditText = getArguments().getString("VitesseSaveProgramme");
        directionSwitch = getArguments().getString("DirectionSaveProgramme");
        stepsEditText = getArguments().getString("TableStepsSaveProgramme");
        frameEditText = getArguments().getString("FrameSaveProgramme");
        camera_numberEditText = getArguments().getString("CameraSaveProgramme");
        pause_between_cameraEditText = getArguments().getString("TempsEntrePhotosSaveProgramme");
        focus_stackingSwitch = getArguments().getString("FocusSaveProgramme");

        oKButton = view.findViewById(R.id.sauver);
        idRentre=view.findViewById(R.id.IDrentre);

        return view;

    }
    @Override
    public void onStart() {
        super.onStart();

        majoutAsyncTask=new ajoutBDDVP(this);

        oKButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                valeurProgramme nouvelEnregistrement = new valeurProgramme();
                nouvelEnregistrement.acceleration = accelerationEditText;
                System.out.println("nouvelle enregistrement : "+nouvelEnregistrement.acceleration);
                nouvelEnregistrement.camera_number=camera_numberEditText;
                if (directionSwitch=="1"){
                    nouvelEnregistrement.direction=true;
                }else{
                    nouvelEnregistrement.direction=false;
                }
                nouvelEnregistrement.frame=frameEditText;
                nouvelEnregistrement.id=idRentre.getText().toString();
                nouvelEnregistrement.speed= vitesseEditText;
                nouvelEnregistrement.tableSteps=stepsEditText;
                nouvelEnregistrement.timeBetweenPhotosNumber=pause_between_cameraEditText;

                if (focus_stackingSwitch=="1"){
                    nouvelEnregistrement.focusStacking=true;
                }else{
                    nouvelEnregistrement.focusStacking=false;
                }

                majoutAsyncTask.execute(nouvelEnregistrement);

            }
        });
    }

    @Override
    public void ajoutBDDvaleursP(Boolean bool) {
        if(bool.equals(false)){
            Toast.makeText(getContext(),"Impossible d'ajouter, supprimez un élément", Toast.LENGTH_LONG).show();
        }
        getFragmentManager().beginTransaction().replace(R.id.fragment, Programme.programme).addToBackStack(null).commit();
    }
}
