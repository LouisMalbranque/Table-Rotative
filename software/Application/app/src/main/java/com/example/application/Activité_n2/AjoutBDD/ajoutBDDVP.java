package com.example.application.Activité_n2.AjoutBDD;

import android.os.AsyncTask;

import com.example.application.BDD.DataBaseHelperValeurProgramme;
import com.example.application.objets.valeurProgramme;


import java.util.List;

public class ajoutBDDVP extends AsyncTask<valeurProgramme,Void, Void> {
    private ajoutVP mListener;

    public ajoutBDDVP(ajoutVP mListener){
        this.mListener=mListener;
    }

    @Override
    protected Void doInBackground(valeurProgramme... strings) {

        List<valeurProgramme> valeurs = DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().getAll();
        valeurs.add(strings[0]);
        DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().insertAll(valeurs);
        return null;
    }

    @Override
    protected void onPostExecute(Void voi) {
        mListener.ajoutBDDvaleursP();

    }
}
