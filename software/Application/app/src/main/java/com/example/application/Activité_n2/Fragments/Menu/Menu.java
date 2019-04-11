package com.example.application.Activité_n2.Fragments.Menu;


import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.Fragment;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;

import com.example.application.Activité_n1.Bluetooth.PeripheriqueAdapter;
import com.example.application.Activité_n2.Adapter.OrderAdapter;
import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.Activité_n2.Order.Order;
import com.example.application.Activité_n2.Order.ProgrammedMode;
import com.example.application.Activité_n2.Order.RealTimeMode;
import com.example.application.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class Menu extends android.app.Fragment {

    RecyclerView listOrder;

    public Menu() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_menu, container, false);

        ListOrder.list.add(new ProgrammedMode());
        ListOrder.list.add(new RealTimeMode());
        ListOrder.list.add(new RealTimeMode());
        ListOrder.list.add(new ProgrammedMode());
        ListOrder.list.add(new RealTimeMode());
        System.out.println(ListOrder.list.size());

        for (Order order: ListOrder.list){
            System.out.println(order.getType());
        }


        listOrder = (RecyclerView) v.findViewById(R.id.orderList);
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(getActivity());
        listOrder.setLayoutManager(layoutManager);
        listOrder.setItemAnimator( new DefaultItemAnimator());
        listOrder.setAdapter(new OrderAdapter(getActivity(),ListOrder.list));


        return v;
    }

}
