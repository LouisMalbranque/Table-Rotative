package com.example.application.Activité_n2.Adapter;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.example.application.Activité_n2.Fragments.Charger_Bdd.BddProgramme;
import com.example.application.Activité_n2.Fragments.Programmé.Programme;
import com.example.application.Activité_n2.Interface.SelectionProgramme;
import com.example.application.Activité_n2.MainActivity;
import com.example.application.R;
import com.example.application.objets.valeurProgramme;

import java.util.List;

public class ValeurProgrammeAdapter extends BaseAdapter implements View.OnClickListener{
    List<valeurProgramme> mListeVP;
    private LayoutInflater mInflater;
    private SelectionProgramme mListener;

    public void setmListener(SelectionProgramme mListener) {
        this.mListener = mListener;
    }

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

    public View getViewUglyWay(int position, View convertView, ViewGroup parent) {

        final View view = mInflater.inflate(R.layout.valeur_programme_adapter, null);
        final valeurProgramme valeurP = (valeurProgramme) getItem(position);

        final TextView id = view.findViewById(R.id.idProgramme);
        id.setText(valeurP.id);
        final TextView speed = view.findViewById(R.id.speedProgramme);
        speed.setText(valeurP.speed);
        final TextView acceleration = view.findViewById(R.id.accelerationProgramme);
        acceleration.setText(valeurP.acceleration);
        final TextView frame = view.findViewById(R.id.frameProgramme);
        frame.setText(valeurP.frame);
        final TextView camera = view.findViewById(R.id.cameraProgramme);
        camera.setText(valeurP.camera_number);
        final TextView steps = view.findViewById(R.id.stepsProgramme);
        steps.setText(valeurP.tableSteps);
        final TextView timeBetweenPhotos = view.findViewById(R.id.timeBetweenphotosProgramme);
        timeBetweenPhotos.setText(valeurP.timeBetweenPhotosNumber);
        final Switch direction = view.findViewById(R.id.directionProgramme);
        if(valeurP.direction=="1"){
            direction.setChecked(true);
            direction.setClickable(false);
        }
        else{
            direction.setChecked(false);
            direction.setClickable(false);
        }
        final Button selection = view.findViewById(R.id.okProgramme);
        final Button deleteButton = view.findViewById(R.id.deleteProgramme);
        return view;

    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        return getViewBestWay(position,convertView,parent);
    }

    private View getViewBestWay(int position, View convertView, ViewGroup parent) {
        ViewHolderProgramme holder;
        if (null==convertView){
            convertView= mInflater.inflate(R.layout.valeur_programme_adapter,null);
            holder=new ViewHolderProgramme(convertView);
            convertView.setTag(holder);
        } else{
            holder=(ViewHolderProgramme) convertView.getTag();
        }

        final valeurProgramme valeurP = (valeurProgramme) getItem(position);

        holder.id.setText(valeurP.id);
        holder.acceleration.setText(valeurP.acceleration);
        holder.camera.setText(valeurP.camera_number);
        holder.frame.setText(valeurP.frame);
        holder.speed.setText(valeurP.speed);
        holder.steps.setText(valeurP.tableSteps);
        holder.timeBetweenPhotos.setText(valeurP.timeBetweenPhotosNumber);
        if(valeurP.direction=="1"){
            holder.direction.setChecked(true);
            holder.direction.setClickable(false);
        }
        else{
            holder.direction.setChecked(false);
            holder.direction.setClickable(false);
        }
        holder.selection.setTag(position);
        holder.selection.setOnClickListener(this);
        holder.suppression.setTag(position);
        holder.suppression.setOnClickListener(this);

        return convertView;

    }

    @Override
    public void onClick(View v) {
        int position =(Integer) v.getTag();
        final valeurProgramme valeurP = (valeurProgramme) getItem(position);
        String idAPasser=null;
        switch (v.getId()){
            case R.id.deleteProgramme :
                Toast.makeText(MainActivity.getContext(), "Suppression", Toast.LENGTH_LONG).show();
                break;
            case R.id.okProgramme:
                Toast.makeText(MainActivity.getContext(), "Selection", Toast.LENGTH_LONG).show();
                mListener.onSelection(valeurP);
                break;
        }

    }

}
