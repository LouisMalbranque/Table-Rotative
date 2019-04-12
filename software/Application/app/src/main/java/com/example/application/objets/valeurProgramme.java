package com.example.application.objets;

import android.arch.persistence.room.ColumnInfo;
import android.arch.persistence.room.Entity;
import android.arch.persistence.room.PrimaryKey;
import android.support.annotation.NonNull;

@Entity
public class valeurProgramme {
    @PrimaryKey
    @NonNull
    public String id;

    @ColumnInfo
    @NonNull
    public String tableSteps;

    @ColumnInfo
    @NonNull
    public String acceleration;

    @ColumnInfo
    @NonNull
    public String speed;

    @ColumnInfo
    @NonNull
    public String direction;

    @ColumnInfo
    @NonNull
    public String timeBetweenPhotosNumber;

    @ColumnInfo
    @NonNull
    public String cameraNumber;

    @ColumnInfo
    @NonNull
    public String frameNumber;


}
