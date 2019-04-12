package com.example.application.Activité_n2.Order;

public class TempsReelOrder extends Order {
    private int acceleration;
    private int vitesse;
    private boolean direction;
    private int steps;
    private boolean choix_rotation;
    private int rotation_number;
    private int rotation_time;

    public TempsReelOrder(int acceleration, int vitesse, boolean direction, int steps, boolean choix_rotation, int rotation_number, int rotation_time) {
        this.acceleration = acceleration;
        this.vitesse = vitesse;
        this.direction = direction;
        this.steps = steps;
        this.choix_rotation = choix_rotation;
        this.rotation_number = rotation_number;
        this.rotation_time = rotation_time;
    }

    public int getAcceleration() {
        return acceleration;
    }

    public int getVitesse() {
        return vitesse;
    }

    public boolean isDirection() {
        return direction;
    }

    public int getSteps() {
        return steps;
    }

    public boolean isTimeMode() {
        return choix_rotation;
    }

    public int getRotation_number() {
        return rotation_number;
    }

    public int getRotation_time() {
        return rotation_time;
    }

    @Override
    public String createDatagramme() {
        return null;
    }
}
