package com.example.application.Activité_n2.Fragments.SauvegardeBDD;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;

import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVP;
import com.example.application.Activité_n2.AjoutBDD.ajoutVP;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

public class SauvegardeProgramme extends Fragment implements ajoutVP{
    private ajoutBDDVP majoutAsyncTask;
    private ajoutVP mListener;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        final View view = inflater.inflate(R.layout.fragment_sauvegarde_programme,container,false);


        return view;

    }
    @Override
    public void onStart() {
        super.onStart();
        final EditText accelerationEditText = getActivity().findViewById(R.id.AccelerationProgramme);
        final EditText vitesseEditText = getActivity().findViewById(R.id.VitesseProgramme);
        final Switch directionSwitch = getActivity().findViewById(R.id.DirectionProgramme);
        final EditText stepsEditText = getActivity().findViewById(R.id.StepsProgramme);
        final EditText frameEditText = getActivity().findViewById(R.id.FrameProgramme);
        final EditText camera_numberEditText = getActivity().findViewById(R.id.Camera_Number_Programme);
        final EditText pause_between_cameraEditText = getActivity().findViewById(R.id.Pause_between_camera_Programme);
        final Switch focus_stackingSwitch = getActivity().findViewById(R.id.Focus_stacking_Programme);
        final Button oKButton = getView().findViewById(R.id.sauver);
        final EditText idRentre=getActivity().findViewById(R.id.IDrentre);

        majoutAsyncTask=new ajoutBDDVP(this);

        getView().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().remove(SauvegardeProgramme.this).addToBackStack(null).commit();
            }
        });

        oKButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                valeurProgramme nouvelEnregistrement = new valeurProgramme();
                nouvelEnregistrement.acceleration=accelerationEditText.getText().toString();
                nouvelEnregistrement.camera_number=camera_numberEditText.getText().toString();
                if(directionSwitch.isChecked()){
                    nouvelEnregistrement.direction="1";
                }
                else
                {
                    nouvelEnregistrement.direction="0";
                }
                nouvelEnregistrement.frame=frameEditText.getText().toString();
                nouvelEnregistrement.id=idRentre.getText().toString();
                nouvelEnregistrement.speed= vitesseEditText.getText().toString();
                nouvelEnregistrement.tableSteps=stepsEditText.getText().toString();
                nouvelEnregistrement.timeBetweenPhotosNumber=pause_between_cameraEditText.getText().toString();
                if(focus_stackingSwitch.isChecked()){
                    nouvelEnregistrement.focusStacking="1";
                }
                else
                {
                    nouvelEnregistrement.focusStacking="0";
                }
                majoutAsyncTask.execute(nouvelEnregistrement);

            }
        });
    }

    @Override
    public void ajoutBDDvaleursP() {
        getFragmentManager().beginTransaction().remove(SauvegardeProgramme.this).commit();
    }
}
