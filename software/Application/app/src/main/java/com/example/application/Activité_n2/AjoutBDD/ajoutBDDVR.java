package com.example.application.Activité_n2.AjoutBDD;

import android.os.AsyncTask;

import com.example.application.BDD.DataBaseHelperValeurReel;
import com.example.application.objets.valeurReel;


import java.util.List;

public class ajoutBDDVR extends AsyncTask<valeurReel,Void, Boolean> {
    private ajoutVR mListener;

    public ajoutBDDVR(ajoutVR mListener){
        this.mListener=mListener;
    }
    @Override
    protected Boolean doInBackground(valeurReel... strings) {

        List<valeurReel> valeurs = DataBaseHelperValeurReel.getInstance().getValeurReelDAO().getAll();
        if(valeurs.size()<10){
        valeurs.add(strings[0]);
        DataBaseHelperValeurReel.getInstance().getValeurReelDAO().insertAll(valeurs);
        return true;}
        else{
            DataBaseHelperValeurReel.getInstance().getValeurReelDAO().insertAll(valeurs);
            return false;
        }

    }

    @Override
    protected void onPostExecute(Boolean bool) {
        mListener.ajoutBDDvaleursR(bool);

    }
}
