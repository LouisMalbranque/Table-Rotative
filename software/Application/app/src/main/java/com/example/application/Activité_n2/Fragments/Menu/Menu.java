package com.example.application.Activité_n2.Fragments.Menu;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import com.example.application.Activité_n2.Adapter.OrderAdapter;
import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.Activité_n2.Fragments.Temps_réel.TempsReel;
import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.R;

import java.util.ArrayList;

/**
 * A simple {@link Fragment} subclass.
 */
public class Menu extends Fragment {

    static public Menu menu = new Menu();

    static public Spinner spinnerMode;
    static public ArrayList<String> spinnerModeItems = new ArrayList<String>();
    static boolean spinnerFirstTime=true;
    static public OrderAdapter orderAdapter;
    static public RecyclerView listOrder;



    public Menu() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v= inflater.inflate(R.layout.fragment_menu,container,false);

        spinnerMode=v.findViewById(R.id.spinner);
        listOrder = (RecyclerView) v.findViewById(R.id.orderList);

        if (orderAdapter==null){
            orderAdapter = new OrderAdapter(getContext(),ListOrder.list);
        }

        if (spinnerFirstTime){
            spinnerModeItems.add("New order");
            spinnerModeItems.add("Mode Programmé");
            spinnerModeItems.add("Mode Temps Réel");

            spinnerFirstTime=false;
        }


        ArrayAdapter<String> adapter = new ArrayAdapter<String>(getContext(), R.layout.custom_spinner, spinnerModeItems);
        adapter.setDropDownViewResource(R.layout.custom_spinner);
        spinnerMode.setAdapter(adapter);
        adapter.setNotifyOnChange(true);
        spinnerMode.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switch (position){
                    case 1:
                        getFragmentManager().beginTransaction().replace(R.id.fragment, Programme.programme).commit();
                        spinnerMode.setEnabled(false);
                        spinnerMode.setSelection(0);

                        break;
                    case 2:
                        getFragmentManager().beginTransaction().replace(R.id.fragment, TempsReel.temps_reel).commit();
                        spinnerMode.setEnabled(false);
                        spinnerMode.setSelection(0);
                        break;
                    default:
                        break;

                }
            }
            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });

        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(getContext());
        listOrder.setLayoutManager(layoutManager);
        listOrder.setItemAnimator( new DefaultItemAnimator());
        listOrder.setAdapter(orderAdapter);


        return v;
    }
}
