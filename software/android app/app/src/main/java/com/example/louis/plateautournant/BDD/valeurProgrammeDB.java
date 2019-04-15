package com.example.louis.plateautournant.BDD;

import android.arch.persistence.room.Database;
import android.arch.persistence.room.RoomDatabase;

@Database(entities = {valeurProgramme.class}, version=2)
public abstract class valeurProgrammeDB extends RoomDatabase {
    public abstract DAOvaleurProgramme valeurProgrammeDAO();
}
