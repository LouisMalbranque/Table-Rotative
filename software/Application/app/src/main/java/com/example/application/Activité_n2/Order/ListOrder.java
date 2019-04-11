package com.example.application.Activité_n2.Order;

import java.util.ArrayList;
import java.util.List;

public class ListOrder {
    static public List<Order> list = new ArrayList<Order>();

    static public Order get(int i){
        return list.get(i);
    }
}
