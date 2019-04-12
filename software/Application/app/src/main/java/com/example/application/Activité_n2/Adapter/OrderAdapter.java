package com.example.application.Activité_n2.Adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.Activité_n2.Order.Order;
import com.example.application.R;

import java.util.ArrayList;
import java.util.List;

public class OrderAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    List<Order> orderList;
    ArrayList<Order> orderArray = new ArrayList<Order>();
    Context context;
    LayoutInflater inflater;

    class ProgrammedViewHolder extends RecyclerView.ViewHolder{

        public ProgrammedViewHolder(View itemView) {
            super(itemView);
        }
    }

    class RealTimeViewHolder extends RecyclerView.ViewHolder {

        public RealTimeViewHolder(View itemView) {
            super(itemView);
        }
    }

    public OrderAdapter(Context c, List<Order> orderList) {
        context=c;
        this.orderList = orderList;
        inflater = LayoutInflater.from(context);
        this.orderArray.addAll(orderList);
    }


    @Override
    public int getItemViewType(int position) {
        if (ListOrder.get(position).getType().equals("ProgrammeOrder")){
            return 0;
        }
        else if (ListOrder.get(position).getType().equals("TempsReelOrder")){
            return 1;
        }
        else{
            return 2;
        }
    }

    @Override
    public int getItemCount() {
        return orderList.size();
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        switch(i){
            case 0: return new ProgrammedViewHolder(LayoutInflater.from(context).inflate(R.layout.fragment_programme,viewGroup,false));
            case 1: return new RealTimeViewHolder(LayoutInflater.from(context).inflate(R.layout.fragment_temps_reel,viewGroup,false));
            default: return new ProgrammedViewHolder(LayoutInflater.from(context).inflate(R.layout.fragment_magneto,viewGroup,false));
        }

    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder viewHolder, int i) {

    }
}
