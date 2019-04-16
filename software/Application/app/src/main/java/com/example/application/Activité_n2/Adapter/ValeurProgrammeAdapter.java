package com.example.application.Activité_n2.Adapter;

import android.graphics.drawable.AdaptiveIconDrawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Switch;
import android.widget.TextView;

import com.example.application.Activité_n2.Fragments.Charger_Bdd.BddProgramme;
import com.example.application.Activité_n2.MainActivity;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

import java.util.List;



import java.util.List;

public class ValeurProgrammeAdapter extends BaseAdapter {
    List<valeurProgramme> mListeVP;
    private LayoutInflater mInflater;

    public ValeurProgrammeAdapter(List<valeurProgramme> ListeVP) {
        this.mListeVP=ListeVP;
        mInflater= LayoutInflater.from(BddProgramme.bddProgramme.getContext());
    }

    @Override
    public int getCount() {
        return null != mListeVP ? mListeVP.size() : 0;
    }

    @Override
    public Object getItem(int position) {
        return null != mListeVP ? mListeVP.get(position) : null;
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final View view = mInflater.inflate(R.layout.valeur_programme_adapter, null);
        final valeurProgramme valeurP = (valeurProgramme) getItem(position);
        final TextView id = view.findViewById(R.id.id);
        id.setText(valeurP.id);
        final TextView speed = view.findViewById(R.id.speed);
        speed.setText(valeurP.speed);
        final TextView acceleration = view.findViewById(R.id.acceleration);
        acceleration.setText(valeurP.acceleration);
        final TextView frame = view.findViewById(R.id.frame);
        frame.setText(valeurP.frame);
        final TextView camera = view.findViewById(R.id.camera);
        camera.setText(valeurP.camera_number);
        final TextView steps = view.findViewById(R.id.steps);
        steps.setText(valeurP.tableSteps);
        final TextView timeBetweenPhotos = view.findViewById(R.id.timeBetweenphotos);
        timeBetweenPhotos.setText(valeurP.timeBetweenPhotosNumber);
        final Switch direction = view.findViewById(R.id.direction);
        if(valeurP.direction=="1"){
            direction.setChecked(true);
        }
        else{
            direction.setChecked(false);
        }
        return view;
    }
}
