package com.example.application.Activité_n2.Fragments.Magnéto;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class Magneto extends Fragment {


    public Magneto() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_magneto, container, false);
        return v;
    }

}
