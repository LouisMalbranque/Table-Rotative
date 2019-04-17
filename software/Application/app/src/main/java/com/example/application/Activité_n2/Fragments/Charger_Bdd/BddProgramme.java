package com.example.application.Activité_n2.Fragments.Charger_Bdd;


import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.example.application.Activité_n2.Adapter.ValeurProgrammeAdapter;
import com.example.application.Activité_n2.ChargementBDD.chargementBDDVP;
import com.example.application.Activité_n2.ChargementBDD.chargmentVP;
import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.Activité_n2.Fragments.SauvegardeBDD.SauvegardeProgramme;
import com.example.application.Activité_n2.Interface.SelectionProgramme;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 */

public class BddProgramme extends Fragment implements chargmentVP, SelectionProgramme {

    public static BddProgramme bddProgramme = new BddProgramme();


    private chargementBDDVP mBDDAsyncTask;
    private ListView mListView;

    chargmentVP mListener2=this;

    public BddProgramme() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View view= inflater.inflate(R.layout.fragment_bdd_programme, container, false);
        mListView = view.findViewById(R.id.ListeViewProgramme);
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
        //ProgressBar progression = (ProgressBar) getView().findViewById(R.id.progressBar);
        //progression.setVisibility(View.GONE);
        final ValeurProgrammeAdapter adapter=new ValeurProgrammeAdapter(listeVP);
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
    public void onSelection(valeurProgramme valeurP) {
        final FragmentTransaction transaction = getFragmentManager().beginTransaction();
        final Programme fragment = new Programme();
        final Bundle bundle = new Bundle();
        bundle.putString("vitesse", valeurP.speed);
        bundle.putString("acceleration", valeurP.acceleration);
        bundle.putString("tempsEntrePhotos", valeurP.timeBetweenPhotosNumber);
        bundle.putString("frame", valeurP.frame);
        bundle.putString("camera", valeurP.camera_number);
        bundle.putString("direction", valeurP.direction);
        bundle.putString("tableSteps", valeurP.tableSteps);
        fragment.setArguments(bundle);

        transaction.replace(R.id.fragment,fragment).addToBackStack(null).commit();

    }

    @Override
    public void onDelete() {
        getFragmentManager().beginTransaction().replace(R.id.fragment, Programme.programme).addToBackStack(null).commit();
    }
}
