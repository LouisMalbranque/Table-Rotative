package com.example.application.Activité_n2.Fragments.Focus;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class FocusParametre extends Fragment {

    static public FocusParametre focusParametre = new FocusParametre();
    public FocusParametre() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_focus_parametre, container, false);





        return v;
    }

}
