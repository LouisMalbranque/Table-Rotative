package com.example.application.Activité_n2.Fragments.Menu;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class Menu extends Fragment {
    static public Menu menu = new Menu();

    public Menu() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v= inflater.inflate(R.layout.fragment_menu,container,false);

        Button new_order = v.findViewById(R.id.new_order);
        new_order.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                getFragmentManager().beginTransaction().replace(R.id.MaintActivity,Programme.programme).addToBackStack(null).commit();
            }
        });
        return v;
    }

}
