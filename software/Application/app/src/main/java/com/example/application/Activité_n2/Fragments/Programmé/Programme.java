package com.example.application.Activité_n2.Fragments.Programmé;


import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;

import com.example.application.Activité_n1.Bluetooth.Peripherique;
import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargementBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargmentVP;
import com.example.application.Activité_n2.Fragments.Charger_Bdd.BddProgramme;
import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.Activité_n2.Order.ProgrammeOrder;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;


/**
 * A simple {@link Fragment} subclass.
 */
public class Programme extends Fragment {

    private Peripherique peripherique;

    String data;
    public int accelerationInt;
    public int vitesseInt;
    public int stepsInt;
    public int frameInt;
    public int camera_numberInt;
    public int pause_between_cameraInt;



    private ajoutBDDVP majoutAsyncTask;

    static public Programme programme = new Programme();

    public Programme() {
        // Required empty public constructor
    }



    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_programme, container, false);

        peripherique=Peripherique.peripherique;

        EditText text = v.findViewById(R.id.text);

        Button save = v.findViewById(R.id.save_programme);
        Button send = v.findViewById(R.id.send_programme);
        Button charger = v.findViewById(R.id.charger);

        final EditText accelerationEditText = v.findViewById(R.id.AccelerationProgramme);
        final EditText vitesseEditText = v.findViewById(R.id.VitesseProgramme);
        final Switch directionSwitch = v.findViewById(R.id.DirectionProgramme);
        final EditText stepsEditText = v.findViewById(R.id.StepsProgramme);
        final EditText frameEditText = v.findViewById(R.id.FrameProgramme);
        final EditText camera_numberEditText = v.findViewById(R.id.Camera_Number_Programme);
        final EditText pause_between_cameraEditText = v.findViewById(R.id.Pause_between_camera_Programme);
        final Switch focus_stackingSwitch = v.findViewById(R.id.Focus_stacking_Programme);



        charger.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                getFragmentManager().beginTransaction().replace(R.id.fragment, BddProgramme.bddProgramme).addToBackStack(null).commit();
            }
        });

        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                majoutAsyncTask=new ajoutBDDVP();
                valeurProgramme nouvelEnregistrement = new valeurProgramme();
                nouvelEnregistrement.id="exemple1";
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
                nouvelEnregistrement.id="Exemple1";
                nouvelEnregistrement.speed=vitesseEditText.getText().toString();
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

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Menu.spinnerMode.setEnabled(true);

                accelerationInt=Integer.parseInt(accelerationEditText.getText().toString());
                vitesseInt=Integer.parseInt(vitesseEditText.getText().toString());
                stepsInt=Integer.parseInt(stepsEditText.getText().toString());
                frameInt=Integer.parseInt(frameEditText.getText().toString());
                camera_numberInt=Integer.parseInt(camera_numberEditText.getText().toString());
                pause_between_cameraInt=Integer.parseInt(pause_between_cameraEditText.getText().toString());

                ProgrammeOrder programmeOrder = new ProgrammeOrder(accelerationInt,vitesseInt,
                        directionSwitch.isChecked(),stepsInt,frameInt,camera_numberInt,pause_between_cameraInt,focus_stackingSwitch.isChecked());
                ListOrder.list.add(programmeOrder);
                getFragmentManager().beginTransaction().remove(Programme.programme).addToBackStack(null).commit();
                Menu.orderAdapter.notifyDataSetChanged();


                data="";
                data+=programmeOrder.getId()+",";
                data+="0"+",";
                data+=Integer.toString(accelerationInt)+",";
                data+=Integer.toString(vitesseInt)+",";
                data+=Integer.toString(stepsInt)+",";

                if (directionSwitch.isChecked()){
                    data+="1"+",";
                }
                else{
                    data+="0"+",";
                }

                data+="-1"+","; //choix rotation
                data+="-1"+","; //rotation number
                data+="-1"+","; //rotation time

                data+=Integer.toString(frameInt)+",";
                data+=Integer.toString(camera_numberInt)+",";
                data+=Integer.toString(pause_between_cameraInt)+",";




                if (focus_stackingSwitch.isChecked()){
                    data+="1";
                }
                else{
                    data+="0";
                }
                System.out.println(data);

                peripherique.envoyer(data);

            }
        });

        return v;

    }

}
