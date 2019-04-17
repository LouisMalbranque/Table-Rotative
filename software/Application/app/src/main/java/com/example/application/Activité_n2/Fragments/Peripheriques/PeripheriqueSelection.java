package com.example.application.Activité_n2.Fragments.Peripheriques;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.example.application.Activité_n2.Adapter.PeripheriqueSelectionAdapter;
import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.R;

import java.util.ArrayList;

public class PeripheriqueSelection extends Fragment {

    public static RecyclerView peripheriquesRecycler;
    public static PeripheriqueSelectionAdapter peripheriqueAdapter;
    public static Button envoyer;

    public PeripheriqueSelection() {

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_peripherique_selection, container, false);
        peripheriquesRecycler = v.findViewById(R.id.peripherique_selection);

        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(getContext());

        final ArrayList<Peripherique> listPeripheriques = new ArrayList<>();
        listPeripheriques.add(new Peripherique("Moteur", false));
        for (int i = 0; i<9; i++){
            listPeripheriques.add(new Peripherique("Camera "+Integer.toString(i), false));
        }

        peripheriqueAdapter = new PeripheriqueSelectionAdapter(getContext(), listPeripheriques);
        peripheriquesRecycler.setLayoutManager(layoutManager);
        peripheriquesRecycler.setItemAnimator( new DefaultItemAnimator());
        peripheriquesRecycler.setAdapter(peripheriqueAdapter);

        envoyer = v.findViewById(R.id.envoyer_peripherique_selection);
        envoyer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data = "0,7";
                for (Peripherique p: listPeripheriques){
                    if (p.isConnecte()) data+=",1";
                    else data+=",0";
                }
                //com.example.application.Activité_n1.Bluetooth.Peripherique.peripherique.envoyer(data);
                System.out.println(data);
                getFragmentManager().beginTransaction().replace(R.id.fragment, Menu.menu).addToBackStack(null).commit();
            }
        });

        return v;
    }
}
