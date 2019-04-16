package com.example.application.Activité_n2.Fragments.Charger_Bdd;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;

import com.example.application.Activité_n2.ChargementBDD.chargementBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargementBDDVR;
import com.example.application.Activité_n2.ChargementBDD.chargmentVP;
import com.example.application.Activité_n2.ChargementBDD.chargmentVR;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;
import com.example.application.objets.valeurReel;

import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 */
public class BddTempsReel extends Fragment implements chargmentVR {

    static public BddTempsReel bddTempsReel =new BddTempsReel();


    private chargementBDDVR mBDDAsyncTask;

    chargmentVR mListener2=this;
    public BddTempsReel() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View view =inflater.inflate(R.layout.fragment_bdd_temps_reel, container, false);
        return view;
    }

    @Override
    public void onStart() {
        super.onStart();
        mBDDAsyncTask=new chargementBDDVR(mListener2);
        mBDDAsyncTask.execute();
    }

    @Override
    public void chargementBDDvaleursR(List<valeurReel> listeVR) {
        ProgressBar progression = (ProgressBar) getView().findViewById(R.id.progressBar2);
        progression.setVisibility(View.GONE);
    }

}
