package com.example.louis.plateautournant.BDD;

import android.arch.persistence.room.Dao;
import android.arch.persistence.room.Delete;
import android.arch.persistence.room.Insert;
import android.arch.persistence.room.OnConflictStrategy;
import android.arch.persistence.room.Query;

import java.util.List;

@Dao
public interface DAOvaleurProgramme {
    @Query("SELECT * FROM valeurProgramme")
    List<valeurProgramme> getAll();

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insertAll(List<valeurProgramme> valeurProgrammes);

    @Delete
    void delete(valeurProgramme valeurProgrammes);
}