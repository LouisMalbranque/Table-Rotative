package com.example.louis.plateautournant.Bluetooth;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Serializable;
import java.io.SerializablePermission;
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
                System.out.println("Connexion en cours");
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
                    System.out.println("Connexion établie");

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
        android.os.Handler handlerUI;
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

                            Message msg = Message.obtain();
                            msg.what = Peripherique.CODE_RECEPTION;
                            msg.obj = data;
                            receiveMessage=data;
                            //handlerUI.sendMessage(msg);
                        }
                    }
                    try {
                        Thread.sleep(250);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
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
                Thread.sleep(250);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}