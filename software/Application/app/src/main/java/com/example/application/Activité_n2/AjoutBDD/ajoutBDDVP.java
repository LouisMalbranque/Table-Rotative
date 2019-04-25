package com.example.application.Activité_n2.AjoutBDD;

import android.os.AsyncTask;

import com.example.application.BDD.DataBaseHelperValeurProgramme;
import com.example.application.objets.valeurProgramme;


import java.util.List;

public class ajoutBDDVP extends AsyncTask<valeurProgramme,Void, Boolean> {
    private ajoutVP mListener;

    public ajoutBDDVP(ajoutVP mListener){
        this.mListener=mListener;
    }

    @Override
    protected Boolean doInBackground(valeurProgramme... strings) {

        List<valeurProgramme> valeurs = DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().getAll();
        if(valeurs.size()<10){
        valeurs.add(strings[0]);
        DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().insertAll(valeurs);
        return true;}
        else{
            DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().insertAll(valeurs);
            return false;
        }
    }

    @Override
    protected void onPostExecute(Boolean bool) {
        mListener.ajoutBDDvaleursP(bool);

    }
}
