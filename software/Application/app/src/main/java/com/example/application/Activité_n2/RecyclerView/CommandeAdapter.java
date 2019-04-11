package com.example.application.Activité_n2.RecyclerView;

import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import com.example.application.R;

public class CommandeAdapter extends RecyclerView.Adapter<CommandeAdapter.MyViewHolder>{

    @Override
    public MyViewHolder onCreateViewHolder(ViewGroup viewGroup, int i){
        return null;
    }

    @Override
    public void onBindViewHolder(MyViewHolder myViewHolder, int i){

    }

    @Override
    public int getItemCount(){
        return 0;
    }

    public class MyViewHolder extends RecyclerView.ViewHolder{
        public TextView nameText;

        MyViewHolder(View v){
            super(v);
            //nameText = v.findViewById(R.id.textName);
        }
    }
}
