package com.example.application.Activité_n2.Fragments.Charger_Bdd;


import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.Toast;

import com.example.application.Activité_n2.Adapter.ValeurProgrammeAdapter;
import com.example.application.Activité_n2.Adapter.ValeurReelAdapter;
import com.example.application.Activité_n2.ChargementBDD.chargementBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargementBDDVR;
import com.example.application.Activité_n2.ChargementBDD.chargmentVP;
import com.example.application.Activité_n2.ChargementBDD.chargmentVR;
import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.Activité_n2.Fragments.Temps_réel.TempsReel;
import com.example.application.Activité_n2.Interface.SelectionProgramme;
import com.example.application.Activité_n2.Interface.SelectionReel;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;
import com.example.application.objets.valeurReel;

import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 */
public class BddTempsReel extends Fragment implements chargmentVR, SelectionReel {

    static public BddTempsReel bddTempsReel =new BddTempsReel();


    private chargementBDDVR mBDDAsyncTask;
    private ListView mListView;

    chargmentVR mListener2=this;
    public BddTempsReel() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View view =inflater.inflate(R.layout.fragment_bdd_temps_reel, container, false);
        mListView = view.findViewById(R.id.ListeViewReel);
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
        //ProgressBar progression = (ProgressBar) getView().findViewById(R.id.progressBar);
        //progression.setVisibility(View.GONE);
        final ValeurReelAdapter adapter=new ValeurReelAdapter(listeVR);
        mListView.setAdapter(adapter);

        adapter.setmListener(this);

        mListView.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                System.out.println("test1");
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                System.out.println("nothing");
            }
        });
        mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Toast.makeText(getContext(), position, Toast.LENGTH_SHORT).show();
            }
        });


    }
    @Override
    public Context getContext() {
        return super.getContext();
    }

    @Override
    public void onSelection(valeurReel valeurR) {
        final FragmentTransaction transaction = getFragmentManager().beginTransaction();
        final TempsReel fragment = new TempsReel();
        final Bundle bundle = new Bundle();
        bundle.putString("vitesse", valeurR.speed);
        bundle.putString("acceleration", valeurR.acceleration);
        bundle.putString("rotationNumber", valeurR.rotationNumber);
        bundle.putBoolean("rotationMode", valeurR.rotationMode);
        bundle.putBoolean("direction", valeurR.direction);
        bundle.putString("tableSteps", valeurR.tableSteps);
        fragment.setArguments(bundle);

        transaction.replace(R.id.fragment,fragment).addToBackStack(null).commit();

    }

    @Override
    public void onDelete() {
        getFragmentManager().beginTransaction().replace(R.id.fragment, TempsReel.temps_reel).addToBackStack(null).commit();
    }


}
