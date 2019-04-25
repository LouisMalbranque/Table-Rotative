package com.example.application.Activité_n2.Fragments.SauvegardeBDD;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.Toast;

import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVP;
import com.example.application.Activité_n2.AjoutBDD.ajoutVP;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

public class SauvegardeProgramme extends Fragment implements ajoutVP{
    private ajoutBDDVP majoutAsyncTask;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        final View view = inflater.inflate(R.layout.fragment_sauvegarde_programme,container,false);


        return view;

    }
    @Override
    public void onStart() {
        super.onStart();
        final Button save = getActivity().findViewById(R.id.save_programme);
        final Button send = getActivity().findViewById(R.id.send_programme);
        final Button charger = getActivity().findViewById(R.id.charger);
        final Button parametrage=getActivity().findViewById(R.id.parametrage);
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
                save.setClickable(true);
                charger.setClickable(true);
                send.setClickable(true);

                parametrage.setClickable(true);
                getFragmentManager().beginTransaction().remove(SauvegardeProgramme.this).addToBackStack(null).commit();
            }
        });

        oKButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                valeurProgramme nouvelEnregistrement = new valeurProgramme();
                nouvelEnregistrement.acceleration=accelerationEditText.getText().toString();
                nouvelEnregistrement.camera_number=camera_numberEditText.getText().toString();
                    nouvelEnregistrement.direction=directionSwitch.isChecked();
                nouvelEnregistrement.frame=frameEditText.getText().toString();
                nouvelEnregistrement.id=idRentre.getText().toString();
                nouvelEnregistrement.speed= vitesseEditText.getText().toString();
                nouvelEnregistrement.tableSteps=stepsEditText.getText().toString();
                nouvelEnregistrement.timeBetweenPhotosNumber=pause_between_cameraEditText.getText().toString();

                nouvelEnregistrement.focusStacking=focus_stackingSwitch.isChecked();

                majoutAsyncTask.execute(nouvelEnregistrement);

            }
        });
    }

    @Override
    public void ajoutBDDvaleursP(Integer bool) {
        Button save = getActivity().findViewById(R.id.save_programme);
        Button send = getActivity().findViewById(R.id.send_programme);
        Button charger = getActivity().findViewById(R.id.charger);
        Button parametrage=getActivity().findViewById(R.id.parametrage);
        save.setClickable(true);
        charger.setClickable(true);
        send.setClickable(true);

        parametrage.setClickable(true);
        if(bool.equals(1)){
            Toast.makeText(getContext(),"Impossible d'ajouter, supprimez un élément", Toast.LENGTH_LONG).show();
        }
        else if (bool.equals(2)){
            Toast.makeText(getContext(),"Cet élément a écrasé l'élément de même nom", Toast.LENGTH_LONG).show();
        }
        getFragmentManager().beginTransaction().remove(SauvegardeProgramme.this).commit();
    }
}
