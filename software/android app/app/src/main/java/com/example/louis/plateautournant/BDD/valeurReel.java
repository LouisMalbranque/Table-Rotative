package com.example.louis.plateautournant.BDD;

import android.arch.persistence.room.ColumnInfo;
import android.arch.persistence.room.Entity;
import android.arch.persistence.room.PrimaryKey;
import android.support.annotation.NonNull;

@Entity
public class valeurReel {
    @PrimaryKey
    @NonNull
    public String id;

    @ColumnInfo

    public String tableSteps;

    @ColumnInfo

    public String acceleration;

    @ColumnInfo

    public String speed;

    @ColumnInfo
    public String direction;


    @ColumnInfo

    public String rotationNumber;

    @ColumnInfo
    public String rotationTime;
}
