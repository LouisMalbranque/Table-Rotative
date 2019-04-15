package com.example.application.Activité_n2.Fragments.Charger_Bdd;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import com.example.application.Activité_n2.ChargementBDD.chargementBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargmentVP;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 */

public class BddProgramme extends Fragment implements chargmentVP {

    public static BddProgramme bddProgramme = new BddProgramme();

    private chargementBDDVP mBDDAsyncTask;

    chargmentVP mListener2=this;
    public BddProgramme() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View view= inflater.inflate(R.layout.fragment_bdd_programme, container, false);
        return view;
    }

    @Override
    public void onStart() {
        super.onStart();
        mBDDAsyncTask=new chargementBDDVP(mListener2);
        mBDDAsyncTask.execute();
    }

    @Override
    public void chargementBDDvaleursP(List<valeurProgramme> listeVP) {
        ProgressBar progression = (ProgressBar) getView().findViewById(R.id.progressBar);
        progression.setVisibility(View.GONE);

    }
}
