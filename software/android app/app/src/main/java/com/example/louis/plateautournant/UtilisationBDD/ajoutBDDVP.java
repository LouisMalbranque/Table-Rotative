package com.example.louis.plateautournant.UtilisationBDD;

import android.os.AsyncTask;

import com.example.louis.plateautournant.BDD.DataBaseHelperValeurProgramme;
import com.example.louis.plateautournant.BDD.valeurProgramme;

import java.util.List;

public class ajoutBDDVP extends AsyncTask<valeurProgramme,Void, Void> {
    //private ajoutValeur mListener;

    /*public ajoutBDDVP(ajoutValeur mListener){
        this.mListener=mListener;
    }*/

    @Override
    protected Void doInBackground(valeurProgramme... strings) {

        List<valeurProgramme> valeurs = DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().getAll();
        valeurs.add(strings[0]);
        DataBaseHelperValeurProgramme.getInstance().getValeurProgrammeDAO().insertAll(valeurs);
        return null;

    }
}
