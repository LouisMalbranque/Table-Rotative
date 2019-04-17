package com.example.application.Activité_n2.Fragments.Temps_réel;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;

import com.example.application.Activité_n1.Bluetooth.Peripherique;
import com.example.application.Activité_n2.AjoutBDD.ajoutBDDVR;
import com.example.application.Activité_n2.Fragments.Charger_Bdd.BddTempsReel;
import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.Activité_n2.Fragments.SauvegardeBDD.SauvegardeProgramme;
import com.example.application.Activité_n2.Fragments.SauvegardeBDD.SauvegardeReel;
import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.Activité_n2.Order.TempsReelOrder;
import com.example.application.R;
import com.example.application.objets.valeurReel;

/**
 * A simple {@link Fragment} subclass.
 */
public class TempsReel extends Fragment {

    static public TempsReel temps_reel = new TempsReel();

    Peripherique peripherique;

    String data;
    public int accelerationInt;
    public int vitesseInt;
    public int stepsInt;
    public int rotation_numberInt;
    SauvegardeReel Sauv_frag = new SauvegardeReel();


    public TempsReel() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_temps_reel, container, false);

        peripherique=Peripherique.peripherique;



        EditText text = v.findViewById(R.id.text);

        Button save = v.findViewById(R.id.save_temps_reel);
        Button send = v.findViewById(R.id.send_temps_reel);
        Button charger = v.findViewById(R.id.charger);

        final EditText accelerationEditText = v.findViewById(R.id.AccelerationTempsReel);
        final EditText vitesseEditText = v.findViewById(R.id.VitesseTempsReel);
        final Switch directionSwitch = v.findViewById(R.id.DirectionTempsReel);
        final EditText stepsEditText = v.findViewById(R.id.StepsTempsReel);
        final Switch choix_rotationSwitch = v.findViewById(R.id.choix_rotation_TempsReel);
        final EditText rotation_numberEditText = v.findViewById(R.id.Rotation_number_TempsReel);
        final TextView rotationText=v.findViewById(R.id.Choix_RotationText);

        if(getArguments()!=null){
            final String speed = getArguments().getString("vitesse");
            vitesseEditText.setText(speed);
            final String acceleration = getArguments().getString("acceleration");
            accelerationEditText.setText(acceleration);
            final String steps = getArguments().getString("tableSteps");
            stepsEditText.setText(steps);
            final String tempsrotat = getArguments().getString("rotationNumber");
            rotation_numberEditText.setText(tempsrotat);

        }

        charger.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().replace(R.id.fragment, BddTempsReel.bddTempsReel).addToBackStack(null).commit();
            }
        });


        choix_rotationSwitch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (choix_rotationSwitch.isChecked()){
                    rotationText.setText("Temps de rotation (s)");
                }
                else{
                    rotationText.setText("Nombre de tours");
                }

            }
        });


        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().add(R.id.container2, Sauv_frag).addToBackStack(null).commit();
            }
        });

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                accelerationInt=Integer.parseInt(accelerationEditText.getText().toString());
                vitesseInt=Integer.parseInt(vitesseEditText.getText().toString());
                stepsInt=Integer.parseInt(stepsEditText.getText().toString());
                rotation_numberInt=Integer.parseInt(rotation_numberEditText.getText().toString());

                TempsReelOrder tempsReelOrder=new TempsReelOrder(accelerationInt,vitesseInt,
                        directionSwitch.isChecked(),stepsInt,choix_rotationSwitch.isChecked(),rotation_numberInt);

                ListOrder.list.add(tempsReelOrder);
                getFragmentManager().beginTransaction().replace(R.id.fragment,Menu.menu).addToBackStack(null).commit();
                Menu.orderAdapter.notifyDataSetChanged();

                data="";
                data+=tempsReelOrder.getId()+",";
                data+="1"+",";
                data+=Integer.toString(accelerationInt)+",";
                data+=Integer.toString(vitesseInt)+",";
                data+=Integer.toString(stepsInt)+",";

                if (directionSwitch.isChecked()){
                    data+="1"+","; // Time mode
                }
                else{
                    data+="0"+","; // turn mode
                }
                if (choix_rotationSwitch.isChecked()){
                    data+="1"+",";
                }
                else{
                    data+="0"+",";
                }
                data+=Integer.toString(rotation_numberInt)+",";

                data+="-1"+",";
                data+="-1"+",";
                data+="-1"+",";
                data+="-1";

                System.out.println(data);

                peripherique.envoyer(data);


            }
        });

        return v;

    }



}
