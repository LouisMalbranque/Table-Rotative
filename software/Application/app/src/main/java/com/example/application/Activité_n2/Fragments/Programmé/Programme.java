package com.example.application.Activité_n2.Fragments.Programmé;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;

import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.Activité_n2.Order.ProgrammeOrder;
import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class Programme extends Fragment {

    static public Programme programme = new Programme();
    public int dir;
    public int focus;

    public Programme() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_programme, container, false);

        EditText text = v.findViewById(R.id.text);

        Button save = v.findViewById(R.id.save_programme);
        Button send = v.findViewById(R.id.send_programme);
        Button charger = v.findViewById(R.id.charger);

        final EditText acceleration = v.findViewById(R.id.AccelerationProgramme);
        final EditText vitesse = v.findViewById(R.id.VitesseProgramme);
        final Switch direction = v.findViewById(R.id.DirectionProgramme);
        final EditText steps = v.findViewById(R.id.StepsProgramme);
        final EditText frame = v.findViewById(R.id.FrameProgramme);
        final EditText camera_number = v.findViewById(R.id.Camera_Number_Programme);
        final EditText pause_between_camera = v.findViewById(R.id.Pause_between_camera_Programme);
        final Switch focus_stacking = v.findViewById(R.id.Focus_stacking_Programme);



        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //sauvegarder dans la BDD
            }
        });

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                ProgrammeOrder programmeOrder = new ProgrammeOrder(Integer.parseInt(acceleration.getText().toString()),Integer.parseInt(vitesse.getText().toString()),
                        direction.isChecked(),Integer.parseInt(steps.getText().toString()),Integer.parseInt(frame.getText().toString())
                        ,Integer.parseInt(camera_number.getText().toString()),Integer.parseInt(pause_between_camera.getText().toString()),focus_stacking.isChecked());
                ListOrder.list.add(programmeOrder);
                getFragmentManager().beginTransaction().remove(Programme.programme).addToBackStack(null).commit();
                Menu.orderAdapter.notifyDataSetChanged();

            }
        });

        return v;

    }

}
