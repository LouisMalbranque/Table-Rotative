package com.example.application.Activité_n2.Adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.application.Activité_n2.Instructions.Instruction;
import com.example.application.Activité_n2.Instructions.InstructionCamera;
import com.example.application.Activité_n2.Instructions.InstructionMoteur;
import com.example.application.Activité_n2.Order.ListOrder;
import com.example.application.R;

import java.util.List;

public class InstructionAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    public List<Instruction> instructionList;
    Context context;
    LayoutInflater inflater;

    public InstructionAdapter(Context c, List<Instruction> instructionList) {
        context=c;
        this.instructionList = instructionList;
        inflater = LayoutInflater.from(context);
    }

    class InstructionMoteurHolder extends RecyclerView.ViewHolder{
        public int id;
        public TextView instructionMoteur;

        public InstructionMoteurHolder(View v) {
            super(v);
            instructionMoteur = v.findViewById(R.id.instructionMoteur);

        }
    }

    class InstructionCameraHolder extends RecyclerView.ViewHolder{

        public int id;
        public TextView instructionCamera;

        public InstructionCameraHolder(View v) {
            super(v);
            instructionCamera = v.findViewById(R.id.instructionCamera);
        }
    }

    @Override
    public int getItemViewType(int position) {
        if (instructionList.get(position).getType().equals("InstructionMoteur")){
            return 0;
        }
        else if (instructionList.get(position).getType().equals("InstructionCamera")){
            return 1;
        }
        else{
            return 2;
        }
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        switch(i){
            case 0:
                return new InstructionMoteurHolder(LayoutInflater.from(context).inflate(R.layout.instruction_moteur_liste,viewGroup,false));
            case 1:
                return new InstructionCameraHolder(LayoutInflater.from(context).inflate(R.layout.instruction_camera_liste,viewGroup,false));
            default :
                return new InstructionMoteurHolder(LayoutInflater.from(context).inflate(R.layout.instruction_moteur_liste,viewGroup,false));
        }
    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder viewHolder, int i) {

        switch (viewHolder.getItemViewType()) {
            case 0:

                InstructionMoteurHolder instructionMoteurHolder = (InstructionMoteurHolder) viewHolder;
                InstructionMoteur instructionMoteur = (InstructionMoteur)( instructionList.get(i));

                String data="";
                data+=Integer.toString(instructionMoteur.getIdCommande())+"||";
                data+=Integer.toString(instructionMoteur.getIdInstruction())+"||";
                data+=Integer.toString(instructionMoteur.getAcceleration())+"||";
                data+=Integer.toString(instructionMoteur.getVitesse())+"||";
                data+=Integer.toString(instructionMoteur.getDirection())+"||";
                data+=Integer.toString(instructionMoteur.getChoixRotation())+"||";
                data+=Integer.toString(instructionMoteur.getStepsTime());

                if (instructionMoteur.termine==2){
                    data+=" : terminée";
                }else if(instructionMoteur.termine==1){
                    data+=" : en cours";
                }else if (instructionMoteur.termine==0){
                    data+=" : pas commencé";
                }

                instructionMoteurHolder.instructionMoteur.setText(data);

                break;
            case 1:

                InstructionCameraHolder instructionCameraHolder = (InstructionCameraHolder) viewHolder;
                InstructionCamera instructionCamera = (InstructionCamera) ( instructionList.get(i));

                data = "";
                data+=Integer.toString(instructionCamera.getIdCommande())+"||";
                data+=Integer.toString(instructionCamera.getIdInstruction())+"||";
                data+=Integer.toString(instructionCamera.getFrame())+"||";
                data+=Integer.toString(instructionCamera.getPause());

                if (instructionCamera.termine==2){
                    data+=" : terminée";
                }else if(instructionCamera.termine==1){
                    data+=" : en cours";
                }else if (instructionCamera.termine==0){
                    data+=" : pas commencé";
                }

                instructionCameraHolder.instructionCamera.setText(data);

                break;
        }
    }

    @Override
    public int getItemCount() {
        if (instructionList == null){
            return 0;
        }
        else if ( instructionList.size() == 0){
            return 0;
        }
        else{
            return ListOrder.getById(instructionList.get(0).getIdCommande()).listInstruction.size();
        }

    }
}
