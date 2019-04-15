package com.example.louis.plateautournant.BDD;

import android.arch.persistence.room.Database;
import android.arch.persistence.room.RoomDatabase;

@Database(entities = {valeurReel.class}, version=2)
public abstract class valeurReelDB extends RoomDatabase {
    public abstract DAOvaleurReel valeurReelDAO();
}
