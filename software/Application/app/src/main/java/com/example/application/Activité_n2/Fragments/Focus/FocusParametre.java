package com.example.application.Activité_n2.Fragments.Focus;


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
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Spinner;
import android.widget.TextView;

import com.example.application.Activité_n2.Adapter.CameraAdapter;
import com.example.application.Activité_n2.Camera.Camera;
import com.example.application.R;

import java.util.ArrayList;
import java.util.List;

/**
 * A simple {@link Fragment} subclass.
 */
public class FocusParametre extends Fragment {



    static public FocusParametre focusParametre = new FocusParametre();
    static public Button sendFocus;
    static public Button reset;
    static public int compteurPas;
    static public TextView compteur;
    static public Spinner spinnerCamera;
    static boolean spinnerFirstTime=true;
    static public ArrayList<String> spinnerCameraItems = new ArrayList<String>();
    static public int numeroCamera;
    static public CameraAdapter cameraAdapter;
    static public RecyclerView listCamera;

    static public ImageButton ajoutPhotoFocus;
    static public ImageButton deletePhotoFocus;

    static public Button sendPhotoFocus;

    static public List<Camera> cameraList = new ArrayList<>();


    public FocusParametre() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_focus_parametre, container, false);
        sendFocus = v.findViewById(R.id.sendFocus);
        reset = v.findViewById(R.id.reset);
        compteur = v.findViewById(R.id.compteur);
        compteur.setEnabled(false);
        spinnerCamera=v.findViewById(R.id.spinnerFocus);
        listCamera = v.findViewById(R.id.listCamera);
        ajoutPhotoFocus = v.findViewById(R.id.AjoutePhotoFocus);
        deletePhotoFocus=v.findViewById(R.id.DeletePhotoFocus);
        sendPhotoFocus = v.findViewById(R.id.sendPhotoFocus);

        if (spinnerFirstTime){
            spinnerCameraItems.add("Camera 1");
            spinnerCameraItems.add("Camera 2");
            spinnerCameraItems.add("Camera 3");
            spinnerCameraItems.add("Camera 4");
            spinnerCameraItems.add("Camera 5");
            spinnerCameraItems.add("Camera 6");
            spinnerCameraItems.add("Camera 7");
            spinnerCameraItems.add("Camera 8");
            spinnerCameraItems.add("Camera 9");

            for (int i = 0; i<9;i++){
                cameraList.add(new Camera());
            }


            spinnerFirstTime=false;
        }

        ajoutPhotoFocus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (cameraAdapter.nombrePhotoFocus<8){
                    cameraAdapter.nombrePhotoFocus++;
                    cameraAdapter.notifyDataSetChanged();
                }
            }
        });
        deletePhotoFocus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (cameraAdapter.nombrePhotoFocus>1){
                    cameraAdapter.nombrePhotoFocus--;
                    cameraAdapter.notifyDataSetChanged();
                }
            }
        });


        if (cameraAdapter==null){
            cameraAdapter = new CameraAdapter(getContext(),cameraList.get(0).param);
            cameraAdapter.nombrePhotoFocus=1;
        }

        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(getContext());
        listCamera.setLayoutManager(layoutManager);
        listCamera.setItemAnimator( new DefaultItemAnimator());
        listCamera.setAdapter(cameraAdapter);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(getContext(), R.layout.custom_spinner, spinnerCameraItems);
        adapter.setDropDownViewResource(R.layout.custom_spinner);
        spinnerCamera.setAdapter(adapter);
        adapter.setNotifyOnChange(true);
        spinnerCamera.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                for (int i=0; i<9; i++){
                    cameraAdapter.nombreDePas.set(i,0);
                }
                for (int i=0; i<9; i++){
                    cameraAdapter.nombreDePas.set(i, cameraList.get(position).param[i]);
                    System.out.println(cameraAdapter.nombreDePas.get(i));
                }
                cameraAdapter.numeroCamera = position;

                cameraAdapter.notifyDataSetChanged();

                numeroCamera = position;
                compteurPas=0;
                compteur.setText(Integer.toString(compteurPas));

            }
            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });


        sendPhotoFocus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //envoie tram bloc commande
            }
        });

        sendFocus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().remove(FocusParametre.focusParametre).addToBackStack(null).commit();
            }
        });

        reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                compteurPas = 0;
                compteur.setText(Integer.toString(compteurPas));

            }
        });


        return v;
    }

}
