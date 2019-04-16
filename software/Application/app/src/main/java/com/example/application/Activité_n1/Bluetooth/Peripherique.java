package com.example.application.Activité_n1.Bluetooth;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Looper;
import android.view.View;

import com.example.application.Activité_n2.Fragments.Menu.Menu;
import com.example.application.Activité_n2.Instructions.InstructionCamera;
import com.example.application.Activité_n2.Instructions.InstructionMoteur;
import com.example.application.Activité_n2.Order.ListOrder;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;


public class Peripherique {
    public static Peripherique peripherique;

    private String nom;
    private String adresse;
    private Handler handler = new Handler();
    private BluetoothDevice device = null;
    private BluetoothSocket socket = null;
    private InputStream receiveStream = null;
    private OutputStream sendStream = null;
    private TReception tReception;
    public final static int CODE_RECEPTION = 1;
    public boolean isConnected = false;
    public String receiveMessage;


    public Peripherique(BluetoothDevice device, Handler handler)
    {
        if(device != null)
        {
            this.device = device;
            this.nom = device.getName();
            this.adresse = device.getAddress();
            this.handler = handler;
        }
        else
        {
            this.device = device;
            this.nom = "Aucun";
            this.adresse = "";
            this.handler = handler;
        }

        try
        {
            socket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
            receiveStream = socket.getInputStream();
            sendStream = socket.getOutputStream();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            socket = null;
        }

        if(socket != null)
            tReception = new TReception(handler);
    }

    public String getNom()
    {
        return nom;
    }

    public String getAdresse()
    {
        return adresse;
    }

    public boolean estConnecte()
    {
        // TODO

        return false;
    }

    public void setNom(String nom)
    {
        this.nom = nom;
    }

    public String toString()
    {
        return "\nNom : " + nom + "\nAdresse : " + adresse;
    }

    public void envoyer(String data)
    {
        if(socket == null)
            return;

        try
        {
            sendStream.write(data.getBytes());
            sendStream.flush();
        }
        catch (IOException e)
        {
            System.out.println("<Socket> error send");
            e.printStackTrace();
        }
    }

    public void connecter()
    {
        System.out.println("Connecter");
        new Thread()
        {
            @Override public void run()
            {
                deconnecter();
                System.out.println("connexion en cours");
                try
                {
                    try {
                        socket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
                        tReception = new TReception(handler);
                    }catch(Exception e){
                        e.printStackTrace();
                        return;
                    }
                    socket.connect();
                    sendStream = socket.getOutputStream();
                    receiveStream = socket.getInputStream();
                    tReception.start();


                    isConnected=true;
                    System.out.println("connexion établie");

                }
                catch (IOException e)
                {
                    System.out.println("<Socket> error connect");
                    e.printStackTrace();
                }
            }
        }.start();
    }

    public boolean deconnecter()
    {
        System.out.println("déconnexion");

        isConnected=false;

        try {
            tReception.arreter();
        }catch (Exception e){
            e.printStackTrace();
        }
        if (receiveStream != null) {
            try {receiveStream.close();} catch (Exception e) {}
            receiveStream = null;
        }

        if (sendStream != null) {
            try {sendStream.close();} catch (Exception e) {}
            sendStream = null;
        }

        if (socket != null) {
            try {socket.close();} catch (Exception e) {}
            socket = null;
        }
        System.out.println("déconnexion réussie");
        return true;

    }



    private class TReception extends Thread {
        Handler handlerUI;
        private boolean fini;

        TReception(android.os.Handler h) {
            handlerUI = h;
            fini = false;
        }

        @Override
        public void run() {

            while (!fini) {
                try {
                    if (receiveStream.available() > 0) {
                        byte buffer[] = new byte[100];
                        int k = receiveStream.read(buffer, 0, 100);
                        if (k > 0) {
                            byte rawdata[] = new byte[k];
                            for (int i = 0; i < k; i++)
                                rawdata[i] = buffer[i];

                            String data = new String(rawdata);
                            System.out.println(data);

                            decode(data);
                        }

                    }
                   /* try {
                        Thread.sleep(20);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }*/
                } catch (IOException e) {
                    //System.out.println("<Socket> error read");
                    e.printStackTrace();
                }
            }
        }

        public void arreter() {
            if (fini == false) {
                fini = true;
            }
            try {
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }


        public void decode(String data) {

            String tableauDonnees[] = data.split(",");

            System.out.println(data);
            if (tableauDonnees.length == 0) return;

            if (tableauDonnees[0].equals("fini")) {

                Menu.instructionAdapter.instructionList = null;

                ListOrder.delete(Integer.parseInt(tableauDonnees[1]));

                handlerUI = new Handler(Looper.getMainLooper());
                handlerUI.post(new Runnable() {
                    @Override
                    public void run() {
                        Menu.view.setVisibility(View.INVISIBLE);
                        Menu.listInfos.setVisibility(View.INVISIBLE);
                        Menu.deleteButton.setVisibility(View.INVISIBLE);
                    }
                });
            } else if (tableauDonnees[0].equals("creation")) {
                int idCommande = Integer.parseInt(tableauDonnees[1]);
                int idInstruction = Integer.parseInt(tableauDonnees[2]);

                if (tableauDonnees[3].equals("moteur")) {
                    int acceleration = Integer.parseInt(tableauDonnees[4]);
                    int vitesse = Integer.parseInt(tableauDonnees[5]);
                    int direction = Integer.parseInt(tableauDonnees[6]);
                    int choixRotation = Integer.parseInt(tableauDonnees[7]);
                    int stepsTime = Integer.parseInt(tableauDonnees[8]);

                    InstructionMoteur instructionMoteur = new InstructionMoteur(idCommande, idInstruction, acceleration,
                            vitesse, direction, choixRotation, stepsTime);
                    System.out.println("ajout instruction moteur");
                    ListOrder.getById(idCommande).listInstruction.add(instructionMoteur);

                } else if (tableauDonnees[3].equals("camera")) {

                    int frame = Integer.parseInt(tableauDonnees[4]);
                    int pause = Integer.parseInt(tableauDonnees[5]);

                    InstructionCamera instructionCamera = new InstructionCamera(idCommande, idInstruction, frame, pause);
                    System.out.println("ajout instruction camera");
                    ListOrder.getById(idCommande).listInstruction.add(instructionCamera);

                }


            } else if (tableauDonnees[0].equals("en cours")) {
                int idCommande = Integer.parseInt(tableauDonnees[1]);
                int idInstruction = Integer.parseInt(tableauDonnees[2]);

                System.out.println(idInstruction);
                if (idInstruction > 1) {
                    ListOrder.getById(idCommande).listInstruction.get(idInstruction - 2).termine = true;
                }


            }
            handlerUI = new Handler(Looper.getMainLooper());
            handlerUI.post(new Runnable() {
                @Override
                public void run() {
                    Menu.instructionAdapter.notifyDataSetChanged();
                }
            });
        }
    }
}