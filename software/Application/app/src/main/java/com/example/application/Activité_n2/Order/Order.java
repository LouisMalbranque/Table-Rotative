package com.example.application.Activité_n2.Order;

public abstract class Order {
    private String name;
    static private int lastid=0;
    private int id;

    Order(){
        id=++lastid;
    }

    public String getType(){
        return this.getClass().getSimpleName();
    }

    public abstract String createDatagramme();

    public int getId() {
        return id;
    }
}
