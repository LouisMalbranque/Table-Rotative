package com.example.louis.plateautournant;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;

public class Fragment_RealTimeRotation extends Fragment {

    Switch switchModeTurnTime;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        View v = getView();
        switchModeTurnTime = v.findViewById(R.id.switchTimeTurn);

    }
}
