package com.example.application.Activité_n2.Fragments.Charger_Bdd;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */

public class BddProgramme extends Fragment {

    public static BddProgramme bddProgramme = new BddProgramme();

    public BddProgramme() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_bdd_programme, container, false);
    }

}
