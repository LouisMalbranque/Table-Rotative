package com.example.louis.plateautournant;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.example.louis.plateautournant.Adapter.PeripheriqueAdapter;
import com.example.louis.plateautournant.Bluetooth.Peripherique;
import com.example.louis.plateautournant.Recycler.RecyclerTouch;

import java.util.ArrayList;
import java.util.Set;

import static java.security.AccessController.getContext;


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
    private RecyclerView listePeripheriques;

    private TextView peripheriqueText;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.connexion);

        peripheriqueText = findViewById(R.id.textPeripheriqueName);
        btnConnecter = findViewById(R.id.btnConnecter);

        btnConnecter.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("click sur connecter");
                peripherique.connecter();
                while(!peripherique.isConnected);
                Peripherique.peripherique = peripherique;
                Intent intent = new Intent(Connexion.this, MainActivity.class);
                startActivity(intent);
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
                peripheriques = new ArrayList<>();
                noms = new ArrayList<>();
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


                System.out.println(peripheriques.size());

                listePeripheriques = (RecyclerView) findViewById(R.id.bluetoothList);
                RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this);
                listePeripheriques.setLayoutManager(layoutManager);
                listePeripheriques.setItemAnimator( new DefaultItemAnimator());
                final PeripheriqueAdapter peripheriqueAdapter = new PeripheriqueAdapter(this, peripheriques);
                listePeripheriques.setAdapter(peripheriqueAdapter);

                listePeripheriques.addOnItemTouchListener(new RecyclerTouch(this, listePeripheriques, new RecyclerTouch.ClickListener() {
                    @Override
                    public void onClick(View view, int position) {
                        peripherique = peripheriques.get(position);
                        peripheriqueText.setText(peripherique.getNom());
                    }
                    @Override
                    public void onLongClick(View view, int position) {
                        peripherique = peripheriques.get(position);
                        peripheriqueText.setText(peripherique.getNom());
                    }
                }));
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

