package com.example.application.Activité_n2.Adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

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

        public TextView programme;
        public ProgrammedViewHolder(View itemView) {
            super(itemView);
            programme=itemView.findViewById(R.id.programme);
        }
    }

    class RealTimeViewHolder extends RecyclerView.ViewHolder {
        public TextView real_time;
        public RealTimeViewHolder(View itemView) {
            super(itemView);
            real_time=itemView.findViewById(R.id.temps_reel);
        }
    }

    public OrderAdapter(Context c, List<Order> orderList) {
        System.out.println("order adapter constructor");
        context=c;
        this.orderList = orderList;
        inflater = LayoutInflater.from(context);
        this.orderArray.addAll(orderList);
    }


    @Override
    public int getItemViewType(int position) {
        System.out.println("getItemViewType");
        if (ListOrder.get(position).getType().equals("ProgrammedMode")){
            return 0;
        }
        else if (ListOrder.get(position).getType().equals("RealTimeMode")){
            return 1;
        }
        else{
            return 0;
        }
    }

    @Override
    public int getItemCount() {
        return orderList.size();
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        System.out.print("creating view holder ");
        System.out.println(i);
        switch(i){
            case 0: return new ProgrammedViewHolder(LayoutInflater.from(context).inflate(R.layout.fragment_programme,viewGroup,false));
            case 1: return new RealTimeViewHolder(LayoutInflater.from(context).inflate(R.layout.fragment_temps_reel,viewGroup,false));
            default: return new ProgrammedViewHolder(LayoutInflater.from(context).inflate(R.layout.fragment_programme,viewGroup,false));
        }

    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder viewHolder, int i) {

    }
}
