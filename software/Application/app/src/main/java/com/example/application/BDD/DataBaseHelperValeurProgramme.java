package com.example.application.BDD;

import android.arch.persistence.room.Room;

import com.example.application.Activité_n2.MainActivity;
import com.example.application.DAO.DAOvaleurProgramme;


public class DataBaseHelperValeurProgramme {
    static DataBaseHelperValeurProgramme instance=null;
    private final valeurProgrammeDB db;

    public static DataBaseHelperValeurProgramme getInstance(){
        if(instance==null){
            instance=new DataBaseHelperValeurProgramme();
        }
        return instance;
    }

    public DAOvaleurProgramme getValeurProgrammeDAO(){
        return db.valeurProgrammeDAO();
    }

    public DataBaseHelperValeurProgramme(){
        db = Room.databaseBuilder(MainActivity.getContext(),valeurProgrammeDB.class,"ma_bdd_valeurProgramme.db").build();

    }
}
