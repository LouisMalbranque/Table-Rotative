package com.example.application.Activité_n2.Order;

public class Order {
    private String name;
    private int id;

    Order(){

    }

    public String getType(){
        return this.getClass().getSimpleName();
    }
}
