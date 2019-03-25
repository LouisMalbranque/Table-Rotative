package com.example.louis.plateautournant;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

import com.example.louis.plateautournant.Bluetooth.Peripherique;

import java.util.ArrayList;
import java.util.Set;


public class Connexion extends AppCompatActivity {
    private final static int REQUEST_CODE_ENABLE_BLUETOOTH = 0;
    private Set<BluetoothDevice> devices;
    private BluetoothAdapter adaptateurBluetooth;
    private BroadcastReceiver bluetoothReceiver;
    private ArrayList<Peripherique> peripheriques;
    private Peripherique peripherique;
    private ArrayList<String> noms;
    private Handler handler;

    private Button btnConnecter;
    private Button btnDeconnecter;
    private Button btnSend;
    private Spinner spinnerListePeripheriques;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.connexion);
        btnConnecter = findViewById(R.id.btnConnecter);
        btnDeconnecter = findViewById(R.id.btnDeconnecter);
        btnSend = findViewById(R.id.btnSend);
        spinnerListePeripheriques = findViewById(R.id.spinnerListePeripheriques);

        btnConnecter.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("click sur connecter");
                peripherique.connecter();
                while(!peripherique.isConnected);
                Intent intent = new Intent(Connexion.this, MainActivity.class);
                startActivity(intent);
            }
        });
        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                peripherique.envoyer("1,0,-1,-1,-1,3000,400,360,-1,5000");
            }
        });
        btnDeconnecter.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                peripherique.deconnecter();
            }
        });





        adaptateurBluetooth = BluetoothAdapter.getDefaultAdapter();
        if (adaptateurBluetooth == null)
        {
            Toast.makeText(getApplicationContext(), "Bluetooth non activé !", Toast.LENGTH_SHORT).show();
        }
        else
        {
            if (!adaptateurBluetooth.isEnabled())
            {
                Toast.makeText(getApplicationContext(), "Bluetooth non activé !", Toast.LENGTH_SHORT).show();
                Intent activeBlueTooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(activeBlueTooth, REQUEST_CODE_ENABLE_BLUETOOTH);
                //bluetoothAdapter.enable();
            }
            else
            {
                Toast.makeText(getApplicationContext(), "Bluetooth activé", Toast.LENGTH_SHORT).show();

                // Recherche des périphériques connus
                peripheriques = new ArrayList<Peripherique>();
                noms = new ArrayList<String>();
                devices = adaptateurBluetooth.getBondedDevices();
                for (BluetoothDevice blueDevice : devices)
                {
                    //Toast.makeText(getApplicationContext(), "Périphérique = " + blueDevice.getName(), Toast.LENGTH_SHORT).show();
                    peripheriques.add(new Peripherique(blueDevice, handler));
                    noms.add(blueDevice.getName());
                }

                if(peripheriques.size() == 0)
                    peripheriques.add(new Peripherique(null, handler));

                if(noms.size() == 0)
                    noms.add("Aucun");

                ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, noms);
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
                spinnerListePeripheriques.setAdapter(adapter);
                adapter.setNotifyOnChange(true);

                spinnerListePeripheriques.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
                {
                    @Override
                    public void onItemSelected(AdapterView<?> arg0, View arg1, int position, long id)
                    {
                        //Toast.makeText(getBaseContext(), noms.get(position), Toast.LENGTH_SHORT).show();
                        peripherique = peripheriques.get(position);
                    }

                    @Override
                    public void onNothingSelected(AdapterView<?> arg0)
                    {
                        // TODO Auto-generated method stub
                    }
                });
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode != REQUEST_CODE_ENABLE_BLUETOOTH)
            return;
        if (resultCode == RESULT_OK)
        {
            Toast.makeText(getApplicationContext(), "Bluetooth activé", Toast.LENGTH_SHORT).show();
        }
        else
        {
            Toast.makeText(getApplicationContext(), "Bluetooth non activé !", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        if (adaptateurBluetooth != null){
            adaptateurBluetooth.cancelDiscovery();
        }
        if (bluetoothReceiver != null){
            unregisterReceiver(bluetoothReceiver);
        }
    }
}

