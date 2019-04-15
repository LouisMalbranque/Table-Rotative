package com.example.application.BDD;

import android.arch.persistence.room.Room;

import com.example.application.DAO.DAOvaleurReel;
import com.example.louis.plateautournant.MainActivity;

public class DataBaseHelperValeurReel {
    static DataBaseHelperValeurReel instance=null;
    private final valeurReelDB db;

    public static DataBaseHelperValeurReel getInstance(){
        if(instance==null){
            instance=new DataBaseHelperValeurReel();
        }
        return instance;
    }

    public DAOvaleurReel getValeurReelDAO(){
        return db.valeurReelDAO();
    }

    public DataBaseHelperValeurReel(){
        db = Room.databaseBuilder(MainActivity.getContext(),valeurReelDB.class,"ma_bdd_valeurReel.db").build();

    }
}
