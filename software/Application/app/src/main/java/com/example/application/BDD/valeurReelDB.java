package com.example.application.BDD;

import android.arch.persistence.room.Database;
import android.arch.persistence.room.RoomDatabase;

import com.example.application.DAO.DAOvaleurReel;
import com.example.application.objets.valeurReel;

@Database(entities = {valeurReel.class}, version=2)
public abstract class valeurReelDB extends RoomDatabase {
    public abstract DAOvaleurReel valeurReelDAO();
}
